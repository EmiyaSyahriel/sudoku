#include <math.h>
#include "../game_scenes.h"
#include "../helper.h"

double cTime = 0.0;
size_t splEnterLen;
int splDisplaySelect;
int termCenter = TERM_W / 2;
size_t displayLen = 0;
const char* splDspText;
extern int authSLen;
int wRandomSelect;
const char* wRandomText;

void splsh_start() {
	cTime = 0.0;
	srand(time(NULL));
	wRandomSelect = (int)fmod(rand(), 10);
	splEnterLen = strlen(splEnter);
}

void splsh_update(double time) {
	cTime += time;

	if (cTime > 0.5 && cTime < 1.0) {
		displayLen = (int)(ilerp(0.5, 1.0, cTime)* strlen(splashName));
	}
	else if (cTime > 1.0 && cTime < 3.0) {
		displayLen = strlen(splashName);
	}
	else if (cTime > 3.0 && cTime < 3.5) {
		displayLen = (int)(ilerp(3.5, 3.0, cTime) * strlen(splashName));
	}
	else if(cTime > 3.5) {
		game_switch(SCN_GameMenu);
	}

	splDisplaySelect = fmod(cTime, 0.5) > 0.25;
	splEnterLen = strlen(splEnter);

	splDspText = strcut(splashName, displayLen);

	vterm_write(termCenter - (displayLen / 2), 12, splDspText);
	if (!splDisplaySelect) {
		vterm_select(termCenter - (displayLen / 2), 12, displayLen);
	}

	wRandomText = splRdmText[wRandomSelect];

	if (wRandomText != NULL) {
		vterm_write_c(15, wRandomText);
	}
	
	vterm_write_c(TERM_H - 5, authorName);
	vterm_select(0, TERM_H - 5, TERM_W);

	vterm_write(0, TERM_H-1, splEnter);
	vterm_write(0, TERM_H-2, splExit);
	game_drawSceneName(scnNameSplash);
}

void splsh_end() {
	cTime = 0.0;
}

void splsh_kdn(int key) {
	switch (key) {
	case GLFW_KEY_SPACE:
	case GLFW_KEY_ENTER:
		game_switch(SCN_GameMenu);
		break;
	case GLFW_KEY_ESCAPE:
		glfwSetWindowShouldClose(win, 1);
		break;
	}
}