#include "iostream"
#include "GL/glut.h"
#include "vector"
#include "unistd.h"
#include "math.h"
using namespace std;

class Point{
public:
	int x,y;
	Point(){}
	Point(int a, int b){
		x = a;
		y = b;
	}
};

int xtrans=0;
class Ball{
public:
	// vector <Point>body;
	Point c;
	int r;
	Point pos=Point(0,0);
	Ball(Point center, int radius){
		c = center;
		r = radius;
	}
	
	void drawBall(){
		glClear(GL_COLOR_BUFFER_BIT);
		glColor3f(1,0,0);
		glBegin(GL_LINE_LOOP);
		for(int i=0; i<=360; i++)
			glVertex2f(pos.x+c.x+r*cos(i*3.14/180),pos.y+c.y+r*sin(i*3.14/180));
		glEnd();
		usleep(10000);
		glFlush();
	}
	int width = 250;
	void trajectory(){
		Point cen=Point(width/2,0);
		int rad;
				glColor3f(1,0,0);
		glBegin(GL_LINE_LOOP);
		
		while(width>=15){
			rad=width/2;
			for(int i=180; i>0; i--){
				// if(width-(cen.x+rad*cos(i*3.14/180))>=0)
				// 	c.x=width-(cen.x+rad*cos(i*3.14/180));
				// else
					c.x=(cen.x+rad*cos(i*3.14/180));
				c.y=(cen.y+rad*sin(i*3.14/180));
				drawBall();
				// glVertex2f(cen.x+rad*cos(i*3.14/180),cen.y+rad*sin(i*3.14/180));
				// glVertex2f(c.x+r*cos(i*3.14/180),c.y+r*sin(i*3.14/180));
			}
			width/=2;
			cen=Point(500-width-width/2,0);

		}
		glEnd();
		glFlush();
	}
	void moveBall(){
		
		glClear(GL_COLOR_BUFFER_BIT);
		// for(int )
	}

};
Ball b(Point(20,20),20);

void idle(){
	// glClear(GL_COLOR_BUFFER_BIT);
	// glColor3f(1,0,0);
	// b.drawBall();
}
void display(){
	b.trajectory();
}
void timer(int){
	idle();
	glutTimerFunc(40,timer,1);
}
int main(int argc, char *argv[])
{
	glutInit(&argc,argv);
	glutCreateWindow("Window");
	glutInitWindowSize(500,500);
	glutInitWindowPosition(00,00);
	gluOrtho2D(0,500,0,500);
	glClearColor(0,0,0,1);
	glClear(GL_COLOR_BUFFER_BIT);
	glutDisplayFunc(display);
	// glutKeyboardFunc(keyboard);
	 glutTimerFunc(40,timer,1);
	glutMainLoop();
	return 0;
}