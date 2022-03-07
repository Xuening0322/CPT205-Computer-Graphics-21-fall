//////////////////////////////////////////
//										//
//	CPT205 Assignment 1					//
//	Xuening Wang						//
//	1929720								//
//										//
//////////////////////////////////////////

#define FREEGLUT_STATIC
#include <GL/freeglut.h>
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <math.h>
#include <windows.h>
#define MAX_CHAR       128

typedef struct { GLfloat x, y; } point;
point p0 = { 0, -1 };
const int Width = 600;
const int Height = 600;
const GLfloat PI = 3.141592653f;

int time_interval = 16;
int wordFlag = 0;
GLfloat step1 = 0.0;
GLfloat step2 = 6;
GLfloat wordx = 300;
GLfloat wordy = 0;

float h = 0.0f;
float m = 0.0f;
float s = 0.0f;


void timerFunc(int value)
{
	s += 1;
	int carry1 = 0;
	if (s >= 60)
	{
		s = 0;
		carry1 = 1;
	}
	m += carry1;
	int carry2 = 0;
	if (m >= 60)
	{
		m = 0;
		carry2 = 1;
	}
	h += carry2;
	if (h >= 24)
		h = 0;

	glutPostRedisplay();
	glutTimerFunc(1000, timerFunc, 1); // Execute every second for 1000 times
}

void OnTimer1(int value) {
	wordy += step1;
	if (wordy >= 900)
	{
		step1 = 0;
		wordy = 925;
	}

	glutTimerFunc(time_interval, OnTimer1, 1);
}

void OnTimer2(int value)
{
	p0.x += step2;
	if (p0.x >= 1000)
		p0.x = 0;
	else if (p0.x <= 0)
		p0.x = 999;
	//when_in_mainloop();
	glutTimerFunc(time_interval, OnTimer2, 1);
}

void keyboard_input(unsigned char key, int x, int y) {// keyboard interaction
	if (key == 'q' || key == 'Q') {
		exit(0);
	}
	else if (key == 'f' || key == 'F') // change direction of movement
	{
		step2 = -step2;
	}
	else if (key == 's' || key == 'S') // stop
	{
		step2 = 0;
	}
	else if (key == 'r' || key == 'R') // set step
	{
		step2 = 10;
	}
	else if (key == 'a' || key == 'A') // decrease step
	{
		step2 -= 1;
	}
	else if (key == 'd' || key == 'D') // increase step
	{
		step2 += 1;
	}
}

void mouse_input(int button, int state, int x, int y) { // mouse interaction
	if (state == GLUT_DOWN && button == GLUT_LEFT_BUTTON && wordy <= 530)
		wordFlag = 1;
	step1 = 4.0;
}

void SetupRC(void)
{
	// Get local time
	SYSTEMTIME sys;
	GetLocalTime(&sys);
	h = sys.wHour;
	m = sys.wMinute;
	s = sys.wSecond;
}

// For drawing the strings
void drawString(const char* str) {
	static int isFirstCall = 1;
	static GLuint lists;
	if (isFirstCall) {
		isFirstCall = 0;
		lists = glGenLists(MAX_CHAR);
		wglUseFontBitmaps(wglGetCurrentDC(), 0, MAX_CHAR, lists);
	}
	for (; *str != '\0'; ++str) {
		glCallList(lists + *str);
	}
}

void selectFont(int size, int charset, const char* face) {
	HFONT hFont = CreateFontA(size, 0, 0, 0, FW_MEDIUM, 0, 0, 0, charset, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_SWISS, face);
	HFONT hOldFont = (HFONT)SelectObject(wglGetCurrentDC(), hFont);
	DeleteObject(hOldFont);
}

void drawBackground() {
	glBegin(GL_POLYGON);
	glColor3ub(75, 8, 138);
	glVertex2d(0, 0);
	glColor3ub(136, 63, 138);
	glVertex2d(1100, 0);
	glColor3ub(136, 63, 138);
	glVertex2d(1100, 740);
	glColor3ub(75, 8, 138);
	glVertex2d(0, 740);
	glEnd();
}

void drawBar() {

	glBegin(GL_POLYGON);
	glColor3ub(47, 11, 58);
	glVertex2d(0, 730);
	glColor3ub(75, 8, 138);
	glVertex2d(1100, 730);
	glColor3ub(75, 8, 138);
	glVertex2d(1100, 690);
	glColor3ub(47, 11, 58);
	glVertex2d(0, 690);
	glEnd();
}

