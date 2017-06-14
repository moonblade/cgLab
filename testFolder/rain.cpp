#include "GL/glut.h"
#include "iostream"
#include "vector"
#include "unistd.h"
using namespace std;
class Point{
public:
	int x,y;
	Point(int a=0,int b=0){x=a; y=b;}
};

class Person{
public:
	vector<Point> body;
	Point position;
	Person(){
		body.push_back(Point(-20,0));
		body.push_back(Point(0,20));
		body.push_back(Point(20,0));
		body.push_back(Point(0,20));
		body.push_back(Point(0,80));
		body.push_back(Point(20,80));
		body.push_back(Point(-20,80));
		body.push_back(Point(0,80));
		body.push_back(Point(20,100));
		body.push_back(Point(0,120));
		body.push_back(Point(-20,100));
		body.push_back(Point(0,80));
		body.push_back(Point(20,80));
		body.push_back(Point(20,140));
		body.push_back(Point(40,140));
		body.push_back(Point(-40,140));
		body.push_back(Point(0,160));
		body.push_back(Point(40,140));

		position.x = -200;
		position.y = -250;
	}
	void draw()
	{
		glBegin(GL_LINE_STRIP);
		for(int i=0;i<body.size();++i)
		{
			glVertex2f(position.x+body[i].x, position.y+ body[i].y);
		}
		glEnd();
	}
	void step(){
		position.x++;
		if(position.x + body[0].x>250)
			position.x=-250;
	}
	Point getMax()
	{
		// top right of man
		Point max = Point(-250,-250);
		for(int i=0;i<body.size();++i)
		{
			if(body[i].y + position.y>max.y)
				max=Point(body[i].x + position.x, body[i].y + position.y);
		}
		for(int i=0;i<body.size();++i)
		{
			if(body[i].x + position.x>max.x)
				max.x=body[i].x + position.x;
		}
		return max;
	}
	Point getMin()
	{
		// bottom left of man
		Point min = Point(250,250);
		for(int i=0;i<body.size();++i)
		{
			if(body[i].y + position.y<min.y)
				min=Point(body[i].x + position.x, body[i].y + position.y);
		}
		for(int i=0;i<body.size();++i)
		{
			if(body[i].x + position.x<min.x)
				min.x=body[i].x + position.x;
		}
		return min;
	}
}p;

class Drop{
public:
	vector<Point> body;
	Point position;
	Drop(){
		body.push_back(Point(0,0));
		body.push_back(Point(0,10));
		position.x = random()%500 - 250;
		position.y = random()%500 - 250;
	}
	void draw(){
		if(!isInPerson())
		{
			glBegin(GL_LINE_STRIP);
				for(int i=0;i<body.size();++i)
				{
					glVertex2f(position.x+body[i].x, position.y+body[i].y);
				}
			glEnd();		
		}
	}
	bool isInPerson()
	{
		Point max = p.getMax();
		Point min = p.getMin();
		return position.x<max.x && position.x>min.x && position.y<max.y && position.y>min.y;
	}
	void step()
	{
		position.y-=3;
		// check if inside person or outside screen
		if(isInPerson() || (position.y<-250))
		{
			// anywhere on screen
			position.x = random()%500 - 250;
			position.y = 250; 
		}
	}

}d[100];
void display(){}
void step(){
	glClear(GL_COLOR_BUFFER_BIT);
	p.draw();
	p.step();
	for(int i=0;i<100;++i){

		d[i].draw();
		d[i].step();
	}
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