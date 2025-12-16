use rppal::gpio::Gpio;
use std::{thread, time::Duration};

const SLEEP_TIME: u64 = 500;

fn main() -> Result<(), Box<dyn std::error::Error>> {
    // BCM numbering (i.e. GPIO 17 is physical pin 11 on the gpio header but use 17)
    let gpio = Gpio::new()?; //get new gpio
    let mut pin = gpio.get(17)?.into_output(); //get pin 17 and make output

    //infinite loop that blinks LED
    loop {
        println!("Setting pin hi");

        pin.set_high();
        thread::sleep(Duration::from_millis(SLEEP_TIME));

        println!("Setting pin low");

        pin.set_low();
        thread::sleep(Duration::from_millis(SLEEP_TIME));
    }
}
