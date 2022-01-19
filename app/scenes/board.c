#include "../game_scenes.h"
#include "mkboard.h"
#include <math.h>

int sxi = 0;
const char* bgLine = "+-+-+";

#define SUDOKU_RNUM sudoku_rnum_gen() 
int isGenerating = 0;

#define BOARD_SIZE 9*9
char cheater_anchor[16] = "CHEATERSIALAN!!";
char isPaused = 0;
volatile char board_real[BOARD_SIZE];
volatile char board_disp[BOARD_SIZE];
volatile char board_mask[BOARD_SIZE];

double currentGameTime;
char checkbuffr[9];
char c = '\0';


#define BOARD_I(x,y) ((y * 9) + x)

/**
Chunk ordering:
+-+-+-+
|1|2|3|
+-+-+-+
|4|5|6|
+-+-+-+
|7|8|9|
+-+-+-+

*/

void checkbuffr_clear() {
	memset(checkbuffr, 0, 9);
}

int board_is_num_valid_here(char c, int x, int y, int real) {
	int i, ii, ix, iy;
	char* board = real == 1 ? board_real : board_disp;

	// Horizontal check
	{
		checkbuffr_clear();
		for (i = 0; i < 9; i++) {
			if (i != x) {
				int bI = BOARD_I(i, y);
				checkbuffr[i] = board[bI];
				for (ii = 0; ii < 9; ii++) {
					if (checkbuffr[ii] == c) {
						println("Duplicate found horizontally at %s @ [%i,%i] == [%i,%i] == %i", real ? "Real" : "Display", x, y, ii, y, c);
						return 0;
					}
				}
			}
		}
	}

	// Vertical check
	{
		checkbuffr_clear();
		for (i = 0; i < 9; i++) {
			if (i != y) {
				int bI = BOARD_I(x, i);
				checkbuffr[i] = board[bI];
				for (ii = 0; ii < 9; ii++) {
					if (checkbuffr[ii] == c) {
						println("Duplicate found vertically at %s @ [%i,%i] == [%i,%i] == %i", real ? "Real" : "Display", x, y, x, ii, c);
						return 0;
					}
				}
			}
		}
	}

	// Chunk check
	{
		checkbuffr_clear();
		int cX = (int)floor(x / 3.0f);
		int cY = (int)floor(y / 3.0f);
		for (iy = 0; iy < 3; iy++) {
			for (ix = 0; ix < 3; ix++) {
				if (cX + ix != x && cY + iy == y) {
					int bI = BOARD_I(cX + ix, cY + iy);
					int cbI = ((iy * 3) + ix);
					checkbuffr[cbI] = board[bI];
					for (ii = 0; ii < y && ii < 9; ii++) {
						if (checkbuffr[ii] == c) {
							println("Duplicate found chunkly at %s @ [%i,%i] == [%i,%i] == %i", real ? "Real" : "Display", x, y, cX + ix, cY + iy, c);
							return 0;
						}
					}
				}
			}
		}
	}
	return 1;
}

char sdNum = 0;

char swapBuffer[2][9];

void board_swap_cols(int from, int to) {
	int y;
	for (y = 0; y < 9; y++) {
		swapBuffer[0][y] = board_real[BOARD_I(from, y)];
	}
	for (y = 0; y < 9; y++) {
		swapBuffer[1][y] = board_real[BOARD_I(to, y)];
	}
	for (y = 0; y < 9; y++) {
		board_real[BOARD_I(to, y)] = swapBuffer[0][y];
	}
	for (y = 0; y < 9; y++) {
		board_real[BOARD_I(from, y)] = swapBuffer[1][y];
	}
}

void board_swap_rows(int from, int to) {
	memcpy(swapBuffer[0], board_real + (from * 9), 9);
	memcpy(swapBuffer[1], board_real + (to * 9), 9);
	memcpy(board_real + (from * 9), swapBuffer[1], 9);
	memcpy(board_real + (to * 9),   swapBuffer[0], 9);
}

void board_swap_rows_by_methods_offset(int r0, int off) {
	int rMod = (int)fmod(r0, 2.0);
	switch (rMod) {
	default:
	case 0: board_swap_rows(off + 0, off + 1); break;
	case 1: board_swap_rows(off + 0, off + 2); break;
	case 2: board_swap_rows(off + 1, off + 2); break;
	}
}

