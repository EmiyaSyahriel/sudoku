#include "mkboard.h"
#include <string.h>
#include <stdlib.h>
#include <math.h>

char sudoku_rnum_gen() {
	char rtv = (char)(1.0 + fmod(rand(), 9.0));
	return rtv;
}
#define SUDOKU_RNUM sudoku_rnum_gen() 

char linebuffer[9];
int linebuffer_movement = 0, linebuffer_move_step = 0;

int mkboard_line_has_duplicate(char c) {
	for (int i = 0; i < 9; i++) {
		if (linebuffer[i] == c) return 1;
	}
	return 0;
}

void mkboard_init_number_pool() {
	memset(linebuffer, 0, 9);
	srand(time(NULL));
	
	linebuffer_movement = (int)fmod(rand(), 1.0);
	linebuffer_move_step = 1 + (int)fmod(rand(), 1.0);

	char c;
	for (int i = 0; i < 9; i++) {
		c = SUDOKU_RNUM;
		while (mkboard_line_has_duplicate(c)) {
			c = SUDOKU_RNUM;
		}
		linebuffer[i] = c;
	}
}

char mvbuff[9];

void mkboard_pool_shl(int count) {
	memcpy(mvbuff, linebuffer, 9);
	for (int i = 0; i < 9; i++) {
		int ii = (int)fmod((9 - count) + i, 9.0);
		linebuffer[ii] = mvbuff[i];
	}
}

void mkboard_pool_shr(int count) {
	memcpy(mvbuff, linebuffer, 9);
	for (int i = 0; i < 9; i++) {
		int ii = (int)fmod(count + i, 9.0);
		linebuffer[ii] = mvbuff[i];
	}
}

void mkboard_pool_swap(int from, int to) {
	char a = linebuffer[from];
	char b = linebuffer[to];
	linebuffer[from] = b;
	linebuffer[to] = a;
}

char* mkboard_getline(int generation) {
	if (linebuffer_movement) {
		mkboard_pool_shl(linebuffer_move_step * 3);
	}else
	{
		mkboard_pool_shr(linebuffer_move_step * 3);
	}
	if (generation == 3 || generation == 6) {
		mkboard_pool_swap(0, 1);
		mkboard_pool_swap(1, 2);

		mkboard_pool_swap(3, 4);
		mkboard_pool_swap(4, 5);

		mkboard_pool_swap(6, 7);
		mkboard_pool_swap(7, 8);
	}
	return linebuffer;
}