#include "sudoku.h"

char termbuf[TERM_SZ];
char selebuf[TERM_SZ];
int winSizeX = 0, winSizeY = 0;
int selectX = 0, selectY = 0;
GLFWwindow* win = NULL;
enum GameScene activeScene = SCN_Null;
int coveredNum = 41, shouldShowHint;
int showTime = 1, showFPS = 1;
double finishGameTime = 0.0;