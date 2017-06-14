#include "iostream"
#include "GL/glut.h"
#include "vector"
#include "unistd.h"
using namespace std;
#define w 500
class Point{
public:
	int x,y;
	Point(int a=0,int b=0){x=a;y=b;}
};
class Fan{
public:
	vector<Point> body;
	int speed=1;

	Fan(){
		body.push_back(Point(0,0));
		body.push_back(Point(100,0));
		body.push_back(Point(100,10));
		body.push_back(Point(0,0));
		body.push_back(Point(-100,0));
		body.push_back(Point(-100,-10));
		body.push_back(Point(0,0));
		body.push_back(Point(0,100));
		body.push_back(Point(-10,100));
		body.push_back(Point(0,0));
		body.push_back(Point(0,-100));
		body.push_back(Point(10,-100));
		body.push_back(Point(0,0));
	}

	void draw(){
		glClear(GL_COLOR_BUFFER_BIT);
		glColor3f(1,0,0);
		glBegin(GL_LINE_STRIP);
		for(int i=0;i<body.size();++i)
		{
			glVertex2f(body[i].x, body[i].y);
		}
		glEnd();
		glFlush();
	}

	void step(){
		glRotatef(speed, 0, 0, 1);
	}

}f;

void keyboard(unsigned char key, int x, int y){
	f.speed=key-'0';
}

void step()
{
	f.draw();
	f.step();
	usleep(40000);
}

void display()
{

}
int main(int argc, char *argv[])
{
	glutInit(&argc, argv);
	glutCreateWindow("window");
	glutInitWindowSize(w,w);
	gluOrtho2D(-w/2,w/2,-w/2,w/2);
	glutDisplayFunc(display);
	glClearColor(1,1,1,1);
	glutIdleFunc(step);
	glutKeyboardFunc(keyboard);
	glClear(GL_COLOR_BUFFER_BIT);
	glutMainLoop();
	return 0;
}