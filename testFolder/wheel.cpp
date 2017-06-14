#include "iostream"
#include "GL/glut.h"
#include "unistd.h"
#include "math.h"
void draw(int x)
{
	glBegin(GL_LINE_STRIP);
	for(int i=0;i<360; ++i)
		{
			float theta=i*3.14/180;
			glVertex2f(x+20*cos(theta),20*sin(theta));
				if((i+x)%30==0)
					glVertex2f(x,0);
		}
	glEnd();
}
void display(){}
int x=-200;
void step(){
	glClear(GL_COLOR_BUFFER_BIT);
	draw(x);
	x++;
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
	glutMainLoop();
	return 0;
}