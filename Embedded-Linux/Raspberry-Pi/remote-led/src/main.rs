use anyhow::{Ok, Result};
use axum::{
    extract::State,
    Router, 
    routing::{get, post},
};
use std::sync::Arc;
use tokio::sync::Mutex;
use tokio_gpiod::{Chip, Lines, Options, Output};

struct AppState {
    led_line: Mutex<Lines<Output>>,
}

#[tokio::main]
async fn main() -> Result<()> {
    let chip = Chip::new("/dev/gpiochip0").await?;
    let output_options = Options::output([17])
        .values([false; 1])
        .consumer("LED Output");
    let output = chip.request_lines(output_options).await?;

    let shared_state = Arc::new(AppState {
        led_line: Mutex::new(output)
    });

    let app = Router::new()
        .route("/", get(index_handler))
        .route("/led", post(led_handler))
        .with_state(shared_state);

    let listener = tokio::net::TcpListener::bind("0.0.0.0:4000").await.unwrap();
    axum::serve(listener, app).await?;

    Ok(())
}

async fn index_handler() -> axum::response::Html<&'static str> {
    axum::response::Html(r#"
        <!DOCTYPE html>
        <html>
            <head>
                <title>LED Control</title>
                <style>
                    body { background: #1a1a1a; color: white; font-family: sans-serif; text-align: center; }
                    .container { margin-top: 50px; }
                    img { border: 4px solid #333; border-radius: 8px; box-shadow: 0 4px 15px rgba(0,0,0,0.5); }
                </style>
            </head>
            <body>
                <div class="container">
                    <h1>Choose state of LED</h1>
                    <input type="radio" id="on" name="state" value="on" onchange="updateLED('on')">
                    <label for="on">ON</label><br>
                    <input type="radio" id="off" name="state" value="off" checked onchange="updateLED('off')">
                    <label for="off">OFF</label><br>
                </div>

                <script>
                    function updateLED(state) {
                        fetch('/led', {
                            method: 'POST',
                            body: state
                        });
                    }
                </script>
            </body>
        </html>
    "#)
}

async fn led_handler(State(state): State<Arc<AppState>>, body: String) -> impl axum::response::IntoResponse {
    println!("Received: {}", body);

    let mut line = state.led_line.lock().await;

    match body.as_str() {
        "on" => {
            let _ = line.set_values([true; 1]).await;
        }

        "off" => {
            let _ = line.set_values([false; 1]).await;
        }

        _ => return "Invalid State",
    };

    "OK"
}