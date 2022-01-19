#include "../game_scenes.h"

int mmSelected = 0;
const char* actMainWindow;

void mmenu_start() {
	mmSelected = 0;
}
void mmenu_update(double time) {

	vterm_write(1, 4, menuOptionHiddenCount);
	actMainWindow = strformat(menuOptionSliderFormat, coveredNum);
	vterm_write(TERM_W - 1 - strlen(actMainWindow), 5, actMainWindow);

	vterm_write(1, 6, menuOptionShowHint);
	actMainWindow = strformat(menuOptionSliderStrFormat, shouldShowHint ? str_Circle : str_Cross);
	vterm_write(TERM_W - 1 - strlen(actMainWindow), 7, actMainWindow);

	vterm_write(1, 8, menuOptionShowTime);
	actMainWindow = strformat(menuOptionSliderStrFormat, showTime ? str_Circle : str_Cross);
	vterm_write(TERM_W - 1 - strlen(actMainWindow), 9, actMainWindow);

	vterm_write(1, 10, menuOptionShowFPS);
	actMainWindow = strformat(menuOptionSliderStrFormat, showFPS ? str_Circle : str_Cross);
	vterm_write(TERM_W - 1 - strlen(actMainWindow), 11, actMainWindow);

	vterm_write(1, 12, menuOptionPlay);
	vterm_write(TERM_W - 1 - strlen(menuOptionPlayDesc), 13, menuOptionPlayDesc);

	vterm_select(0, 4 + (mmSelected * 2) + 0, TERM_W);
	vterm_select(0, 4 + (mmSelected * 2) + 1, TERM_W);

	for (int i = 0; i < 4; i++) {
		vterm_write_c((TERM_H - 13) + i, menuWarningError[i]);
	}
	vterm_select(0, TERM_H - 13, TERM_W);

	vterm_write_c(TERM_H - 5, authorName);
	vterm_select(0, TERM_H - 5, TERM_W);
	vterm_write_l(TERM_H - 4, menuDisplayLegend1);
	vterm_write_l(TERM_H - 3, menuDisplayLegend2);
	vterm_write_l(TERM_H - 2, menuDisplayLegend3);
	vterm_write_l(TERM_H - 1, menuDisplayLegend4);

	game_drawSceneName(scnNameMenu);
}

void mmenu_end() {}

void selectMenuDelta(int num) {
	mmSelected += num;
	if (mmSelected < 0) {
		mmSelected = 4;
	}

	if (mmSelected > 4) {
		mmSelected = 0;
	}
}

void selectValueDelta(int num) {
	switch (mmSelected) {
	case 0:
		coveredNum = min(max(coveredNum + num, 5), 75);
		break;
	case 1:
		shouldShowHint = min(max(shouldShowHint + num, 0), 1);
		break;
	case 2:
		showTime = min(max(showTime + num, 0), 1);
		break;
	case 3:
		showFPS = min(max(showFPS + num, 0), 1);
		break;
	}
}

void selectMenuEnter() {
	switch (mmSelected) {
	case 1: shouldShowHint = !shouldShowHint; break;
	case 2: showTime = !showTime; break;
	case 3: showFPS = !showFPS; break;
	case 4: game_switch(SCN_Board); break;
	}
}

void mmenu_kdn(int key){
	switch (key) {
	case GLFW_KEY_UP:    selectMenuDelta(-1); break;
	case GLFW_KEY_DOWN:  selectMenuDelta(1); break;
	case GLFW_KEY_LEFT:  selectValueDelta(-1); break;
	case GLFW_KEY_RIGHT: selectValueDelta(1); break;
	case GLFW_KEY_ENTER: selectMenuEnter(); break;
	case GLFW_KEY_ESCAPE: glfwSetWindowShouldClose(win, 1); break;
	}
}