void drawClock() {

	int cx = Width / 2; // Center of the circle
	int cy = Height / 2;
	int R = 100; // Radius
	int n = 100;
	int i;

	glBegin(GL_LINE_LOOP);
	for (i = 0; i < n; i++)
	{
		glVertex2f(cx + (R + 2) * cos(2 * PI / n * i), cy + (R + 2) * sin(2 * PI / n * i));
	}
	glEnd();

	glBegin(GL_LINE_LOOP);
	for (i = 0; i < n; i++)
	{
		glVertex2f(cx + (R + 5) * cos(2 * PI / n * i), cy + (R + 5) * sin(2 * PI / n * i));
	}
	glEnd();


	// Draw the clock 
	int lines = 60;
	float ship1 = 10;
	float ship2 = 5;
	for (i = 0; i < lines; i++)
	{
		if (i % 5 == 0)
		{
			glLineWidth(3);
			glBegin(GL_LINES);
			glVertex2f(cx + (R - ship1) * sin(2 * PI / lines * i), cy + (R - ship1) * cos(2 * PI / lines * i));
			glVertex2f(cx + R * sin(2 * PI / lines * i), cy + R * cos(2 * PI / lines * i));
			glEnd();
		}
		else
		{
			glLineWidth(1);
			glBegin(GL_LINES);
			glVertex2f(cx + (R - ship2) * sin(2 * PI / lines * i), cy + (R - ship2) * cos(2 * PI / lines * i));
			glVertex2f(cx + R * sin(2 * PI / lines * i), cy + R * cos(2 * PI / lines * i));
			glEnd();
		}
	}

	// Draw the centric point
	glBegin(GL_POLYGON);
	for (i = 0; i < n; ++i)
		glVertex2i(cx + 5 * cos(2 * PI / n * i), cy + 5 * sin(2 * PI / n * i));
	glEnd();

	// Draw hour/minute/second hand
	int h_len = R - 3 * ship1;
	int m_len = R - ship1;
	int s_len = R - ship1 + 2 * ship1;

	float s_Angle = s / 60.0;
	float m_Angle = (m * 60 + s) / 3600.0;
	float h2 = h >= 12 ? (h - 12) : h;
	float h_Angle = (h2 * 60 * 60 + m * 60 + s) / (12 * 60 * 60);

	glLineWidth(0.5f); // Second
	glBegin(GL_LINES);
	glVertex2f(cx - 2 * ship1 * sin(2 * PI * s_Angle), cy - 2 * ship1 * cos(2 * PI * s_Angle));
	glVertex2f(cx + (R - ship2) * sin(2 * PI * s_Angle), cy + (R - ship2) * cos(2 * PI * s_Angle));
	glEnd();

	glLineWidth(3); // Hour
	glBegin(GL_LINES);
	glVertex2f(cx, cy);
	glVertex2f(cx + h_len * sin(2 * PI * h_Angle), cy + h_len * cos(2 * PI * h_Angle));
	glEnd();

	glLineWidth(1); // Minute
	glBegin(GL_LINES);
	glVertex2f(cx, cy);
	glVertex2f(cx + m_len * sin(2 * PI * m_Angle), cy + m_len * cos(2 * PI * m_Angle));
	glEnd();
}

// Divide the irregular figure into several triangles or polygons
void drawCB() {

	// A
	glColor3ub(170, 170, 170);
	glBegin(GL_POLYGON);
	glVertex2d(410, 182);
	glVertex2d(415, 401);
	glVertex2d(611, 492);
	glVertex2d(604, 321);
	glEnd();

	// B
	glColor3ub(120, 120, 120);
	glBegin(GL_POLYGON);
	glVertex2d(410, 182);
	glVertex2d(415, 401);
	glVertex2d(324, 488);
	glVertex2d(218, 387);
	glVertex2d(218, 316);
	glEnd();

	//C
	glColor3ub(120, 120, 120);
	glBegin(GL_POLYGON);
	glVertex2d(218, 387);
	glVertex2d(324, 488);
	glVertex2d(144, 558);
	glVertex2d(193, 400);
	glEnd();

	//D
	glColor3ub(120, 120, 120);
	glBegin(GL_POLYGON);
	glVertex2d(107, 396);
	glVertex2d(179, 344);
	glVertex2d(193, 400);
	glVertex2d(144, 558);
	glVertex2d(107, 558);
	glEnd();

	// E
	glColor3ub(190, 77, 48);
	glBegin(GL_POLYGON);
	glVertex2d(179, 344);
	glVertex2d(204, 349);
	glVertex2d(218, 387);
	glVertex2d(193, 400);
	glEnd();

	// F
	glColor3ub(48, 113, 157);
	glBegin(GL_TRIANGLES);
	glVertex2d(204, 349);
	glVertex2d(218, 344);
	glVertex2d(218, 387);
	glEnd();

	// G
	glColor3ub(120, 120, 120);
	glBegin(GL_POLYGON);
	glVertex2d(107, 558);
	glVertex2d(144, 558);
	glVertex2d(144, 743);
	glVertex2d(107, 742);
	glEnd();

	// H
	glColor3ub(120, 120, 120);
	glBegin(GL_POLYGON);
	glVertex2d(142, 622);
	glVertex2d(167, 614);
	glVertex2d(242, 562);
	glVertex2d(416, 506);
	glVertex2d(421, 758);
	glVertex2d(144, 743);
	glEnd();

	// I
	glColor3ub(170, 170, 170);
	glBegin(GL_POLYGON);
	glVertex2d(416, 506);
	glVertex2d(595, 569);
	glVertex2d(732, 692);
	glVertex2d(734, 751);
	glVertex2d(421, 758);
	glEnd();

	// J
	glColor3ub(170, 170, 170);
	glBegin(GL_POLYGON);
	glVertex2d(664, 364);
	glVertex2d(720, 407);
	glVertex2d(730, 624);
	glVertex2d(699, 624);
	glEnd();

	// K
	glColor3ub(190, 77, 48);
	glBegin(GL_POLYGON);
	glVertex2d(640, 366);
	glVertex2d(664, 364);
	glVertex2d(699, 624);
	glVertex2d(682, 619);
	glEnd();

	// L
	glColor3ub(190, 77, 48);
	glBegin(GL_POLYGON);
	glVertex2d(611, 492);
	glVertex2d(592, 512);
	glVertex2d(416, 432);
	glVertex2d(415, 401);
	glEnd();

	// M
	glColor3ub(190, 77, 48);
	glBegin(GL_POLYGON);
	glVertex2d(415, 401);
	glVertex2d(416, 432);
	glVertex2d(346, 502);
	glVertex2d(324, 488);
	glEnd();

	// N
	glColor3ub(190, 77, 48);
	glBegin(GL_POLYGON);
	glVertex2d(346, 502);
	glVertex2d(167, 572);
	glVertex2d(144, 558);
	glVertex2d(324, 488);
	glEnd();

	// O
	glColor3ub(190, 77, 48);
	glBegin(GL_POLYGON);
	glVertex2d(144, 558);
	glVertex2d(167, 572);
	glVertex2d(167, 614);
	glVertex2d(144, 622);
	glEnd();

	// P
	glColor3ub(48, 113, 157);
	glBegin(GL_TRIANGLES);
	glVertex2d(167, 572);
	glVertex2d(167, 614);
	glVertex2d(242, 562);
	glEnd();

	// Q
	glColor3ub(48, 113, 157);
	glBegin(GL_POLYGON);
	glVertex2d(242, 562);
	glVertex2d(167, 572);
	glVertex2d(346, 502);
	glVertex2d(416, 506);
	glEnd();

	// R
	glColor3ub(48, 113, 157);
	glBegin(GL_TRIANGLES);
	glVertex2d(346, 502);
	glVertex2d(416, 432);
	glVertex2d(416, 506);
	glEnd();

	// S
	glColor3ub(48, 113, 157);
	glBegin(GL_POLYGON);
	glVertex2d(416, 432);
	glVertex2d(592, 512);
	glVertex2d(595, 569);
	glVertex2d(416, 506);
	glEnd();

	// T
	glColor3ub(48, 113, 157);
	glBegin(GL_POLYGON);
	glVertex2d(592, 512);
	glVertex2d(611, 492);
	glVertex2d(682, 619);
	glVertex2d(682, 649);
	glVertex2d(595, 569);
	glEnd();

	// U
	glColor3ub(48, 113, 157);
	glBegin(GL_POLYGON);
	glVertex2d(640, 366);
	glVertex2d(682, 619);
	glVertex2d(611, 492);
	glVertex2d(604, 343);
	glEnd();

	// W
	glColor3ub(48, 113, 157);
	glBegin(GL_POLYGON);
	glVertex2d(682, 619);
	glVertex2d(723, 623);
	glVertex2d(725, 685);
	glVertex2d(682, 649);
	glEnd();
}

