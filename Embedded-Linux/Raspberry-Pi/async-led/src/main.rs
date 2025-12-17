use anyhow::{Ok, Result};
use futures::StreamExt;
use tokio::time::{Duration, sleep};
use tokio_gpiod::{Active, Chip, Event, Input, Lines, Options, Output};

const RED_BUTTON_LINE: u32 = 17;
const GREEN_BUTTON_LINE: u32 = 27;
const BLUE_BUTTON_LINE: u32 = 22;
const RED_OUTPUT_LINE: u32 = 23;
const GREEN_OUTPUT_LINE: u32 = 24;
const BLUE_OUTPUT_LINE: u32 = 25;
const RED_LED_OUTPUT_INDEX: usize = 0;
const GREEN_LED_OUTPUT_INDEX: usize = 1;
const BLUE_LED_OUPUT_INDEX: usize = 2;
const RED_BUTT_INPUT_INDEX: u8 = 0;
const GREEN_BUTT_INPUT_INDEX: u8 = 1;
const BLUE_BUTT_INPUT_INDEX: u8 = 2;

#[tokio::main]
async fn main() -> Result<()> {
    let chip = Chip::new("/dev/gpiochip0").await?;

    let input_options = Options::input(&[RED_BUTTON_LINE, GREEN_BUTTON_LINE, BLUE_BUTTON_LINE])
        .bias(tokio_gpiod::Bias::PullUp)
        .active(Active::Low)
        .edge(tokio_gpiod::EdgeDetect::Falling)
        .consumer("RGB Inputs");

    let inputs = chip.request_lines(input_options).await?;

    let output_options = Options::output(&[RED_OUTPUT_LINE, GREEN_OUTPUT_LINE, BLUE_OUTPUT_LINE])
        .values([false; 3])
        .consumer("RGB Outputs");

    let outputs = chip.request_lines(output_options).await?;

    tokio::spawn(async move {
        button_task(inputs, outputs).await.unwrap();
    });

    Ok(())
}

async fn button_task(
    mut buttons: tokio_gpiod::Lines<Input>,
    mut leds: tokio_gpiod::Lines<Output>,
) -> Result<()> {
    loop {
        let event = buttons.read_event().await?;

        let mut led_status = [false; 3];
        leds.get_values(led_status).await?;

        match event.line {
            RED_BUTT_INPUT_INDEX => {
                led_status[RED_LED_OUTPUT_INDEX] = !led_status[RED_LED_OUTPUT_INDEX];

                leds.set_values(led_status).await?;

                tokio::time::sleep(Duration::from_millis(30)).await; //Debounce
            }

            GREEN_BUTT_INPUT_INDEX => {
                led_status[GREEN_LED_OUTPUT_INDEX] = !led_status[GREEN_LED_OUTPUT_INDEX];

                leds.set_values(led_status).await?;

                tokio::time::sleep(Duration::from_millis(30)).await; //Debounce
            }

            BLUE_BUTT_INPUT_INDEX => {
                led_status[BLUE_LED_OUPUT_INDEX] = !led_status[BLUE_LED_OUPUT_INDEX];

                leds.set_values(led_status).await?;

                tokio::time::sleep(Duration::from_millis(30)).await; //Debounce
            }

            _ => {
                println!("Unknown input detected!");
                tokio::time::sleep(Duration::from_millis(30)).await; //Debounce
            }
        }
    }

    Ok(())
}
