#include<GL/glut.h>
#include<iostream>
#include<math.h>
#include <windows.h>
using namespace std;

GLfloat pointsize = 1.0f;
int mode;
int graphic_mode;
int r_x1, r_y1, r_x2, r_y2, r_x3, r_y3, r_x4, r_y4;
int t_x1, t_y1, t_x2, t_y2, t_x3, t_y3;
int R, xm, ym;
//int X1, Y1, X2, Y2;

void DDA_Draw_Line(int x1, int y1, int x2, int y2) { //DDA
	if (x1 > x2) {
		int t;
		t = x1;
		x1 = x2;
		x2 = t;
		t = y1;
		y1 = y2;
		y2 = t;
	}
	GLfloat delta_x, delta_y, x, y;
	int dx, dy, steps;
	dx = x2 - x1;
	dy = y2 - y1;
	steps = abs(dx) > abs(dy) ? abs(dx) : abs(dy);
	delta_x = (GLfloat)dx / (GLfloat)steps;//计算斜率
	delta_y = (GLfloat)dy / (GLfloat)steps;//计算斜率
	x = x1;
	y = y1;
	//  glClear(GL_COLOR_BUFFER_BIT);
	glBegin(GL_POINTS);
	if (x1 == x2) {
		if (y1 > y2) {
			int t;
			t = y1;
			y1 = y2;
			y2 = t;
		}
		for (int i = y1; i <= y2; i++) {
			glVertex2i(x, i);
		}
		glEnd();
		return;
	}
	glVertex2f(x, y);
	for (int i = 1; i <= steps; i++) {
		x += delta_x;//增加增量画点
		y += delta_y;
		glVertex2f(x, y);
	}
	glEnd();
}

void Middle_Draw_Line(int x1, int y1, int x2, int y2) {//中点
	if (x1 > x2) {
		int t;
		t = x1;
		x1 = x2;
		x2 = t;
		t = y1;
		y1 = y2;
		y2 = t;
	}
	int a, b, deltal, delta2, d, x, y;
	a = y1 - y2;
	b = x2 - x1;
	d = 2 * a + b;
	deltal = 2 * a;
	delta2 = 2 * (a + b);
	x = x1;
	y = y1;
	if (x1 == x2) {
		if (y1 > y2) {
			int t;
			t = y1;
			y1 = y2;
			y2 = t;
		}
		for (int i = y1; i <= y2; i++) {
			glVertex2i(x, i);
		}
		return;
	}
	glVertex2i(x, y);
	while (x < x2)
	{
		if (d < 0)
		{
			x++;
			y++;
			d += delta2;
		}
		else
		{
			x++;
			d += deltal;
		}
		glVertex2i(x, y);
	}
}
void setpoint(int x0, int y0, int x, int y)//同时绘制八个点(对称)
{
	glColor3f(1.0f, 1.0f, 1.0f);
	glVertex2f((x0 + x), (y0 + y));
	glVertex2f((x0 + y), (y0 + x));
	glVertex2f((x0 + y), (y0 - x));
	glVertex2f((x0 + x), (y0 - y));
	glVertex2f((x0 - x), (y0 - y));
	glVertex2f((x0 - y), (y0 - x));
	glVertex2f((x0 - y), (y0 + x));
	glVertex2f((x0 - x), (y0 + y));
}
void midpointcircle(int x0, int y0, int r)//中点画圆法
{
	int x = 0;
	int y = r;
	int d = 1 - r;      // 为了简化算法，摆脱浮点数，所以对d进行取整计算所以从1.25-r变到了1-r
	glClear(GL_COLOR_BUFFER_BIT);
	glBegin(GL_POLYGON);
	setpoint(x0, y0, x, y);
	while (x < y)
	{
		if (d < 0)
		{
			d += 2 * x + 3;
		}
		else
		{
			d += 2 * (x - y) + 5;
			y--;
		}
		x++;
		setpoint(x0, y0, x, y);
	}
	glEnd();
	glFlush();
}


void display() {          //选择哪种直线生成算法
	glClear(GL_COLOR_BUFFER_BIT);//clear
	glColor3f(1.0f, 1.0f, 1.0f);//white
	glBegin(GL_POINTS);
	if (graphic_mode == 3)
		midpointcircle(xm, ym, R);
	else {
		switch (mode) {
		case 1:
			if (graphic_mode == 1) {
				DDA_Draw_Line(r_x1, r_y1, r_x2, r_y2);
				DDA_Draw_Line(r_x2, r_y2, r_x3, r_y3);
				DDA_Draw_Line(r_x3, r_y3, r_x4, r_y4);
				DDA_Draw_Line(r_x4, r_y4, r_x1, r_y1);
			}
			else if (graphic_mode == 2) {
				DDA_Draw_Line(t_x1, t_y1, t_x2, t_y2);
				DDA_Draw_Line(t_x2, t_y2, t_x3, t_y3);
				DDA_Draw_Line(t_x3, t_y3, t_x1, t_y1);
			}
			break;
		case 2:
			if (graphic_mode == 1) {
				Middle_Draw_Line(r_x1, r_y1, r_x2, r_y2);
				Middle_Draw_Line(r_x2, r_y2, r_x3, r_y3);
				Middle_Draw_Line(r_x3, r_y3, r_x4, r_y4);
				Middle_Draw_Line(r_x4, r_y4, r_x1, r_y1);
			}
			else if (graphic_mode == 2) {
				Middle_Draw_Line(t_x1, t_y1, t_x2, t_y2);
				Middle_Draw_Line(t_x2, t_y2, t_x3, t_y3);
				Middle_Draw_Line(t_x3, t_y3, t_x1, t_y1);
			}
			break;
		}
	}
    
	glEnd();
	glFlush();
}

int main(int argc, char** argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(800, 800);
	glutCreateWindow("Lab_1_line");
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(-500.0, 800.0, -500.0, 800.0);
	cout << "choose your graphic:1.rectangle 2.triangle 3.cycle" << endl;
	cin >> graphic_mode;
	if (graphic_mode == 1) {
		cout << "input 4 point" << endl;
		cin >> r_x1 >> r_y1 >> r_x2 >> r_y2 >> r_x3 >> r_y3 >> r_x4 >> r_y4;
		cout << "choose your mode: 1.DDA 2.Middle" << endl;
		cin >> mode;
		glutDisplayFunc(display);
	}
	else if (graphic_mode == 2) {
		cout << "input 3 point" << endl;
		cin >> t_x1 >> t_y1 >> t_x2 >> t_y2 >> t_x3 >> t_y3;
		cout << "choose your mode: 1.DDA 2.Middle" << endl;
		cin >> mode;
		glutDisplayFunc(display);
	}
	else if (graphic_mode == 3) {
		cout << "input R and point" << endl;
		cin >> R >> xm >> ym;
		glutDisplayFunc(display);
	}

	glutDisplayFunc(display);
	glutMainLoop();
	return 0;
}
//按着注释填空就完了