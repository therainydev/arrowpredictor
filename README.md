# Arrow predictor

**Note: Implementation of a neural network is ongoing in the `net` branch.**

This is a simple C program that predicts what arrow key you'll press next using a probabilistic model. It's similar to
the core of the TokiLM-p language model.

## Compiling
```sh
cc -lncurses arrowpredictor.c -o arrowpredictor
```
Requires `ncurses` (for the TUI).

## Usage
Without any arguments, presents a TUI which prompts the user to press arrow keys while predicting the next press, and
updates predictions live.

`-h`: prints a help message.
