#include "sudoku.h"
#include <stdio.h>

GLenum initCode;
int i;
double glTime;

void window_keycode_callback(GLFWwindow* window, int key, int scancode, int action, int mods) {
	if(action == GLFW_PRESS || action == GLFW_REPEAT) game_keydown(key);
}

int main(int argc, char** argv) {
	term_hide();
	_sudoku_putarg(argc, argv);
	if (_sudoku_argval (1, str_OK) == arg_OK || _sudoku_hasarg(1, arg_run)) {
		println(logArgval);
	}

	println("Binary pointer size : %i", sizeof(void*));

	i = glfwInit();
	if (i != GL_TRUE) return 0;
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
	glfwWindowHint(GLFW_TRANSPARENT_FRAMEBUFFER, GLFW_TRUE);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_COMPAT_PROFILE);
#if WIN32
	//glfwSetWindowIcon()
#endif

	win = glfwCreateWindow(512, 512, windowName, NULL, NULL);

	if (win == NULL) {
		println(errGLFWInit);
		alert(errTitle, errGLFWInit);
		return 0;
	}

	glfwMakeContextCurrent(win);
	initCode = glewInit();
	if (initCode != GLEW_OK) {
		println(errGLEWInit);
		alert(errTitle, errGLEWInit);
		return 0;
	}

	println(glStartupLog, glGetString(GL_VERSION), glGetString(GL_RENDERER));

	game_start();
	ogl_start();
	game_switch(SCN_Splash);
	glfwSetWindowAspectRatio(win, 1, 1);

	glfwSetKeyCallback(win, window_keycode_callback);
	while (!glfwWindowShouldClose(win)) {
		vterm_clear();
		glfwGetWindowSize(win, &winSizeX, &winSizeY);
		glTime = glfwGetTime();
		game_update(glTime);
		ogl_draw(glTime);
		glfwSwapBuffers(win);
		glfwPollEvents();
	}
	game_end();
	ogl_close();	
	glfwTerminate();

	return 0;
}