void drawLiv() {

	glColor3f(0, 0, 0);
	glBegin(GL_LINES);
	glVertex2d(104, 88);
	glVertex2d(104, 144);
	glEnd();

	glColor3ub(120, 120, 120);
	glBegin(GL_TRIANGLES);
	glVertex2d(104, 114);
	glVertex2d(132, 188);
	glVertex2d(76, 188);
	glEnd();

	glColor3ub(170, 170, 170);
	glBegin(GL_POLYGON);
	glVertex2d(84, 188);
	glVertex2d(124, 188);
	glVertex2d(124, 224);
	glVertex2d(84, 224);
	glEnd();

	glColor3ub(136, 34, 34);
	glBegin(GL_POLYGON);
	glVertex2d(68, 224);
	glVertex2d(140, 224);
	glVertex2d(140, 300);
	glVertex2d(68, 300);
	glEnd();

	glColor3ub(143, 62, 62);
	glBegin(GL_POLYGON);
	glVertex2d(140, 224);
	glVertex2d(160, 224);
	glVertex2d(160, 300);
	glVertex2d(140, 300);
	glEnd();

	glColor3ub(120, 120, 120);
	glBegin(GL_TRIANGLES);
	glVertex2d(140, 224);
	glVertex2d(160, 224);
	glVertex2d(150, 168);
	glEnd();

	glColor3ub(136, 34, 34);
	glBegin(GL_POLYGON);
	glVertex2d(68, 300);
	glVertex2d(160, 300);
	glVertex2d(160, 600);
	glVertex2d(68, 600);
	glEnd();

	glColor3ub(143, 62, 62);
	glBegin(GL_POLYGON);
	glVertex2d(80, 560);
	glVertex2d(148, 560);
	glVertex2d(148, 600);
	glVertex2d(80, 600);
	glEnd();

	glColor3ub(143, 62, 62);
	glBegin(GL_POLYGON);
	glVertex2d(90, 530);
	glVertex2d(138, 530);
	glVertex2d(148, 560);
	glVertex2d(80, 560);
	glEnd();

	glColor3ub(143, 62, 62);
	glBegin(GL_POLYGON);
	glVertex2d(90, 530);
	glVertex2d(90, 480);
	glVertex2d(138, 480);
	glVertex2d(138, 530);
	glEnd();

	glColor3ub(143, 62, 62);
	glBegin(GL_POLYGON);
	glVertex2d(90, 480);
	glVertex2d(100, 450);
	glVertex2d(128, 450);
	glVertex2d(138, 480);
	glEnd();

	glColor3ub(136, 34, 34);
	glBegin(GL_POLYGON);
	glVertex2d(160, 370);
	glVertex2d(300, 370);
	glVertex2d(300, 600);
	glVertex2d(160, 600);
	glEnd();

	glColor3ub(143, 62, 62);
	glBegin(GL_POLYGON);
	glVertex2d(195, 370);
	glVertex2d(195, 330);
	glVertex2d(230, 300);
	glVertex2d(265, 330);
	glVertex2d(265, 370);
	glEnd();

	glColor3ub(143, 62, 62);
	glBegin(GL_POLYGON);
	glVertex2d(300, 370);
	glVertex2d(400, 370);
	glVertex2d(400, 600);
	glVertex2d(300, 600);
	glEnd();

	glColor3ub(136, 34, 34);
	glBegin(GL_POLYGON);
	glVertex2d(400, 320);
	glVertex2d(472, 320);
	glVertex2d(472, 600);
	glVertex2d(400, 600);
	glEnd();

	glColor3ub(143, 62, 62);
	glBegin(GL_POLYGON);
	glVertex2d(65, 365);
	glVertex2d(165, 365);
	glVertex2d(165, 370);
	glVertex2d(65, 370);
	glEnd();

	glColor3ub(143, 62, 62);
	glBegin(GL_POLYGON);
	glVertex2d(65, 300);
	glVertex2d(165, 300);
	glVertex2d(165, 305);
	glVertex2d(65, 305);
	glEnd();

	glColor3ub(143, 62, 62);
	glBegin(GL_POLYGON);
	glVertex2d(158, 300);
	glVertex2d(163, 300);
	glVertex2d(163, 600);
	glVertex2d(158, 600);
	glEnd();

	glColor3ub(143, 62, 62);
	glBegin(GL_POLYGON);
	glVertex2d(398, 365);
	glVertex2d(475, 365);
	glVertex2d(475, 370);
	glVertex2d(398, 370);
	glEnd();

	glColor3ub(136, 34, 34);
	glBegin(GL_POLYGON);
	glVertex2d(410, 300);
	glVertex2d(462, 300);
	glVertex2d(467, 320);
	glVertex2d(405, 320);
	glEnd();

	glColor3ub(170, 170, 170);
	glBegin(GL_POLYGON);
	glVertex2d(405, 300);
	glVertex2d(467, 300);
	glVertex2d(467, 295);
	glVertex2d(405, 295);
	glEnd();

	glColor3ub(120, 120, 120);
	glBegin(GL_TRIANGLES);
	glVertex2d(409, 295);
	glVertex2d(463, 295);
	glVertex2d(436, 190);
	glEnd();

	glColor3f(0, 0, 0);
	glBegin(GL_LINES);
	glVertex2d(436, 190);
	glVertex2d(436, 144);
	glEnd();

	glColor3ub(143, 62, 62);
	glBegin(GL_POLYGON);
	glVertex2d(415, 560);
	glVertex2d(460, 560);
	glVertex2d(460, 600);
	glVertex2d(415, 600);
	glEnd();

	glColor3ub(143, 62, 62);
	glBegin(GL_POLYGON);
	glVertex2d(425, 530);
	glVertex2d(450, 530);
	glVertex2d(460, 560);
	glVertex2d(415, 560);
	glEnd();

	// Door
	glColor3ub(30, 30, 30);
	float R = 19.0f;
	int n = 1000;
	glBegin(GL_POLYGON);
	for (int i = 0; i < n; i++) {
		glVertex2f(R * cos(2 * PI * i / n) + 113, R * sin(2 * PI * i / n) + 570);
	}
	glEnd();

	glBegin(GL_POLYGON);
	glVertex2d(95, 570);
	glVertex2d(133, 570);
	glVertex2d(133, 600);
	glVertex2d(95, 600);
	glEnd();

	R = 15.0f;
	glBegin(GL_POLYGON);
	for (int i = 0; i < n; i++) {
		glVertex2f(R * cos(2 * PI * i / n) + 437, R * sin(2 * PI * i / n) + 580);
	}
	glEnd();

	glBegin(GL_POLYGON);
	glVertex2d(422, 580);
	glVertex2d(452, 580);
	glVertex2d(452, 600);
	glVertex2d(422, 600);
	glEnd();

	// Two windows in a row

	for (int i = 0; i < 2; i++) {
		for (int j = 0; j < 2; j++) {
			glColor3ub(30, 30, 30);
			glBegin(GL_POLYGON);
			glVertex2d(100 + 18 * j, 530 - 25 * i);
			glVertex2d(110 + 18 * j, 530 - 25 * i);
			glVertex2d(110 + 18 * j, 510 - 25 * i);
			glVertex2d(100 + 18 * j, 510 - 25 * i);
			glEnd();
		}
	}

	R = 5.0f;
	for (int a = 0; a < 2; a++) {
		glBegin(GL_POLYGON);
		for (int i = 0; i < n; i++) {
			glVertex2f(R * cos(2 * PI * i / n) + 105 + 18 * a, R * sin(2 * PI * i / n) + 485);
		}
		glEnd();
	}

	// Next Colomn
	// Two windows in a row

	for (int i = 0; i < 2; i++) {
		for (int j = 0; j < 2; j++) {
			glColor3ub(30, 30, 30);
			glBegin(GL_POLYGON);
			glVertex2d(422 + 18 * j, 480 - 25 * i);
			glVertex2d(432 + 18 * j, 480 - 25 * i);
			glVertex2d(432 + 18 * j, 460 - 25 * i);
			glVertex2d(422 + 18 * j, 460 - 25 * i);
			glEnd();
		}
	}

	R = 5.0f;
	for (int a = 0; a < 2; a++) {
		glBegin(GL_POLYGON);
		for (int i = 0; i < n; i++) {
			glVertex2f(R * cos(2 * PI * i / n) + 427 + 18 * a, R * sin(2 * PI * i / n) + 435);
		}
		glEnd();
	}

	// Three windoes in a row

	for (int i = 0; i < 3; i++) {
		glColor3ub(30, 30, 30);
		glBegin(GL_POLYGON);
		glVertex2d(210 + 15 * i, 340);
		glVertex2d(220 + 15 * i, 340);
		glVertex2d(220 + 15 * i, 365);
		glVertex2d(210 + 15 * i, 365);
		glEnd();
	}

	R = 5.0f;
	for (int a = 0; a < 3; a++) {
		glBegin(GL_POLYGON);
		for (int i = 0; i < n; i++) {
			glVertex2f(R * cos(2 * PI * i / n) + 215 + 15 * a, R * sin(2 * PI * i / n) + 340);
		}
		glEnd();
	}

	// 2 * 2 * 2 windows
	for (int i = 0; i < 2; i++) {
		for (int j = 0; j < 2; j++) {
			for (int z = 0; z < 2; z++) {
				glColor3ub(30, 30, 30);
				glBegin(GL_POLYGON);
				glVertex2d(355 - 40 * z + 17 * j, 445 - 27 * i);
				glVertex2d(365 - 40 * z + 17 * j, 445 - 27 * i);
				glVertex2d(365 - 40 * z + 17 * j, 425 - 27 * i);
				glVertex2d(355 - 40 * z + 17 * j, 425 - 27 * i);
				glEnd();
			}
		}
	}

	// 2 * 2 circles
	R = 5.0f;
	n = 1000;
	for (int a = 0; a < 2; a++) {
		for (int b = 0; b < 2; b++) {
			glBegin(GL_POLYGON);
			for (int i = 0; i < n; i++) {
				glVertex2f(R * cos(2 * PI * i / n) + 320 + 40 * b + 17 * a, R * sin(2 * PI * i / n) + 398);
			}
			glEnd();
		}
	}

	// 2 * 2 * 2 windows
	for (int i = 0; i < 2; i++) {
		for (int j = 0; j < 2; j++) {
			for (int z = 0; z < 2; z++) {
				glColor3ub(30, 30, 30);
				glBegin(GL_POLYGON);
				glVertex2d(355 - 40 * z + 17 * j, 535 - 40 * i);
				glVertex2d(365 - 40 * z + 17 * j, 535 - 40 * i);
				glVertex2d(365 - 40 * z + 17 * j, 505 - 40 * i);
				glVertex2d(355 - 40 * z + 17 * j, 505 - 40 * i);
				glEnd();
			}
		}
	}

	// Drawing the next row
	// 2 * 2 * 2 windows
	for (int i = 0; i < 2; i++) {
		for (int j = 0; j < 2; j++) {
			for (int z = 0; z < 2; z++) {
				glColor3ub(30, 30, 30);
				glBegin(GL_POLYGON);
				glVertex2d(235 - 40 * z + 17 * j, 445 - 27 * i);
				glVertex2d(245 - 40 * z + 17 * j, 445 - 27 * i);
				glVertex2d(245 - 40 * z + 17 * j, 425 - 27 * i);
				glVertex2d(235 - 40 * z + 17 * j, 425 - 27 * i);
				glEnd();
			}
		}
	}

	// 2 * 2 circles
	R = 5.0f;
	n = 1000;
	for (int a = 0; a < 2; a++) {
		for (int b = 0; b < 2; b++) {
			glBegin(GL_POLYGON);
			for (int i = 0; i < n; i++) {
				glVertex2f(R * cos(2 * PI * i / n) + 200 + 40 * b + 17 * a, R * sin(2 * PI * i / n) + 398);
			}
			glEnd();
		}
	}

	// 2 * 2 * 2 windows
	for (int i = 0; i < 2; i++) {
		for (int j = 0; j < 2; j++) {
			for (int z = 0; z < 2; z++) {
				glColor3ub(30, 30, 30);
				glBegin(GL_POLYGON);
				glVertex2d(235 - 40 * z + 17 * j, 535 - 40 * i);
				glVertex2d(245 - 40 * z + 17 * j, 535 - 40 * i);
				glVertex2d(245 - 40 * z + 17 * j, 505 - 40 * i);
				glVertex2d(235 - 40 * z + 17 * j, 505 - 40 * i);
				glEnd();
			}
		}
	}
}

