#include <curses.h>
#include <inttypes.h>
#include <signal.h>
#include <stdlib.h>

static void cleanup(int sn) {
	endwin();
	_Exit(0);
}

int main(void) {
	signal(SIGINT, cleanup);
	signal(SIGTERM, cleanup);
	initscr();
	keypad(stdscr, TRUE);
	noecho();
	int c;
	uint64_t t = 0, p = 0;
	uint8_t prev = 0;
	uint64_t *seq = calloc(256, sizeof(uint64_t));
	if (seq == NULL) {
		fputs("memory allocation failed\n", stderr);
		return 1;
	}
	printw(
		"Welcome to the arrow predictor, also known as an Aaronson Oracle!\n"
		"To begin, start pressing the left and right arrow keys.\n"
		"For most people, this program will correctly predict their presses about 70%% of the time.\n"
		"Good luck being random!\n"
		"If you're tired of this program, you can press Q or CTRL+C to quit it.\n"
	);
	while (1) {
		prev <<= 1;
		printw(
			"You have pressed %"PRIu64" arrow keys, of which %"PRIu64" presses were correctly predicted.\n"
			"So far, the predictions have been %2.1lf%% accurate.\n"
			"The last 7 keys you pressed were %c%c%c%c%c%c%c.\n"
			"You have been in this situation %"PRIu64" times before, and you pressed...\n"
			" - the left  arrow %"PRIu64" times.\n"
			" - the right arrow %"PRIu64" times.\n"
			"You are predicted to press the %s arrow.\n",
			t,
			p,
			((double)p / (double)t) * 100,
			(prev & UINT8_C(128)) ? '>' : '<',
			(prev & UINT8_C( 64)) ? '>' : '<',
			(prev & UINT8_C( 32)) ? '>' : '<',
			(prev & UINT8_C( 16)) ? '>' : '<',
			(prev & UINT8_C(  8)) ? '>' : '<',
			(prev & UINT8_C(  4)) ? '>' : '<',
			(prev & UINT8_C(  2)) ? '>' : '<',
			seq[prev] + seq[prev|UINT8_C(1)],
			seq[prev],
			seq[prev|UINT8_C(1)],
			(seq[prev] > seq[prev|UINT8_C(1)]) ? "left" : "right"
		);
		c = getch();
		clear();
		switch (c) {
			case KEY_LEFT:
				printw("You pressed the left arrow.\n");
				if (seq[prev] > seq[prev|UINT8_C(1)]) {
					p++;
				}
				break;
			case KEY_RIGHT:
				printw("You pressed the right arrow.\n");
				if (seq[prev] <= seq[prev|UINT8_C(1)]) {
					p++;
				}
				prev |= UINT8_C(1);
				break;
			case 'q':
				cleanup(0);
		}
		seq[prev]++;
		t++;
	}
}
