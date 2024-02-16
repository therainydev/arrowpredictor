#include <curses.h>
#include <inttypes.h>
#include <signal.h>
#include <stdlib.h>

void cleanup(void) {
	endwin();
	_Exit(0);
}

int main(void) {
	initscr();
	keypad(stdscr, TRUE);
	noecho();
	int c;
	/* data structure:
	 * array of 256 uint64_t, indexed by uint8_t, left = 0, right = 1
	 * uint8_t structure is ABCDEFGH, A-G are previous presses, H is press to predict
	 */
	uint64_t *seq = calloc(256, sizeof(uint64_t));
	if (seq == NULL) {
		fputs("memory allocation failed\n", stderr);
		return 1;
	}
	printw("press left or right arrow key to be predicted, or press Q to quit\n");
	while (1) {
		c = getch();
		switch (c) {
			case KEY_LEFT:
				printw("you pressed left arrow\n");
				break;
			case KEY_RIGHT:
				printw("you pressed right arrow\n");
				break;
			case 'q':
				cleanup();
		}
	}
}