void drawS() {

	// Fill in the color of blocks
	for (int i = 0; i < 10; i++) {
		for (int j = 0; j < 6; j++) {
			if (i % 2 == 1 && j % 2 == 1) {
				glColor3ub(104, 127, 127);
			}
			else if (i % 2 == 1 && j % 2 == 0) {
				glColor3ub(63, 100, 93);
			}
			else if (i % 2 == 0 && j % 2 == 1) {
				glColor3ub(108, 147, 141);
			}
			else if (i % 2 == 0 && j % 2 == 0) {
				glColor3ub(73, 124, 114);
			}
			glBegin(GL_POLYGON);
			glVertex2d(0 + i * 30, 30 + j * 27);
			glVertex2d(0 + i * 30, 60 + j * 27);
			glVertex2d(30 + i * 30, 60 + j * 27);
			glVertex2d(30 + i * 30, 30 + j * 27);
			glEnd();
		}
	}

	// Filling algorithm for columns 
	for (int i = 0; i < 6; i++) {
		if (i % 2 == 1) {
			glColor3ub(177, 64, 64);
		}
		else {
			glColor3ub(185, 106, 106);
		}
		glBegin(GL_POLYGON);
		glVertex2d(0, 30 + i * 30);
		glVertex2d(0, 60 + i * 30);
		glVertex2d(10, 60 + i * 30);
		glVertex2d(10, 30 + i * 30);
		glEnd();
	}

	// Filling algorithm for rows

	for (int i = 0; i < 3; i++) {
		if (i % 2 == 0) {
			glColor3ub(177, 64, 64);
		}
		else {
			glColor3ub(185, 106, 106);
		}
		glBegin(GL_POLYGON);
		glVertex2d(10 + i * 30, 30);
		glVertex2d(10 + i * 30, 40);
		glVertex2d(40 + i * 30, 40);
		glVertex2d(40 + i * 30, 30);
		glEnd();
	}

	for (int i = 0; i < 2; i++) {
		if (i % 2 == 1) {
			glColor3ub(177, 64, 64);
		}
		else {
			glColor3ub(185, 106, 106);
		}
		glBegin(GL_POLYGON);
		glVertex2d(100, 30 + i * 30);
		glVertex2d(110, 30 + i * 30);
		glVertex2d(110, 60 + i * 30);
		glVertex2d(100, 60 + i * 30);
		glEnd();
	}

	for (int i = 0; i < 2; i++) {
		if (i % 2 == 1) {
			glColor3ub(177, 64, 64);
		}
		else {
			glColor3ub(185, 106, 106);
		}
		glBegin(GL_POLYGON);
		glVertex2d(100 + i * 30, 90);
		glVertex2d(100 + i * 30, 100);
		glVertex2d(130 + i * 30, 100);
		glVertex2d(130 + i * 30, 90);
		glEnd();
	}

	for (int i = 0; i < 3; i++) {
		if (i % 2 == 1) {
			glColor3ub(177, 64, 64);
		}
		else {
			glColor3ub(185, 106, 106);
		}
		glBegin(GL_POLYGON);
		glVertex2d(210 + i * 30, 30);
		glVertex2d(210 + i * 30, 40);
		glVertex2d(240 + i * 30, 40);
		glVertex2d(240 + i * 30, 30);
		glEnd();
	}

	for (int i = 0; i < 6; i++) {
		if (i % 2 == 0) {
			glColor3ub(177, 64, 64);
		}
		else {
			glColor3ub(185, 106, 106);
		}
		glBegin(GL_POLYGON);
		glVertex2d(300, 30 + i * 30);
		glVertex2d(300, 60 + i * 30);
		glVertex2d(310, 60 + i * 30);
		glVertex2d(310, 30 + i * 30);
		glEnd();
	}

	glColor3ub(185, 106, 106);
	glBegin(GL_POLYGON);
	glVertex2d(160, 90);
	glVertex2d(160, 100);
	glVertex2d(185, 70);
	glVertex2d(185, 60);
	glEnd();

	glColor3ub(177, 64, 64);
	glBegin(GL_POLYGON);
	glVertex2d(185, 70);
	glVertex2d(185, 60);
	glVertex2d(210, 30);
	glVertex2d(210, 40);
	glEnd();

	glColor3ub(170, 170, 170);
	glBegin(GL_POLYGON);
	glVertex2d(0, 0);
	glVertex2d(0, 30);
	glVertex2d(310, 30);
	glVertex2d(310, 0);
	glEnd();

	glColor3ub(41, 63, 95);
	glBegin(GL_POLYGON);
	glVertex2d(0, 0);
	glVertex2d(0, 10);
	glVertex2d(310, 10);
	glVertex2d(310, 0);
	glEnd();

	glColor3ub(120, 120, 120);
	glBegin(GL_POLYGON);
	glVertex2d(0, 0);
	glVertex2d(0, 30);
	glVertex2d(30, 30);
	glVertex2d(30, 0);
	glEnd();

	glColor3ub(120, 120, 120);
	glBegin(GL_POLYGON);
	glVertex2d(60, 0);
	glVertex2d(60, 30);
	glVertex2d(90, 30);
	glVertex2d(90, 0);
	glEnd();


	glColor3ub(120, 120, 120);
	glBegin(GL_POLYGON);
	glVertex2d(120, 0);
	glVertex2d(120, 40);
	glVertex2d(180, 40);
	glVertex2d(180, 0);
	glEnd();

	glColor3ub(41, 63, 95);
	glBegin(GL_POLYGON);
	glVertex2d(130, 0);
	glVertex2d(130, 30);
	glVertex2d(170, 30);
	glVertex2d(170, 0);
	glEnd();

	glColor3ub(120, 120, 120);
	glBegin(GL_POLYGON);
	glVertex2d(220, 0);
	glVertex2d(220, 30);
	glVertex2d(250, 30);
	glVertex2d(250, 0);
	glEnd();

	glColor3ub(120, 120, 120);
	glBegin(GL_POLYGON);
	glVertex2d(280, 0);
	glVertex2d(280, 30);
	glVertex2d(310, 30);
	glVertex2d(310, 0);
	glEnd();

}

