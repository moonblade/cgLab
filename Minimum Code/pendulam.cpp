#include "iostream"
#include "GL/glut.h"
#include "unistd.h"
#include "math.h"
int counter=50;
int speed=1;
void draw()
{
	glBegin(GL_LINE_STRIP);
		glVertex2f(0,0);
		glVertex2f(0,-100);
		for(int i=0+90;i<360+90; ++i)
		{
			float theta=i*3.14/180;
			glVertex2f(20*cos(theta),-100+20*sin(theta));
		}
	glEnd();
}
void display(){}
void step(){
	glClear(GL_COLOR_BUFFER_BIT);
	glRotatef(speed, 0,0,1);
	if(++counter%100==0)
		speed=-speed;
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
	glutMainLoop();
	return 0;
}