use anyhow::{Ok, Result};
use futures::StreamExt;
use tokio::time::{Duration, sleep};
use tokio_gpiod::{Chip, Lines, Options};

const RED_BUTTON: u32 = 17;
const GREEN_BUTTON: u32 = 27;
const BLUE_BUTTON: u32 = 22;
const RED_OUTPUT: u32 = 23;
const GREEN_OUTPUT: u32 = 24;
const BLUE_OUTPUT: u32 = 25;

#[tokio::main]
async fn main() -> Result<()> {
    let chip = Chip::new("/dev/gpiochip0").await?;

    let input_options = Options::input([RED_BUTTON, GREEN_BUTTON, BLUE_BUTTON])
        .bias(tokio_gpiod::Bias::PullUp)
        .edge(tokio_gpiod::EdgeDetect::Falling)
        .consumer("RGB Inputs");

    let inputs = chip.request_lines(input_options).await?;

    let output_options = Options::output([RED_OUTPUT, GREEN_OUTPUT, BLUE_OUTPUT])
        .values([false; 3])
        .consumer("RGB Outputs");

    let outputs = chip.request_lines(output_options).await?;

    Ok(())
}