void drawLogo() {

	glLineWidth(1);
	glBegin(GL_LINES);
	for (int i = 0; i < 3; i++) {
		glColor3ub(255, 255, 255);
		glVertex2d(20 + 5 * i, 35);
		glColor3ub(110, 110, 110);
		glVertex2d(20 + 5 * i, 110);

		glColor3ub(255, 255, 255);
		glVertex2d(20 + 5 * i, 115);
		glVertex2d(20 + 5 * i, 130);
	};
	glEnd();

	glBegin(GL_LINES);
	for (int i = 0; i < 3; i++) {
		glColor3ub(255, 255, 255);
		glVertex2d(35 + 5 * i, 35);
		glColor3ub(110, 110, 110);
		glVertex2d(35 + 5 * i, 108 - 2 * i);

		glColor3ub(255, 255, 255);
		glVertex2d(35 + 5 * i, 113 - 2 * i);
		glVertex2d(35 + 5 * i, 130);
	};
	glEnd();

	glBegin(GL_LINES);
	glColor3ub(110, 110, 110);
	glVertex2d(50, 45);
	glColor3ub(50, 50, 50);
	glVertex2d(50, 102);
	glEnd();

	glBegin(GL_LINES);
	glColor3ub(110, 110, 110);
	glVertex2d(55, 50);
	glColor3ub(55, 50, 50);
	glVertex2d(55, 100);
	glEnd();

	glBegin(GL_LINES);
	for (int i = 0; i < 3; i++) {
		glColor3ub(110, 110, 110);
		glVertex2d(60 + 5 * i, 55);
		glColor3ub(50, 50, 50);
		glVertex2d(60 + 5 * i, 98 - 2 * i);
	};
	glEnd();

	glColor3ub(110, 110, 110);
	glBegin(GL_LINES);
	for (int i = 0; i < 5; i++) {
		glVertex2d(50 + 5 * i, 107 - 2 * i);
		glVertex2d(50 + 5 * i, 130);
	};
	glEnd();

	glBegin(GL_LINES);
	for (int i = 0; i < 6; i++) {
		glColor3ub(255, 255, 255);
		glVertex2d(75 + 5 * i, 35);
		glColor3ub(110, 110, 110);
		glVertex2d(75 + 5 * i, 92 - 2 * i);
	};
	glEnd();

	glBegin(GL_LINES);
	for (int i = 0; i < 12; i++) {
		glColor3ub(110, 110, 110);
		glVertex2d(105 + 5 * i, 35);
		glColor3ub(50, 50, 50);
		glVertex2d(105 + 5 * i, 80);
		glColor3ub(255, 255, 255);
		glVertex2d(105 + 5 * i, 50);
		glVertex2d(105 + 5 * i, 65);
	};
	glEnd();

	glColor3ub(255, 255, 255);
	glBegin(GL_LINES);
	for (int i = 0; i < 6; i++) {
		glVertex2d(75 + 5 * i, 97 - 2 * i);
		glVertex2d(75 + 5 * i, 130);
	};
	glEnd();

	glColor3ub(255, 255, 255);
	glBegin(GL_LINES);
	for (int i = 0; i < 12; i++) {
		glVertex2d(105 + 5 * i, 85);
		glVertex2d(105 + 5 * i, 130);
	};
	glEnd();

	glColor3ub(110, 110, 110);
	glBegin(GL_LINES);
	for (int i = 0; i < 5; i++) {
		glVertex2d(75 + 5 * i, 98);
		glVertex2d(75 + 5 * i, 120 - 2 * i);
	};
	glEnd();

	glBegin(GL_LINES);
	for (int i = 0; i < 8; i++) {
		glColor3ub(110, 110, 110);
		glVertex2d(100 + 5 * i, 98);
		glColor3ub(50, 50, 50);
		glVertex2d(100 + 5 * i, 118);
	};
	glEnd();
}

