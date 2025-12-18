use anyhow::{Ok, Result};
use tokio::time::Duration;
use tokio_gpiod::{Chip, Input, Options, Output};

const RED_BUTTON_LINE: u32 = 17;
const GREEN_BUTTON_LINE: u32 = 27;
const BLUE_BUTTON_LINE: u32 = 22;
const RED_OUTPUT_LINE: u32 = 23;
const GREEN_OUTPUT_LINE: u32 = 24;
const BLUE_OUTPUT_LINE: u32 = 25;
const RED_LED_OUTPUT_INDEX: usize = 0;
const GREEN_LED_OUTPUT_INDEX: usize = 1;
const BLUE_LED_OUTPUT_INDEX: usize = 2;
const RED_BUTT_INPUT_INDEX: u8 = 0;
const GREEN_BUTT_INPUT_INDEX: u8 = 1;
const BLUE_BUTT_INPUT_INDEX: u8 = 2;

#[tokio::main]
async fn main() -> Result<()> {
    let chip = Chip::new("/dev/gpiochip0").await?;

    let input_options = Options::input(&[RED_BUTTON_LINE, GREEN_BUTTON_LINE, BLUE_BUTTON_LINE])
        .bias(tokio_gpiod::Bias::PullUp)
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

    loop {
        tokio::time::sleep(Duration::from_secs(60)).await;
    }

    Ok(())
}

async fn button_task(
    mut buttons: tokio_gpiod::Lines<Input>,
    leds: tokio_gpiod::Lines<Output>,
) -> Result<()> {
    loop {
        let event = loop {
            match buttons.read_event().await {
                Result::Ok(ev) => break ev,
                Result::Err(e) => {
                    if e.kind() == std::io::ErrorKind::WouldBlock {
                        continue;
                    } else {
                        return Err(e.into());
                    }
                }
            };
        };

        println!("Made it here! event = {:?}", event);

        let mut led_status = leds.get_values([false; 3]).await?;

        match event.line {
            RED_BUTT_INPUT_INDEX => {
                led_status[RED_LED_OUTPUT_INDEX] ^= true;
            }

            GREEN_BUTT_INPUT_INDEX => {
                led_status[GREEN_LED_OUTPUT_INDEX] ^= true;
            }

            BLUE_BUTT_INPUT_INDEX => {
                led_status[BLUE_LED_OUTPUT_INDEX] ^= true;
            }

            _ => {
                println!("Unknown input detected!");
            }
        };

        leds.set_values(led_status).await?;

        tokio::time::sleep(Duration::from_millis(30)).await; //Debounce
    }

    Ok(())
}
