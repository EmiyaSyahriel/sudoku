#include "sudoku.h"
#include <stdarg.h>
#include <string.h>
#include <malloc.h>

const char** _sudoku_argv;
int _sudoku_argc;

#define ARGC _sudoku_argc
#define ARGV _sudoku_argv

const char** va_toarr(int count, va_list args) {
	const char** retval = (const char**)malloc(count * sizeof(char*));
	for (int i = 0; i < count; i++) {
		retval[i] = va_arg(args, const char*);
	}
	return retval;
}

const char* _sudoku_argval(int count, ...) {
	va_list argtemp; va_start(argtemp, count);
	const char** args = va_toarr(count, argtemp);
	va_end(argtemp);
	
	for (int i = 0; i < ARGC; i++) {
		for (int j = 0; j < count; j++) {
			if (_stricmp(args[j], ARGV[i]) == 0 && (i + 1 < ARGC)) {
				return ARGV[i+1];
			}
		}
	}
	
	free(args);
	return NULL;
}

int _sudoku_hasarg(int count, ...) {
	va_list argtemp; va_start(argtemp, count);
	const char** args = va_toarr(count, argtemp);
	va_end(argtemp);
	for (int i = 0; i < ARGC; i++) {
		for (int j = 0; j < count; j++) {
			if (_stricmp(args[j],ARGV[i]) == 0) {
				return 1;
			}
		}
	}
	free(args);
	return 0;
}

void _sudoku_putarg(int argc, const char** argv)
{
	ARGC = argc;
	ARGV = argv;
}