void drawBalloon(void) {

	if (wordFlag == 0)
	{
		glColor3f(1, 1, 1);
		selectFont(24, ANSI_CHARSET, "Helvetica");
		glRasterPos2f(370, 200);
		drawString("Click the mouse to show balloons!");
	}
	else if (wordFlag == 1)
	{
		int n = 3000;
		float a = 50.0f;
		float b = 55.0f;

		// Balloon 1
		glColor3ub(169, 60, 196);
		glBegin(GL_TRIANGLE_FAN);

		for (int i = 1; i <= n; i++) {
			glVertex2f(a * cos(2 * PI / i * n) + 100, b * sin(2 * PI / i * n) + 100 + wordy + step1);
		}
		glEnd();
		glBegin(GL_POINTS);
		for (float i = 0; i < 500; i = i + 5.0) {
			float x = 5.0 * sin(i * (2 * PI / 360.0));
			float y = 0.3 * (float)i;
			glColor3ub(255, 255, 255);
			glVertex2f(x + 95, y + wordy + step1 - 106);
		}
		glEnd();

		// Balloon 2
		glColor3ub(85, 50, 137);
		glBegin(GL_TRIANGLE_FAN);
		for (int i = 1; i <= n; i++) {
			glVertex2f(a * cos(2 * PI / i * n) + 810, b * sin(2 * PI / i * n) + 50 + wordy + step1);
		}
		glEnd();
		glBegin(GL_POINTS);
		for (float i = 0; i < 500; i = i + 5.0) {
			float x = 5.0 * sin(i * (2 * PI / 360.0));
			float y = 0.3 * (float)i;
			glColor3ub(255, 255, 255);
			glVertex2f(x + 805, y + wordy + step1 - 154);
		}
		glEnd();

		// Balloon 3
		glColor3ub(116, 68, 187);
		glBegin(GL_TRIANGLE_FAN);
		for (int i = 1; i <= n; i++) {
			glVertex2f(a * cos(2 * PI / i * n) + 410, b * sin(2 * PI / i * n) + 50 + wordy + step1);
		}
		glEnd();
		glBegin(GL_POINTS);
		for (float i = 0; i < 500; i = i + 5.0) {
			float x = 5.0 * sin(i * (2 * PI / 360.0));
			float y = 0.3 * (float)i;
			glColor3ub(255, 255, 255);
			glVertex2f(x + 405, y + wordy + step1 - 154);
		}
		glEnd();

		if (wordy >= 600)
		{
			selectFont(24, ANSI_CHARSET, "Helvetica");
			glRasterPos2f(380, 230);
			drawString("Press \"F\" or \"f\" to \"change direction\"");

			selectFont(24, ANSI_CHARSET, "Helvetica");
			glRasterPos2f(380, 200);
			drawString("Press \"S\" or \"s\" to \"stop\"");

			selectFont(24, ANSI_CHARSET, "Helvetica");
			glRasterPos2f(380, 170);
			drawString("Press \"R\" or \"r\" to \"restart\"");

			selectFont(24, ANSI_CHARSET, "Helvetica");
			glRasterPos2f(380, 140);
			drawString("Press \"A\" or \"a\" to \"decrement\"");

			selectFont(24, ANSI_CHARSET, "Helvetica");
			glRasterPos2f(380, 110);
			drawString("Press \"D\" or \"d\" to \"increment\"");

			selectFont(24, ANSI_CHARSET, "Helvetica");
			glRasterPos2f(380, 80);
			drawString("Press \"Q\" or \"q\" to \"exit\"");
		}

	}
	glLoadIdentity();
	glFlush();
}




