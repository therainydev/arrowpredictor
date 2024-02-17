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
		"press left or right arrow key to be predicted, or press Q to quit\n"
	);
	while (1) {
		prev <<= 1;
		printw(
			"total: %"PRIu64" presses\n"
			"correctly predicted: %"PRIu64" presses\n"
			"prev: %c%c%c%c%c%c%c\n"
			"before: %"PRIu64" <\n"
			"        %"PRIu64" >\n"
			"predicted: %c\n",
			t,
			p,
			(prev & UINT8_C(128)) ? '>' : '<',
			(prev & UINT8_C( 64)) ? '>' : '<',
			(prev & UINT8_C( 32)) ? '>' : '<',
			(prev & UINT8_C( 16)) ? '>' : '<',
			(prev & UINT8_C(  8)) ? '>' : '<',
			(prev & UINT8_C(  4)) ? '>' : '<',
			(prev & UINT8_C(  2)) ? '>' : '<',
			seq[prev],
			seq[prev|UINT8_C(1)],
			(seq[prev] > seq[prev|UINT8_C(1)]) ? '<': '>'
		);
		c = getch();
		clear();
		switch (c) {
			case KEY_LEFT:
				printw("you pressed left arrow\n");
				if (seq[prev] > seq[prev|UINT8_C(1)]) {
					p++;
				}
				break;
			case KEY_RIGHT:
				printw("you pressed right arrow\n");
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
