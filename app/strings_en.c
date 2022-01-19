#ifdef GAME_LANGUAGE_EN
#include "strings.h"

/**
*
* Symbols is actually a normal ASCII character, it's just textured that way
* Left Arrow   : '{'
* Right Arrow  : '}'
* Up Arrow     : '^'
* Down Arrow   : '~'
* Enter Symbol : '`'
*
*/

const char* windowName = "C Sudoku";
const char* authorName = "EmiyaSyahriel";
const char* errGLFWInit = "Failed to load GLFW, required to create OpenGL Context";
const char* errGLEWInit = "Failed to load GLEW, required to load OpenGL functions";
const char* glStartupLog = "OpenGL v%s, on hardware : %s";
const char* logArgval = "Argval argument is given...";
const char* errTitle = "Error";
const char* str_OK = "OK";
const char* str_Yes = "Yes";
const char* str_No = "No";
const char* str_Circle = "O";
const char* str_Cross = "X";
const char* arg_run = "--run";
const char* arg_OK = "__ok";
const char* glErrorFormat = "OpenGL Error 0x%08x pada %s:%i";
const char* glShaderError = "OpenGL Shader Error : %s";
const char* glShaderCompiled = "OpenGL Shader compiled.";

const char* glShpArg[5] = { "v_vpos","v_uv","v_sel","color_a","color_b" };
const char* textureLoadFinish = "OpenGL Texture loaded.";
const char* bufferGenFinish = "OpenGL Buffer generated.";
const char* gmFPS = "FPS: %i";

const char* splExit = "[Esc] Quit";
const char* splEnter = "[`] Skip";
const char* splashName = "Sudoku - in C and OpenGL";
const char* splRdmText[10] = {
	"8 bit? what about 1? :)",
	"Crappier than Bebas Berapi!",
	"C is simply difficult :')",
	"OpenGL is 3D! not cmD!",
	"Uses OpenGL btw, not cmd",

	"Is Watatsumi = Toba Lake?",
	"github.com/EmiyaSyahriel/sudoku",
	"Source code freely accessible!",
	"Source code freely modifiable!",
	"Can a game be a NFT?"
};

const char* scnNameSplash = "A title screen, ICYDK..";
const char* scnNameMenu = "C Sudoku";
const char* scnNameBoard = "Game Board";
const char* scnNameEnd = "Game Finished";

const char* menuOptionSliderFormat = "{ %2i }";
const char* menuOptionSliderStrFormat = "{ %s }";
const char* menuOptionHiddenCount = "Covered Tile Count";
const char* menuOptionShowHint = "Allow Hints";
const char* menuOptionShowFPS = "Show FPS";
const char* menuOptionShowTime = "Show Time";
const char* menuOptionPlay = "Play";
const char* menuOptionPlayDesc = "Make sure your brain ready! }";
const char* menuDisplayLegend1 = "[^] [~] Change Option";
const char* menuDisplayLegend2 = "[{] [}] Change Value";
const char* menuDisplayLegend3 = "  [`]   Choose Option";
const char* menuDisplayLegend4 = " [Esc]  Quit";
const char* menuWarningError[4] = {
	//12345678901234567890123456789012
	 "INFO: ",
	 "Generator algorithm is still",
	 "too simple, pattern is visible",
	 "and can be easily finished."
};

const char* boardBackgroundCross = "+---+---+---+";
const char* boardBackgroundTiles = "|   |   |   |";
const char* boardGenerating1 = "Please wait! Generating";
const char* boardGenerating2 = "game board...";
const char* boardErrorVertical = "Look up/down, maybe?";
const char* boardErrorHorizontal = "Look left/right, maybe?";
const char* boardErrorBlock = "Look around, maybe?";
const char* boardDisplayLegend1 = "[1-9]  Put Number";
const char* boardDisplayLegend2 = " [0]   Clear";
const char* boardDisplayLegend3 = "[{}^~] Move Cursor";
const char* boardDisplayLegend4 = "[C] Check All | [`] Check One";
const char* boardDisplayLegend5 = "[Esc] Pause Game";
const char* boardTimeFormat = "%02i:%02i:%02i";
const char* boardPaused = "[Game Paused]";
const char* boardPausedLegend1 = "[Esc] Quit";
const char* boardPausedLegend2 = "[`] Continue";

const char* endScreenLevelName = "Covered Tile Count";
const char* endScreenLevelFormat = "%i";
const char* endScreenTimeName = "Finished in";
const char* endScreenTimeFormat = "%02i:%02i:%02i";
const char* endScreenLegend1 = "[`] Back to menu";

#endif