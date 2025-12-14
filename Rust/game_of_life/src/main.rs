extern crate rand;
extern crate termion;

use std::{env, thread, time};
use std::fs::File;
use std::io::{BufRead, BufReader};
use termion::{clear, color};

const DEFAULT_ROWS: usize = 75;
const DEFAULT_COLS: usize = 75;
const SLEEP_TIME: u64 = 2;

fn main() {
    let mut world = [[0u8; DEFAULT_COLS]; DEFAULT_ROWS];
    let mut generations = 0;

    let args: Vec<String> = env::args().collect();

    if args.len() < 2 {
        for i in 0..DEFAULT_ROWS {
            for j in 0..DEFAULT_COLS {
                if rand::random() {
                    world[i][j] = 1;
                } else {
                    world[i][j] = 0;
                }
            }
        }
    } else {
        let filename = env::args().nth(1).unwrap();
        world = populate_from_file(filename);
    } 

    println!("Population at generation {} is {}", generations, census(world));

    for _gens in 0..100 {
        let temp = generation(world);
        world = temp;

        generations += 1;

        println!("{}", clear::All);

        display_world(world);

        println!("{blue}Population at generation {g} is {c}", 
            blue = color::Fg(color::Blue), 
            g = generations, 
            c = census(world));

        thread::sleep(time::Duration::from_secs(SLEEP_TIME));
    }
}

fn census(_world: [[u8; DEFAULT_COLS]; DEFAULT_ROWS]) -> u16 {
    let mut count = 0;

    for i in 0..DEFAULT_ROWS {
        for j in 0..DEFAULT_COLS {
            if _world[i][j] == 1 {
                count += 1;
            } 
        }
    }

    count
}

fn generation(_world: [[u8; DEFAULT_COLS]; DEFAULT_ROWS]) -> [[u8; DEFAULT_COLS]; DEFAULT_ROWS] {
    let mut newworld = [[0u8; DEFAULT_COLS]; DEFAULT_ROWS];

    for i in 0..DEFAULT_ROWS {
        for j in 0..DEFAULT_COLS {
            let mut count = 0;

            if i > 0 {
                count += _world[i - 1][j]; //check top middle
            }

            if i > 0 && j > 0 {
                count += _world[i - 1][j - 1]; //check top left
            }

            if i > 0 && j < DEFAULT_COLS - 1 {
                count += _world[i - 1][j + 1]; //check top right
            }

            if i < DEFAULT_ROWS - 1 && j > 0 {
                count += _world[i + 1][j - 1]; //check bottom left
            }

            if i < DEFAULT_ROWS - 1 {
                count += _world[i + 1][j]; //check bottom middle
            }

            if i < DEFAULT_ROWS - 1 && j < DEFAULT_COLS - 1 {
                count += _world[i + 1][j + 1]; //check bottom right
            }

            if j > 0 {
                count += _world[i][j - 1]; //check middle left
            }

            if j < DEFAULT_COLS - 1 {
                count += _world[i][j + 1]; //check middle right
            }

            newworld[i][j] = 0;

            if (count < 2 || count > 3) && (_world[i][j] == 1) {
                newworld[i][j] = 0;
            }

            if _world[i][j] == 1 && (count == 2 || count == 3) {
                newworld[i][j] = 1;
            }

            if _world[i][j] == 0 && count == 3 {
                newworld[i][j] = 1;
            } 
        }
    }

    newworld
}

fn populate_from_file(filename: String) -> [[u8; DEFAULT_COLS]; DEFAULT_ROWS] {
    let mut newworld = [[0u8; DEFAULT_COLS]; DEFAULT_ROWS];
    let file = File::open(filename).unwrap();
    let reader = BufReader::new(file);
    let mut pairs: Vec<(usize, usize)> = Vec::new();

    for (_index, line) in reader.lines().enumerate() {
        let l = line.unwrap();
        let mut words = l.split_whitespace();

        let left = words.next().unwrap().parse::<usize>().unwrap();
        let right = words.next().unwrap().parse::<usize>().unwrap();

        if !(left >= DEFAULT_ROWS || right >= DEFAULT_COLS) {
            pairs.push((left, right));
        }
    }

    for i in 0..DEFAULT_ROWS {
        for j in 0..DEFAULT_COLS {
            newworld[i][j] = 0;
        }
    }

    for (x, y) in pairs {
        newworld[x][y] = 1;
    }

    newworld
}

fn display_world(world: [[u8; DEFAULT_COLS]; DEFAULT_ROWS]) {
    for i in 0..DEFAULT_ROWS {
        for j in 0..DEFAULT_COLS {
            if world[i][j] == 1 {
                print!("{green}*", 
                green = color::Fg(color::Green));
            } else {
                print!(" ");
            }
        }

        println!("");
    }
}