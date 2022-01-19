#pragma once
#ifndef MINI_SUDOKU_SHARED_SOURCE
#define MINI_SUDOKU_SHARED_SOURCE

#if !defined(unix) && !defined(GLEW_STATIC)
#define GLEW_STATIC
#endif

#pragma warning(disable:4996)
#pragma warning(disable:4005)

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "strings.h"

#if WIN32
#include <Windows.h>
#endif

#define TERM_W 32
#define TERM_H 32
#define TERM_SZ TERM_W * TERM_H

enum GameScene {
	SCN_Null,
	SCN_Splash,
	SCN_GameMenu,
	SCN_Board,
	SCN_GameEnd
};

extern char termbuf[TERM_SZ];
extern char selebuf[TERM_SZ];
extern char* texture, *shader_f, *shader_v;
extern int winSizeX, winSizeY;
extern int selectX, selectY;
extern double finishGameTime;
extern int coveredNum, shouldShowHint;
extern int showTime, showFPS;
extern enum GameScene activeScene;
extern GLFWwindow* win;

void println(const char* format, ...);
void alert(const char* title, const char* message);

const char* strformat(const char* format, ...);
const char* strcut(const char* format, int len);

const char* _sudoku_argval(int count, ...);
int _sudoku_hasarg(int count, ...);
void _sudoku_putarg(int argc, const char** argv);

void vterm_clear();
void vterm_write(int x, int y, const char* txt);
void vterm_write_l(int y, const char* txt);
void vterm_write_r(int y, const char* txt);
void vterm_write_c(int y, const char* txt);
void vterm_select(int x, int y, int w);
void vterm_putchar(int x, int y, char c);

void ogl_start();
void ogl_draw(double dTime);
void ogl_close();

void game_start();
void game_end();
void game_update();
void game_switch(enum GameScene scene);
void game_keydown(int keycode);
void game_drawSceneName(const char* chr);

void term_hide();

#endif