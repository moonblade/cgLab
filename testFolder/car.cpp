#include "iostream"
#include "GL/glut.h"
#include "unistd.h"
#include "math.h"
void draw(int x, int y)
{
	glBegin(GL_LINE_STRIP);
		glVertex2f(x+-50,y+0);
		glVertex2f(x+-50,y+50);
		glVertex2f(x+100,y+50);
		glVertex2f(x+100,y+0);
		for(int i=0;i<360; ++i)
		{
			float theta=i*3.14/180;
			glVertex2f(x+75+20*cos(theta),y+20*sin(theta));
				if((i+x)%30==0)
					glVertex2f(x+75,y);
		}
		for(int i=0;i<360; ++i)
		{
			float theta=i*3.14/180;
			glVertex2f(x-20+20*cos(theta),y+20*sin(theta));
				if((i+x)%30==0)
					glVertex2f(x-20,y);
		}
	glEnd();
}
void display(){}
int ax = -100, ay=0, bx=-100, by=-200;
void step(){
	glClear(GL_COLOR_BUFFER_BIT);
	draw(ax,ay);
	draw(bx,by);
	ax+=random()%10;
	bx+=random()%10;
	if(ax>500)
		ax=bx=-100;
	usleep(40000);
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