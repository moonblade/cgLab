#include<iostream>
#include<math.h>
#include<unistd.h>
#include<GL/glut.h>
#define w 500
using namespace std;
class Point{
public:
    int x,y;
    Point(int a=0, int b=0){x=a; y=b;}
    Point middle(Point b)
    {
        return Point((x+b.x)/2, (y+b.y)/2);
    }
    Point shift(Point b)
    {
        return Point(x+(x-b.x), y);
    }
    void print()
    {
        cout<<"x : "<<x<<", y : "<<y<<endl; 
    }
};
class ball{
public:
    Point start;
    Point end;
    Point center;
    Point position;
    int radius = w/4;
    int r=10;
    ball(){
        start = Point(0,10);
        end = Point(w/2,10);
        center = start.middle(end);

        position=start;
    }
    void bounce(){
        glClear(GL_COLOR_BUFFER_BIT);
        glColor3f(1,0,0);
        draw();
        while(end.x<w)
        {
            start.print();
            end.print();
            center.print();
            arc();
            start = end;
            end = end.shift(center);
            center = start.middle(end);
            radius/=2;
        }
    }
    void arc()
    {
        for(int i=180; i>0; i-=125/radius)
        {
            glClear(GL_COLOR_BUFFER_BIT);
            float theta = i*3.14/180;
            position = Point(center.x + radius*cos(theta), center.y + radius*sin(theta));
            draw();
            usleep(30000);
        }
    }
    void draw(){
        glBegin(GL_LINE_STRIP);
        for(int i=0;i<360;++i)
        {
            float theta = i*3.14/180;
            glVertex2f(position.x + r*cos(theta), position.y + r*sin(theta));
        }
        glEnd();
        glFlush();
    }
}b;
void display()
{
    glClear(GL_COLOR_BUFFER_BIT);
    b.bounce();
    glFlush();
}
int main(int argc, char *argv[])
{
    glutInit(&argc, argv);
    glutCreateWindow("w");
    glutInitWindowSize(w,w);
    gluOrtho2D(0,w,0,w);
    glClearColor(1,1,1,1);
    glutDisplayFunc(display);
    glutMainLoop();
}