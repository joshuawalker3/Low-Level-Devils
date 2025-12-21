use i2cdev::core::*;
use i2cdev::linux::LinuxI2CDevice;
use std::io;
use tokio::sync::mpsc;
use tokio::time::Duration;

const AHT10_ADDRESS: u16 = 0x38;
const READ_DATA_CMD_BYTE_1: u8 = 0xAC;
const READ_DATA_CMD_BYTE_2: u8 = 0x33;
const READ_DATA_CMD_BYTE_3: u8 = 0x00;
const DATA_BUFFER_SIZE: usize = 6;
const READ_WAIT_TIME: Duration = Duration::from_millis(80);

#[derive(Debug)]
struct Aht10Data {
    temp: i32,
    humidity: u32,
}

fn calculate_relative_humidity(raw_humidity: u32) -> u32 {
    (raw_humidity * 100) >> 20
}

fn calculate_temperature(raw_temperature: u32) -> i32 {
    (((raw_temperature as i32) * 200) >> 20) - 50
}

fn generate_sensor_data(data_bytes: [u8; 6]) -> Aht10Data {
    let raw_humidity: u32 = ((data_bytes[1] as u32) << 12)
        | ((data_bytes[2] as u32) << 4)
        | (((data_bytes[3] as u32) & 0xF0) >> 4);
    let raw_temperature: u32 = (((data_bytes[3] as u32) & 0x0F) << 16)
        | ((data_bytes[4] as u32) << 8)
        | (data_bytes[5] as u32);

    Aht10Data {
        temp: calculate_temperature(raw_temperature),
        humidity: calculate_relative_humidity(raw_humidity),
    }
}

fn read_sensor(dev: &mut LinuxI2CDevice) -> io::Result<Aht10Data> {
    let read_cmd_buffer = [
        READ_DATA_CMD_BYTE_1,
        READ_DATA_CMD_BYTE_2,
        READ_DATA_CMD_BYTE_3,
    ];
    let mut data_buffer = [0u8; DATA_BUFFER_SIZE];

    dev.write(&read_cmd_buffer)?;

    std::thread::sleep(READ_WAIT_TIME);

    dev.read(&mut data_buffer)?;

    Ok(generate_sensor_data(data_buffer))
}

#[tokio::main]
async fn main() {
    let (tx, mut rx) = mpsc::channel(10);

    tokio::task::spawn_blocking(move || {
        let mut dev =
            LinuxI2CDevice::new("/dev/i2c-1", AHT10_ADDRESS).expect("Failed to open I2C bus");

        loop {
            match read_sensor(&mut dev) {
                Ok(data) => {
                    if tx.blocking_send(data).is_err() {
                        break;
                    }
                }
                Err(e) => eprintln!("Join error: {}", e),
            }

            std::thread::sleep(Duration::from_secs(1));
        }
    });

    while let Some(data) = rx.recv().await {
        println!("Temp: {}°C, Humidity: {}%", data.temp, data.humidity);
    }
}
