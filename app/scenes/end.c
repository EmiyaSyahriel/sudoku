#include "../game_scenes.h"
#include <math.h>
#include "../helper.h"

const char* fmt_end;
double currentEndTime = 0.0;

void gmend_start() {
	currentEndTime = 0.0;
}
void gmend_update(double time) {
	currentEndTime += time;
	vterm_write_c(5, scnNameEnd);
	vterm_select(0, 5, TERM_W);
	
	fmt_end = strformat(endScreenLevelFormat, (int)(min(currentEndTime, 1.0) * coveredNum));

	vterm_write(1, 7, endScreenLevelName);
	vterm_write(TERM_W - 1 - strlen(fmt_end), 7, fmt_end);

	if (showTime) {
		double fTime = (min(currentEndTime, 1.0) * finishGameTime);
		int ss = (int)fmod(fTime, 60);
		int mm = (int)fmod(floor(fTime / 60.0), 60);
		int hh = (int)floor(fTime / 3600.0);

		fmt_end = strformat(boardTimeFormat, hh,mm,ss);
		vterm_write(1, 8, endScreenTimeName);
		vterm_write(TERM_W - 1 - strlen(fmt_end), 8, fmt_end);
	}

	vterm_write_l(TERM_H - 1, endScreenLegend1);

	game_drawSceneName(scnNameEnd);
}
void gmend_end() {}
void gmend_kdn(int key) {
	if (key == GLFW_KEY_ENTER) {
		game_switch(SCN_GameMenu);
	}
}