void board_swap_cols_by_methods_offset(int r0, int off) {
	int rMod = (int)fmod(r0, 2.0);
	switch (rMod) {
	default:
	case 0: board_swap_cols(off + 0, off + 1); break;
	case 1: board_swap_cols(off + 0, off + 2); break;
	case 2: board_swap_cols(off + 1, off + 2); break;
	}
}

void board_swap_rows_by_methods(int r0, int r1, int r2) {
	board_swap_rows_by_methods_offset(r0, 0);
	board_swap_rows_by_methods_offset(r1, 3);
	board_swap_rows_by_methods_offset(r2, 6);
}
void board_swap_cols_by_methods(int r0, int r1, int r2) {
	board_swap_cols_by_methods_offset(r0, 0);
	board_swap_cols_by_methods_offset(r1, 3);
	board_swap_cols_by_methods_offset(r2, 6);
}

void board_generate_numbers() {
	srand(time(NULL));
	memset(board_real, 0, BOARD_SIZE);
	mkboard_init_number_pool();

	char lineStartAt = (int)fmod(rand(), 9.0);

	for (int gen = 0; gen < 9; gen++) {
		int i = (int)fmod(gen + lineStartAt, 9);
		memcpy(board_real + (i * 9), mkboard_getline(gen), 9);
	}

	board_swap_rows_by_methods(rand(), rand(), rand());
	board_swap_cols_by_methods(rand(), rand(), rand());

	// check all
	for (int y = 0; y < 9; y++) {
		for (int x = 0; x < 9; x++) {
			char cc = board_real[BOARD_I(x, y)];
			if (! board_is_num_valid_here(cc, x, y, 1)) {
				println("Invalidity at [%i, %i] == %i", x,y,cc);
			}
		}
	}
}

void board_generate_mask() {
	int pos = 0;
	memset(board_mask, 1, BOARD_SIZE);
	for (sxi = 0; sxi < coveredNum; sxi++) {
		pos = (int)fmod(rand(), 9 * 9);
		while (!board_mask[pos]) {
			pos = (int)fmod(rand(), BOARD_SIZE);
		}
		board_mask[pos] = 0;
	}
}

void board_generator_thread(void* data) {
	isGenerating = 1;
	memset(board_real, 0, BOARD_SIZE);
	memset(board_disp, 0, BOARD_SIZE);
	memset(board_mask, 0, BOARD_SIZE);

	board_generate_numbers();
	board_generate_mask();

	int i;

	memcpy(board_disp, board_real, BOARD_SIZE);
	for (i = 0; i < BOARD_SIZE; i++) {
		if (!board_mask[i]) board_disp[i] = 0;
	}
	vterm_write_c(0, cheater_anchor);
	isGenerating = 0;
}

int board_check_all() {
	int retval = 1;
	int i;
	for (i = 0; i < BOARD_SIZE; i++) {
		retval = retval || board_disp[i] == board_real[i];
	}
	return retval;
}

void board_start() {
	isPaused = 0;
	isGenerating = 1;
	currentGameTime = 0.0;

#if WIN32
	CreateThread(NULL, 0, board_generator_thread, NULL, 0, NULL);
#endif
}

double dPauseTime = 0.0;

