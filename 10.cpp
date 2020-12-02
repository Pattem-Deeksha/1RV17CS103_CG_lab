#include <math.h>
#include <vector>
#include <Windows.h>
#include <gl\glut.h>

using namespace std;


void myInit() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnable(GL_DEPTH_TEST);
	glClearColor(0, 0, 0, 1);
	glOrtho(-2, 2, -2, 2, 2, -2);
}

float Cube[][3] = { {-1, -1, -1}, {1, -1, -1}, {1, 1, -1}, {-1, 1, -1}, {-1, -1, 1}, {1, -1, 1}, {1, 1, 1}, {-1, 1, 1} };
float Colors[][3] = { {0, 0, 0}, {1, 0, 0}, {0, 1, 0}, {0, 0, 1}, {1, 1, 0}, {0, 1, 1}, {1, 0, 1}, {1, 1, 1} };
int axis = 0, theta[3] = { 0, 0, 0 };

void draw_face(int a, int b, int c, int d) {
	glBegin(GL_QUADS);
	glColor3fv(Colors[a]);
	glVertex3fv(Cube[a]);
	glColor3fv(Colors[b]);
	glVertex3fv(Cube[b]);
	glColor3fv(Colors[c]);
	glVertex3fv(Cube[c]);
	glColor3fv(Colors[d]);
	glVertex3fv(Cube[d]);
	glEnd();
}


void draw_cube() {
	draw_face(0, 3, 2, 1);
	draw_face(2, 3, 7, 6);
	draw_face(0, 4, 7, 3);
	draw_face(1, 2, 6, 5);
	draw_face(4, 5, 6, 7);
	draw_face(0, 1, 5, 4);
}


void spin_cube() {
	theta[axis] += 2;
	if (theta[axis] > 360)
		theta[axis] = -360;
	glutPostRedisplay();
}


void idle_func() {
	Sleep(10);
	spin_cube();
}


void mouse_func(int button, int state, int x, int y) {
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
		axis = 0;
	else if (button == GLUT_MIDDLE_BUTTON && state == GLUT_DOWN)
		axis = 1;
	else if (button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN)
		axis = 2;
}


void myDrawing() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glPushMatrix();
	glRotatef(theta[0], 1, 0, 0);
	glRotatef(theta[1], 0, 1, 0);
	glRotatef(theta[2], 0, 0, 1);
	draw_cube();
	glPopMatrix();
	glFlush();
	glutSwapBuffers();
}


int main(int argc, char* argv[]) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(500, 500);
	glutInitWindowPosition(0, 0);
	glutCreateWindow("sample");
	glutDisplayFunc(myDrawing);
	glutIdleFunc(idle_func);
	glutMouseFunc(mouse_func);
	myInit();
	glutMainLoop();
}
