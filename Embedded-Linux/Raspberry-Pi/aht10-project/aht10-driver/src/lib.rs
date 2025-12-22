use anyhow::{Ok, Result};
use i2cdev::core::*;
use i2cdev::linux::LinuxI2CDevice;
use tokio::sync::mpsc;
use tokio::time::Duration;
use tokio_gpiod::{Chip, Options};

const AHT10_ADDRESS: u16 = 0x38;
const READ_DATA_CMD_BYTE_1: u8 = 0xAC;
const READ_DATA_CMD_BYTE_2: u8 = 0x33;
const READ_DATA_CMD_BYTE_3: u8 = 0x00;
const DATA_BUFFER_SIZE: usize = 6;
const POWER_WAIT_TIME: Duration = Duration::from_millis(20);
const READ_WAIT_TIME: Duration = Duration::from_millis(80);

pub struct Aht10Sensor {
    ctrl_pin: u32,
    temp: i32,
    humidity: u32,
    chip: Option<Chip>,
    output: Option<tokio_gpiod::Lines<tokio_gpiod::Output>>,
    dev: Option<LinuxI2CDevice>,
    poll_time: Duration,
    tx: mpsc::Sender<(u32, i32)>,
}

impl Aht10Sensor {
    pub fn new(ctrl_pin: u32, poll_time: Duration, tx: mpsc::Sender<(u32, i32)>) -> Self {
        Self {
            ctrl_pin,
            humidity: 0,
            temp: 0,
            chip: None,
            output: None,
            dev: None,
            poll_time,
            tx,
        }
    }

    pub async fn init_and_poll(&mut self) -> Result<()> {
        let chip = Chip::new("/dev/gpiochip0").await?;

        let output_options = Options::output([self.ctrl_pin])
            .values([false; 1])
            .consumer("AHT10 Power control");
        let output = chip.request_lines(output_options).await?;
        let dev = LinuxI2CDevice::new("/dev/i2c-1", AHT10_ADDRESS)?;

        self.chip = Some(chip);
        self.output = Some(output);
        self.dev = Some(dev);

        loop {
            self.read_sensor().await?;

            let hum = self.humidity;
            let temp = self.temp;

            self.tx.send((hum, temp)).await?;

            tokio::time::sleep(self.poll_time).await;
        }

        Ok(())
    }

    fn calculate_relative_humidity(&self, raw_humidity: u32) -> u32 {
        (raw_humidity * 100) >> 20
    }

    fn calculate_temperature(&self, raw_temperature: u32) -> i32 {
        (((raw_temperature as i32) * 200) >> 20) - 50
    }

    fn generate_sensor_data(&mut self, data_bytes: [u8; 6]) -> Result<()> {
        let raw_humidity: u32 = ((data_bytes[1] as u32) << 12)
            | ((data_bytes[2] as u32) << 4)
            | (((data_bytes[3] as u32) & 0xF0) >> 4);
        let raw_temperature: u32 = (((data_bytes[3] as u32) & 0x0F) << 16)
            | ((data_bytes[4] as u32) << 8)
            | (data_bytes[5] as u32);

        self.temp = self.calculate_temperature(raw_temperature);
        self.humidity = self.calculate_relative_humidity(raw_humidity);

        Ok(())
    }

    async fn read_sensor(&mut self) -> Result<()> {
        let dev = self.dev.as_mut().expect("Device not initialized");
        let output = self.output.as_mut().expect("Power not initialized");

        output.set_values([true; 1]).await?;

        tokio::time::sleep(POWER_WAIT_TIME).await;

        let read_cmd_buffer = [
            READ_DATA_CMD_BYTE_1,
            READ_DATA_CMD_BYTE_2,
            READ_DATA_CMD_BYTE_3,
        ];

        let mut data_bytes = [0u8; DATA_BUFFER_SIZE];

        dev.write(&read_cmd_buffer)?;

        tokio::time::sleep(READ_WAIT_TIME).await;

        dev.read(&mut data_bytes)?;

        output.set_values([false; 1]).await?;

        self.generate_sensor_data(data_bytes)?;

        Ok(())
    }
}
