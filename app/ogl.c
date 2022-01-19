#include "sudoku.h"
#include <math.h>
#include <time.h>
#include <stdlib.h>

#ifndef M_PI
#define M_PI 3.14129047
#endif

int shv, shf, shp;
int tAscii;
int lastW, lastH;
int triNum = 0;
float vPosData[8], vUvData[8], vSelData[4];
int iDataBuffer[6] = {0,1,2,1,2,3};
double oglCurrentTime;

int attrvpos, attrvuv, attrvsel;
int unifca, unifcb;

void glerr_doCheck(const char* fileName, int line) {
	GLenum err = glGetError();
	if (err != GL_NO_ERROR) {
		println(glErrorFormat, err, fileName, line);
	}
}

int ogl_vData_x, ogl_vData_y, ogl_vData_i;

#ifdef DEBUG
#define CGL() glerr_doCheck(__FILE__, __LINE__)
#else
#define CGL()
#endif

void ogl_get_char_uv(char c, float *x1, float *y1, float *x2, float *y2) {
	float charW = 1.0f / 16;
	float charH = 1.0f / 6;

	char chp = (c < ' ' || c > 0x7F) ? 0x7F : c;
	if (c == '\0') chp = ' ';
	chp -= ' ';
	int chx = (int)fmod(chp, 16);
	int chy = (int)floor(chp / 16.0f);
	*x1 = chx * charW;
	*y1 = chy * charH;
	*x2 = (chx + 1) * charW;
	*y2 = (chy + 1) * charH;
}

void ogl_compile_shader() {
	shv = glCreateShader(GL_VERTEX_SHADER); CGL();
	shf = glCreateShader(GL_FRAGMENT_SHADER); CGL();
	shp = glCreateProgram(); CGL();
	glShaderSource(shv, 1, &shader_v, NULL); CGL();
	glShaderSource(shf, 1, &shader_f, NULL); CGL();
	glCompileShader(shv); CGL();
	glCompileShader(shf); CGL();
	glAttachShader(shp, shv); CGL();
	glAttachShader(shp, shf); CGL();
	glLinkProgram(shp); CGL();
	glUseProgram(shp); CGL();

	int inf = 0;
	glGetProgramiv(shp, GL_LINK_STATUS, &inf);
	if (inf != GL_TRUE) {
		int bSize = 512;
		int dSize = bSize;
		char infoLogBuff[512];
		glGetProgramInfoLog(shp, bSize, &dSize, &infoLogBuff);
		println(glShaderError, infoLogBuff);
	}
	else {
		println(glShaderCompiled);
		attrvpos = glGetAttribLocation(shp, glShpArg[0]);
		attrvuv =  glGetAttribLocation(shp, glShpArg[1]);
		attrvsel = glGetAttribLocation(shp, glShpArg[2]);
		unifca =   glGetUniformLocation(shp, glShpArg[3]);
		unifcb =   glGetUniformLocation(shp, glShpArg[4]);
	}
}

void ogl_load_texture() {
	glGenTextures(1, &tAscii);
	glBindTexture(GL_TEXTURE_2D, tAscii);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RED, 16 * 8, 6 * 8, 0, GL_RED, GL_UNSIGNED_BYTE, texture);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	println(textureLoadFinish);
}

void ogl_viewport() {
	if (lastW != winSizeX && lastH != winSizeY) {
		lastW = winSizeX;
		lastH = winSizeY;
		int minSz = min(lastW, lastH);
		glViewport(
			(lastW / 2) - (minSz / 2),
			(lastH / 2) - (minSz / 2),
			minSz,
			minSz
		);  CGL();
	}
}

void ogl_start() {
	glClearColor(0.6f, 0.0f, 1.0f, 1.0f); CGL();
	ogl_viewport(); CGL();
	ogl_compile_shader(); CGL();
	ogl_load_texture();
	// ogl_fill_vData_random();
}

int vSelNum = 0;
int vUvNum = 0;
int vPosNum = 0;
size_t fs = sizeof(float);
int hasPtrInit = 0;

void ogl_draw_vterm_chars() {
	float xGridSize = 2.0f / (TERM_W);
	float yGridSize = 2.0f / (TERM_H);
	int i = 0;
	float uv_x1, uv_y1, uv_x2, uv_y2;
	float x1, y1;
	float x2, y2;
	int iv = 0;
	if (!hasPtrInit) {
		glVertexAttribPointer(attrvpos, 2, GL_FLOAT, GL_FALSE, fs * 2, vPosData);
		glVertexAttribPointer(attrvuv, 2, GL_FLOAT, GL_FALSE, fs * 2, vUvData);
		glVertexAttribPointer(attrvsel, 1, GL_FLOAT, GL_FALSE, fs * 1, vSelData);
		hasPtrInit = 1;
	}
	for (int y = 0; y < TERM_H; y++) {
		for (int x = 0; x < TERM_W; x++) {
			int i = (y * TERM_W) + x;
			vPosNum = 0;
			vSelNum = 0;
			vUvNum = 0;
			char c = termbuf[i];

			ogl_get_char_uv(c, &uv_x1, &uv_y1, &uv_x2, &uv_y2);
			x1 = (xGridSize * (x + 0)) - 1.0f;
			x2 = (xGridSize * (x + 1)) - 1.0f;
			y1 = -(yGridSize * (y + 0)) + 1.0f;
			y2 = -(yGridSize * (y + 1)) + 1.0f;
			float selected = selebuf[i] != 0 ? 1.0f : 0.0f;

#ifndef put_vtx
#define put_vtx(x,y,u,v) {\
	vPosData[vPosNum + 0] = x;\
	vPosData[vPosNum + 1] = y;\
	vUvData[vUvNum + 0] = u;\
	vUvData[vUvNum + 1] = v;\
	vSelData[vSelNum] = selected;\
    vSelNum ++; vPosNum += 2; vUvNum += 2;\
}
#endif

			// Quad 1
			{
				put_vtx(x1, y1, uv_x1, uv_y1);
				put_vtx(x2, y1, uv_x2, uv_y1);
				put_vtx(x1, y2, uv_x1, uv_y2);
				put_vtx(x2, y2, uv_x2, uv_y2);
			}
			glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, iDataBuffer);
		}
	}
}

double lastCurrentTime = 0.0;

void ogl_draw(double dTime) {
	lastCurrentTime = 0.0;
	oglCurrentTime = dTime;
	ogl_viewport();
	glClearColor(0.0f, 0.0f, 0.0f, 0.5f); CGL();
	glClear(GL_COLOR_BUFFER_BIT);


	glUseProgram(shp); CGL();
	glUniform4f(unifca, 0.5f, 0.5f, 0.0f, 1.0f); CGL();
	glUniform4f(unifcb, 0.0f, 0.0f, 0.0f, 1.0f); CGL();

	glEnableVertexAttribArray(attrvpos); CGL();
	glEnableVertexAttribArray(attrvuv); CGL();
	glEnableVertexAttribArray(attrvsel); CGL();
	ogl_draw_vterm_chars(); CGL();
	glDisableVertexAttribArray(attrvpos); CGL();
	glDisableVertexAttribArray(attrvuv); CGL();
	glDisableVertexAttribArray(attrvsel); CGL();
}

void ogl_close() {
	glDeleteProgram(shp); CGL();
	glDeleteShader(shv); CGL();
	glDeleteShader(shf); CGL();
	glDeleteTextures(1, &tAscii); CGL();
}