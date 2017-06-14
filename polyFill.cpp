#include<iostream>
#include<vector>
#include<set>
#include<unistd.h>
#include<GL/glut.h>
using namespace std;
#define w 300
float boundary[]={1,0,0};
float fillC[]={0,1,0};
float blue[]={0,0,1};
float black[]={1,1,1};
float col[]={0,0,0};
bool same(float a[], float b[]){
    for(int i=0;i<3;++i)
        if(a[i]!=b[i])
            return false;
    return true;
}
void color(float a[])
{
    for(int i=0;i<3;++i)
        cout<<a[i]<<" ";
    cout<<endl;
}
class Point
{
public:
    int x,y;
    Point(int a=0, int b=0){x=a;y=b;}
    int toInt(){return w*x+y;}
    Point up(){return Point(x,y+1);}
    Point down(){return Point(x,y-1);}
    Point right(){return Point(x+1,y);}
    Point left(){return Point(x-1,y);}
    void print(){cout<<"x: "<<x<<", y: "<<y<<endl;}
};
class Set
{
public:
    set<int> s;
    void insert(Point a)
    {
        s.insert(a.toInt());
    }
    bool has(Point a)
    {
        return s.find(a.toInt())!=s.end();
    }
}s;
class Polygon
{
public:
    vector<Point> body;
    int thickness;
    Point position;
    Polygon()
    {
        body.push_back(Point(0,0));
        body.push_back(Point(0,100));
        body.push_back(Point(100,100));
        body.push_back(Point(120,150));
        body.push_back(Point(100,0));
        body.push_back(Point(0,0));

        position=Point(w/2,w/2);
        thickness=2;
    }

    bool painted(Point p)
    {
        glReadPixels(p.x, p.y, 1, 1, GL_RGB, GL_FLOAT,col);
        if(same(col, boundary) || same(col, fillC))
            return true;
        return false;
    }

    void draw()
    {
        glColor3fv(boundary);
        glLineWidth(thickness);
        glBegin(GL_LINE_STRIP);
        for(int i=0;i<body.size();++i)
            glVertex2f(position.x+body[i].x, position.y+body[i].y);
        glEnd();
        glLineWidth(1);
        glFlush();
    }

    void paint(Point p)
    {
        glColor3fv(fillC);
        glBegin(GL_POINTS);
        glVertex2f(p.x,p.y);
        glEnd();
        glFlush();
    }

    void fill(Point p)
    {
        if(s.has(p))
            return;
        s.insert(p);
        if(!painted(p))
        {
            fill(p.up());
            fill(p.right());
            fill(p.down());
            fill(p.left());
            paint(p);
        }
    }
}p;
void display()
{
    glClear(GL_COLOR_BUFFER_BIT);
    p.draw();
    glFlush();
}
void mouse(int button,int state, int x, int y)
{
    cout<<x<<" "<<w-y<<endl;
    p.fill(Point(x,w-y));
}
int main(int argc, char *argv[])
{
    glutInit(&argc, argv);
    glutCreateWindow("window");
    glutInitWindowSize(w,w);
    glLoadIdentity();
    gluOrtho2D(0,w,0,w);
    glClearColor(1,1,1,1);
    glutDisplayFunc(display);
    glutMouseFunc(mouse);
    glutMainLoop();
}