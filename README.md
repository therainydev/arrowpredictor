# Arrow predictor

This is a simple C program that predicts what arrow key you'll press next using a neural network. It's similar to the
core of the TokiLM-n language model.

## Compiling
```sh
cc -lncurses arrowpredictor.c -o arrowpredictor
```
Requires `ncurses` (for the TUI).

## Usage
Run the program without any arguments. It'll throw away any arguments you give to it, anyways. You'll be presented a
TUI explaining how to use this program and what it does.
