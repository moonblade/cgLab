#include <iostream>
#include <GL/glut.h>
#include <vector>
#include <math.h>
#include <unistd.h>
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

class Polygon{
public:
    vector<Point>poly;
    Polygon(){
        poly.push_back(Point(0,0));
        poly.push_back(Point(0,100));
        poly.push_back(Point(100,100));
        poly.push_back(Point(100,0));
    }
    void drawPolygon(){
        glBegin(GL_LINE_LOOP);
        for(int i=0; i<poly.size(); ++i)
            glVertex2f(poly[i].x, poly[i].y);
        glEnd();
        glFlush();
    }
};
Polygon p;
void display(){
    p.drawPolygon();
    glFlush();
}

int main(int argc, char *argv[]){
    glutInit(&argc, argv);
	glutCreateWindow("window");
	glutInitWindowSize(500,500);
	gluOrtho2D(-250,250,-250,250);
	glutDisplayFunc(display);
	glColor3f(1,0,0);
	glClearColor(1,1,1,1);
	glutDisplayFunc(display);
	glutMainLoop();
}