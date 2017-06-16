#include "iostream"
#include "GL/glut.h"
#include "vector"
#include "unistd.h"
#include "math.h"
#include "stdlib.h"
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
class Rain{
public:
	int i=99;
	int transy[100];
	Point rain[100];
	void drawLine(int rx,int ry){
		glColor3f(1,1,1);
		glBegin(GL_LINES);
		glVertex2f(rx,ry);
		glVertex2f(rx,ry+10);
		glEnd();
		glFlush();
	}
	void initRain(){
		for(;i>=0; i--){
			int randx = random()%500;
			int randy = random()%500;
			rain[i].x = randx;
			rain[i].y = randy;
			// drawLine(randx,randy);
		}
	}
	void drawRain(){
		for(int i=0; i<100; i++)
			drawLine(rain[i].x,rain[i].y+transy[i]);
	}
	void step(){
		for(int i=0; i<100; i++)
			transy[i] -=1;
		// transy %= 500;
		glClear(GL_COLOR_BUFFER_BIT);
		for(int i=0; i<100; i++){
			if((rain[i].y+transy[i])<=0){
				// cout<<"here";
				transy[i]=500;
			}
		}
	}
};
 Rain r;
 class Person{
 public:
 	vector<Point>body;
 	int transx=0;
 	Person(){
 		body.push_back(Point(0,0));
 		body.push_back(Point(30,30));
 		body.push_back(Point(60,0));
 		body.push_back(Point(30,30));
 		body.push_back(Point(30,70));
 		body.push_back(Point(60,40));
 		body.push_back(Point(90,70));
 		body.push_back(Point(90,150));
 		body.push_back(Point(90,70));
 		body.push_back(Point(60,40));
 		body.push_back(Point(30,70));
 		body.push_back(Point(0,40));
 		body.push_back(Point(30,70));
 		body.push_back(Point(30,90));
 	}
 	void drawPerson(){
 		glColor3f(0,0,1);
 		glBegin(GL_LINE_STRIP);
 		for(int i=0; i<body.size(); i++)
 			glVertex2f(body[i].x+transx,body[i].y);
 		glEnd();
 		glBegin(GL_LINE_LOOP);
 		for(int i=0; i<=360; i++)
 			glVertex2f(30+25*cos(i*3.14/180)+transx,115+25*sin(i*3.14/180));
 		glEnd();
 		glBegin(GL_LINE_LOOP);
 		for (int i = 0; i <=180; ++i)
 		{
 			glVertex2f(90+70*cos(i*3.14/180)+transx,150+70*sin(i*3.14/180));
 		}
 		glEnd();
 		glFlush();
 	}

 	void step(){
 		transx+=1;
 		transx%=500;
 		glClear(GL_COLOR_BUFFER_BIT);
 	}
 	void drawBound(){
 		for(int i=0; i<100; i++){
            cout<<r.rain[i].x<<" ";
            cout<<r.rain[i].y<<" ";
            cout<<r.transy[i]<<" ";
            cout<<r.rain[i].y+r.transy[i]<<" ";

 			cout<<(r.rain[i].x<=160+transx && r.rain[i].x>=20+transx)||(r.rain[i].y+r.transy[i]>=0 && r.rain[i].y+r.transy[i]<=150);
             cout<<endl;
 			if((r.rain[i].x<=160+transx && r.rain[i].x>=20+transx)&&(r.rain[i].y+r.transy[i]>=0 && r.rain[i].y+r.transy[i]<=150)){
 				r.transy[i]=500;
 			}
 		}
         cout<<endl;
 	}
 };
 
 
 Person p;
 void idle(){
 	p.drawPerson();
 	r.drawRain();
 	r.step();
 	p.step();
 	p.drawBound();
 	// r.drawRain();
 }
 void timer(int){
 	idle();
	glutTimerFunc(40,timer,1);

 }

 void display(){}
int main(int argc, char *argv[])
{
	glutInit(&argc,argv);
	glutCreateWindow("Window");
	glutInitWindowSize(500,500);
	glutInitWindowPosition(00,00);
	gluOrtho2D(0,500,0,500);
	glClearColor(0,0,0,1);
	glClear(GL_COLOR_BUFFER_BIT);
 	r.initRain();
 	// p.bound();
	glutDisplayFunc(display);
	// glutKeyboardFunc(keyboard);
	glutTimerFunc(40,timer,1);
	glutMainLoop();
	return 0;
}