void board_update(double time) {
	if (isGenerating) 
	{
		vterm_write_c(12, boardGenerating1);
		vterm_write_c(13, boardGenerating2);
	}
	if (isPaused) {
		dPauseTime += time;
		vterm_write_c(13, boardPaused);
		if (fmod(dPauseTime, 2.0) > 1.0) {
			vterm_select(0, 13, TERM_W);
		}
		vterm_write(0, TERM_H - 2, boardPausedLegend1);
		vterm_write(0, TERM_H - 1, boardPausedLegend2);
	}
	else
	{
		currentGameTime += time;
		// Draw Board
		{
			for (sxi = 0; sxi < 13; sxi++) {
				bgLine = boardBackgroundTiles;
				if ((int)fmod(sxi, 4.0) == 0) {
					bgLine = boardBackgroundCross;
				}
				vterm_write_c(3 + sxi, bgLine);
			}

			int ltile = (TERM_W / 2) - 5;

			for (int y = 0; y < 9; y++) {
				for (int x = 0; x < 9; x++) {
					int dx = x, dy = y;
					sxi = (y * 9) + x;
					if (x >= 3) dx++;
					if (x >= 6) dx++;
					if (y >= 3) dy++;
					if (y >= 6) dy++;
					c = (isGenerating ? board_real : board_disp)[sxi];
					if (c > 0 && c <= 9) {
						c += '0';
					}
					else if (c == 0) {
						c = ' ';
					}
					else {
						c = '\x7F';
					}
					vterm_putchar(ltile + dx, 4 + dy, c);
					if (selectX == x && selectY == y) {
						vterm_select(ltile + dx, 4 + dy, 1);
					}
				}
			}
			vterm_write(0, TERM_H - 5, boardDisplayLegend1);
			vterm_write(0, TERM_H - 4, boardDisplayLegend2);
			vterm_write(0, TERM_H - 3, boardDisplayLegend3);
			vterm_write(0, TERM_H - 2, boardDisplayLegend4);
			vterm_write(0, TERM_H - 1, boardDisplayLegend5);
		}

		if (showTime) {
			int ss = (int)fmod(currentGameTime, 60);
			int mm = (int)fmod(floor(currentGameTime / 60.0), 60);
			int hh = (int)floor(currentGameTime / 3600.0);

			vterm_write_c(2, strformat(boardTimeFormat, hh, mm, ss));
		}
	}


	game_drawSceneName(scnNameBoard);
}
void board_end() {}

void board_key_u() {
	selectY = max(selectY - 1, 0);
}

void board_key_d() {
	selectY = min(selectY + 1, 8);
}
void board_key_l() {
	selectX = max(selectX - 1, 0);
}
void board_key_r() {
	selectX = min(selectX + 1, 8);
}

void board_check_isfinished() {
	if (memcmp(board_disp, board_real, BOARD_SIZE) == 0) {
		finishGameTime = currentGameTime;
		game_switch(SCN_GameEnd);
	}
}

void board_set_char(char c) {
	int i = BOARD_I(selectX, selectY);
	if (!board_mask[i]) {
		board_disp[i] = c;
	}
	board_check_isfinished();
}

void board_reveal() {
	memcpy(board_disp, board_real, BOARD_SIZE);
}

void board_key_single_check() {
	if (!isGenerating) {
		if (isPaused) {
			isPaused = 0;
		}
		else {

		}
	}
}

void board_on_escape_key() {
	if (!isGenerating) {
		if (isPaused) {
			game_switch(SCN_GameMenu);
		}
		else {
			dPauseTime = 0.5;
			isPaused = 1;
		}
	}
}

void board_kdn(int key) {
	switch (key) {
	case GLFW_KEY_UP:     board_key_u(); break;
	case GLFW_KEY_DOWN:   board_key_d(); break;
	case GLFW_KEY_LEFT:   board_key_l(); break;
	case GLFW_KEY_RIGHT:  board_key_r(); break;
	case GLFW_KEY_ENTER:  board_key_single_check(); break;
	case GLFW_KEY_ESCAPE: board_on_escape_key(); break;
	case GLFW_KEY_1 : case GLFW_KEY_KP_1: board_set_char(1); break;
	case GLFW_KEY_2 : case GLFW_KEY_KP_2: board_set_char(2); break;
	case GLFW_KEY_3 : case GLFW_KEY_KP_3: board_set_char(3); break;
	case GLFW_KEY_4 : case GLFW_KEY_KP_4: board_set_char(4); break;
	case GLFW_KEY_5 : case GLFW_KEY_KP_5: board_set_char(5); break;
	case GLFW_KEY_6 : case GLFW_KEY_KP_6: board_set_char(6); break;
	case GLFW_KEY_7 : case GLFW_KEY_KP_7: board_set_char(7); break;
	case GLFW_KEY_8 : case GLFW_KEY_KP_8: board_set_char(8); break;
	case GLFW_KEY_9 : case GLFW_KEY_KP_9: board_set_char(9); break;
	case GLFW_KEY_C : board_reveal(); break;
	}
}