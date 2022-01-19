#include "game_scenes.h"

char original_board[9 * 9];
char view_board[9 * 9];
double gmCurrentTime = 0.0;
double gmLastCTime = 0.0;
double fps;
double deltaTime;
size_t authSLen = 7;

void game_start() {
	gmCurrentTime = 0.0f;
	authSLen = strlen(authorName);
}

void game_end() {

}

void game_update(double time) {
	gmLastCTime = gmCurrentTime;
	gmCurrentTime = time;
	deltaTime = gmCurrentTime - gmLastCTime;
	fps = 1.0 / deltaTime;

	switch (activeScene)
	{
		case SCN_Splash:   splsh_update(deltaTime); break;
		case SCN_GameMenu: mmenu_update(deltaTime); break;
		case SCN_Board:    board_update(deltaTime); break;
		case SCN_GameEnd:  gmend_update(deltaTime); break;
	}
	if (showFPS) {
		vterm_write(0, 0, strformat(gmFPS, (int)fps));
		vterm_select(0, 0, 7);
	}
}

void game_switch(enum GameScene scene) {
	switch (activeScene) 
	{
		case SCN_Splash:   splsh_end(); break;
		case SCN_GameMenu: mmenu_end(); break;
		case SCN_Board:    board_end(); break;
		case SCN_GameEnd:  gmend_end(); break;
	}
	activeScene = scene;
	switch (activeScene) 
	{
		case SCN_Splash:   splsh_start(); break;
		case SCN_GameMenu: mmenu_start(); break;
		case SCN_Board:    board_start(); break;
		case SCN_GameEnd:  gmend_start(); break;
	}
}

int gameWinPosX, gameWinPosY;
int gameWinSzX,  gameWinSzY;

void game_switchfullscreen() {
	int bIsFullScreen = glfwGetWindowMonitor(win) == NULL;

	if (bIsFullScreen) {
		glfwGetWindowPos(win, &gameWinPosX, &gameWinPosY);
		glfwGetWindowSize(win, &gameWinSzX, &gameWinSzY);
		GLFWmonitor* monitor = glfwGetPrimaryMonitor();
		GLFWvidmode* mode = glfwGetVideoMode(monitor);
		glfwSetWindowMonitor(win, monitor, 0, 0, mode->width, mode->height, mode->refreshRate);
	}
	else {
		glfwSetWindowMonitor(win, NULL, gameWinPosX, gameWinPosY, gameWinSzX, gameWinSzY, 0);
	}
}

void game_keydown(int keycode) {
	if (keycode == GLFW_KEY_F11) {
		game_switchfullscreen();
	}
	else {
		switch (activeScene)
		{
		case SCN_Splash:   splsh_kdn(keycode); break;
		case SCN_GameMenu: mmenu_kdn(keycode); break;
		case SCN_Board:    board_kdn(keycode); break;
		case SCN_GameEnd:  gmend_kdn(keycode); break;
		}
	}
}

void game_drawSceneName(const char* chr) {
	vterm_write_r(0, chr);
	vterm_select(TERM_W - (int)strlen(chr), 0, (int)strlen(chr));
}