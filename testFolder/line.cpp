#include<GL/glut.h>
#include<stdio.h>
#include<math.h>
using namespace std;

float startx,starty;
float endx,endy;

float round_value(float x){
	return floor(x+0.5);
}
void ddaline(){
	float dx=endx-startx;
	float dy=endy-starty;
	int steps;
	float xinc,yinc,x=startx,y=starty;
	steps=(abs(dx)>abs(dy))?abs(dx):abs(dy);
	xinc=dx/float(steps);
	yinc=dy/float(steps);
	glColor3f(1,0,0);
	glBegin(GL_POINTS);
	glVertex2f(x,y);
	for(int i=0;i<steps;++i){
		x+=xinc;
		y+=yinc;
		glVertex2f(x,y);
	}
	glEnd();
	glFlush();
}
void display()
{
    for(int i=0;i<360;i+=15)
	{
		startx=320; starty=240;
		endx=320+100*cos(i*3.14/180);
		endy=480+100*sin(i*3.14/180);
		ddaline();
		glFlush();
	}
}
void Init(){
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowPosition(0,0);
	glutInitWindowSize(640,480);
	glutCreateWindow("DDA");
	glClearColor(0.0,0.0,0.0,0);
	gluOrtho2D(0,640,0,480);
}

int main(int argc,char**argv){
	// cout<<"Enter the first ";
	// cin>>startx;
	// cin>>starty;
	// cout<<"enter the second ";
	// cin>>startx;
	// cin>>starty;
	glutInit(&argc,argv);
	Init();
	glutDisplayFunc(display);
	glutMainLoop();
	return 0;
}