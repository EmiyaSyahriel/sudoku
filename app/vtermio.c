#include "sudoku.h"
// #include <malloc.h>
#include <string.h>

int i = 0;
size_t clen = 0;


void vterm_clear() {
	memset(termbuf, 0, TERM_SZ);
	memset(selebuf, 0, TERM_SZ);
}

#define CURSOR_I ((y * TERM_W) + x)

void vterm_write(int x, int y, const char* txt) {
	i = CURSOR_I;
	clen = strlen(txt);
	if (i + clen <= TERM_SZ) {
		memcpy(termbuf + i, txt, clen);
	}
}

void vterm_write_l(int y, const char* txt) {
	vterm_write(0, y, txt);
}

void vterm_write_c(int y, const char* txt) {
	vterm_write((TERM_W / 2) - (strlen(txt) / 2), y, txt);
}

void vterm_write_r(int y, const char* txt) {
	vterm_write(TERM_W - strlen(txt), y, txt);
}

void vterm_select(int x, int y, int w) {
	i = CURSOR_I;
	if (i + w <= TERM_SZ) {
		memset(selebuf + i, 1, w);
	}
}

void vterm_putchar(int x, int y, char c) {
	i = CURSOR_I;
	termbuf[i] = c;
}