// Idle callback function
void whenInMainloop() {
	// Force OpenGL to redraw the current window
	glutPostRedisplay();
}


void myDisplay(void) {
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0, 1080, 0, 720);
	glClearColor(1, 1, 1, 0);
	glClear(GL_COLOR_BUFFER_BIT);
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

	// Draw Blending Background
	glPushMatrix();
	drawBackground();
	glPopMatrix();
	glFlush();

	// Draw Blending Bars
	glPushMatrix();
	drawBar();
	glPopMatrix();

	// Draw Logo
	glPushMatrix();
	glTranslated(390, 550, 0);
	glScalef(1.5f, -1.5f, 1.5f);
	drawLogo();
	glPopMatrix();

	// Draw CB Cube
	glPushMatrix();
	glTranslated(720, 370, 0);
	glScalef(0.45f, -0.45f, 0.45f);
	drawCB();
	glPopMatrix();

	// Draw Liv
	glPushMatrix();
	glTranslated(0, 400, 0);
	glScalef(0.6f, -0.6f, 0.6f);
	drawLiv();
	glPopMatrix();

	// Draw Clock on Liv
	glPushMatrix();
	glTranslated(18, 197, 0);
	glScalef(0.15f, 0.15f, 0.15f);
	glColor3f(0, 0, 0);
	drawClock();
	glPopMatrix();

	// Draw Clock
	glPushMatrix();
	glTranslated(750, 380, 0);
	glScalef(0.7f, 0.7f, 0.7f);
	glColor4ub(255, 255, 255, 0.5);
	drawClock();
	glPopMatrix();

	// Draw Science Building
	glPushMatrix();
	glTranslated(50, 550, 0);
	glScalef(0.5f, 0.5f, 0.5f);
	drawS();
	glPopMatrix();

	// Draw 2D Text
	glColor3f(1.0, 1.0, 1.0);
	selectFont(24, ANSI_CHARSET, "Helvetica");
	glRasterPos2f(418, 320);
	drawString("2006 - 2021  X J T L U");

	glColor3f(1.0, 1.0, 1.0);
	selectFont(24, ANSI_CHARSET, "Helvetica");
	glRasterPos2f(10, 698);
	drawString("Xi'an Jiaotong-Liverpool University");

	glColor3f(1.0, 1.0, 1.0);
	selectFont(24, ANSI_CHARSET, "Helvetica");
	glRasterPos2f(910, 698);
	drawString("Xuening.Wang19");


	// Draw Balloon
	glPushMatrix();
	drawBalloon();
	glPopMatrix();

	// Draw Greetings
	glColor3f(1.0, 1.0, 1.0);
	selectFont(24, ANSI_CHARSET, "Helvetica");
	glRasterPos2f(p0.x + 100, p0.y + 400);
	drawString("Happy 15th Anniversary!!!");

	glRasterPos2f(p0.x + 50, p0.y + 520);
	drawString("Light & Wings");

	glRasterPos2f(p0.x + 0, p0.y + 450);
	drawString("XJTLU");

	glRasterPos2f(p0.x + 300, p0.y + 520);
	drawString("Happy Birthday");

	glRasterPos2f(p0.x + 250, p0.y + 450);
	drawString("ICS YYDS");

	glutSwapBuffers();
}



int main(int argc, char** argv) {
	glutInit(&argc, argv);
	/*glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE);*/
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowSize(1080, 720);
	glutCreateWindow("Greeting Card");
	SetupRC();
	glutTimerFunc(time_interval, OnTimer1, 1);
	glutTimerFunc(time_interval, OnTimer2, 1);
	glutTimerFunc(1000, timerFunc, 1);
	glutDisplayFunc(&myDisplay);
	glutIdleFunc(whenInMainloop);
	glutMouseFunc(mouse_input);//mouse callback function
	glutKeyboardFunc(keyboard_input); // keyboard callback function

	glutMainLoop();
}