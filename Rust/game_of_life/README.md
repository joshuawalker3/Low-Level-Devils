# Game of Life

# Project Description
This Rust application simulates a "Game of Life", which is a simple simulation which follows these rules:
    - If a cell is alive with fewer than 2 neighbors it will die
    - if a cell is alive and has 2 or 3 neighbors it will live to the next generation
    - If a cell is alive and has more than 3 neighbors it will die
    - If a cell is dead and has exactly 2 neighbors it will come to life the next generation

The starting generation is either generated randomly or the 1st generation live cells can be imported from a file where each line is a cells coordinates (x and y seperated by whitespace).

# Required Crates
- rand
- termion

# Build and run
1. 
```bash
cargo build
```

2. 
```bash
./path/to/executable <filename>
```
The file arg is for the optional user generated 1st generation.