use tokio::sync::mpsc;
use tokio::time::Duration;
use aht10::Aht10Sensor;

const CTRL_PIN: u32 = 17;
const POLL_TIME: Duration = tokio::time::Duration::from_secs(1);

#[tokio::main]
async fn main() {
    let (tx, mut rx) = mpsc::channel(10);

    let mut aht10 = Aht10Sensor::new(CTRL_PIN, POLL_TIME, tx);

    tokio::task::spawn(async move {
        if let Err(e) = aht10.init_and_poll().await {
            eprintln!("Sensor error: {}", e);
        }
    });

    while let Some((humid, temp)) = rx.recv().await {
        println!("Temp: {}°C, Humidity: {}%", temp, humid);
    }
}
