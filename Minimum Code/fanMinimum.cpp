#include "iostream"
#include "GL/glut.h"
#include "unistd.h"
int speed=1;
void draw()
{
	glBegin(GL_LINE_LOOP);
		glVertex2f(0,0);
		glVertex2f(100,0);
		glVertex2f(100,10);
		glVertex2f(-100,-10);
		glVertex2f(-100,0);
	glEnd();
}
void display(){}
void keyboard(unsigned char key, int x, int y)
{
	speed = key - '0';
}
void step(){
	glClear(GL_COLOR_BUFFER_BIT);
	glRotatef(speed, 0,0,1);
	draw();
	usleep(30000);
	glFlush();
}
int main(int argc, char *argv[])
{
	glutInit(&argc, argv);
	glutCreateWindow("window");
	glutInitWindowSize(500,500);
	gluOrtho2D(-250,250,-250,250);
	glutDisplayFunc(display);
	glColor3f(1,0,0);
	glClearColor(1,1,1,1);
	glutIdleFunc(step);
	glutKeyboardFunc(keyboard);
	glutMainLoop();
	return 0;
}