#include "sudoku.h"
#include <stdarg.h>
#include <stdio.h>

#define PRINTLN_BUFSIZE 1024
#define _CRT_SECURE_NO_WARNINGS
 
char println_buffer[PRINTLN_BUFSIZE];
int println_size = PRINTLN_BUFSIZE;
char strformat_buffer[PRINTLN_BUFSIZE];
int strfmt_size = PRINTLN_BUFSIZE;

void alert(const char* title, const char* message) {
#ifdef WIN32
	MessageBox(0, message, title, MB_OK | MB_ICONASTERISK);
#endif
}

void println(const char* format, ...) {
	println_size = PRINTLN_BUFSIZE;
	va_list args;
	va_start(args, format);
	println_size = vsnprintf(println_buffer, println_size, format, args);
	if (println_size < PRINTLN_BUFSIZE + 1) {
		println_buffer[println_size + 1] = '\0';
	}
	va_end(args);
	printf("%s\n", println_buffer);
}

const char* strformat(const char* format, ...) {
	strfmt_size = PRINTLN_BUFSIZE;
	va_list args;
	va_start(args, format);
	strfmt_size = vsprintf(strformat_buffer, format, args);
	if (strfmt_size < PRINTLN_BUFSIZE + 1) {
		strformat_buffer[strfmt_size + 1] = '\0';
	}
	va_end(args);
	return strformat_buffer;
}

char strcut_buffer[PRINTLN_BUFSIZE];
int strcut_len = PRINTLN_BUFSIZE;

const char* strcut(const char* format, int len) {
	strcut_len = len < PRINTLN_BUFSIZE ? len : PRINTLN_BUFSIZE-1;
	strncpy(strcut_buffer, format, strcut_len);
	strcut_buffer[strcut_len] = '\0';
	return strcut_buffer;
}

void term_hide() {
#if WIN32
	HWND win = GetConsoleWindow();
	ShowWindow(win, 
#ifdef DEBUG
		SW_SHOW
#else
		SW_HIDE
#endif
	);
#endif
}