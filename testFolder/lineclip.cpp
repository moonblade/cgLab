#include<iostream>
#include<GL/glut.h>
#define wi 500
float blue[] = {0,0,1};
float green[] = {0,1,0};
float red[] = {1,0,0};
class Point{
public:
    int x,y;
    Point(int a=0, int b=0){x=a;y=b;}
    Point middle(Point b){return Point((x+b.x)/2, (y+b.y)/2);}
    bool equal(Point b){return (x==b.x)&&(y==b.y);}
};
class Window{
public:
    Point tr, bl;
    Window()
    {
        tr = Point(200,200);
        bl = Point(10,10);
    }
    void draw()
    {
        glColor3fv(red);
        glBegin(GL_LINE_LOOP);
            glVertex2f(bl.x, bl.y);
            glVertex2f(bl.x, tr.y);
            glVertex2f(tr.x, tr.y);
            glVertex2f(tr.x, bl.y);
        glEnd();
    }

    //  8
    // 4 2
    //  1 
    int outcode(Point p)
    {
        int out=0;
        if (p.y>=tr.y)
            out|=8;
        if (p.x>=tr.x)
            out|=2;
        if (p.x<=bl.x)
            out|=4;
        if (p.y<=bl.y)
            out|=1;
        return out;
    }
}w;

class Line
{
public:
    Point a, b;
    Line(Point aa = Point(0,0), Point bb = Point(240,210))
    {
        a=aa;
        b=bb;
    }

    void draw(float color[3])
    {
        glColor3fv(color);
        glBegin(GL_LINE_STRIP);
            glVertex2f(a.x, a.y);
            glVertex2f(b.x, b.y);
        glEnd();
    }

    void draw(float color[3], Point a, Point b)
    {
        glColor3fv(color);
        glBegin(GL_LINE_STRIP);
            glVertex2f(a.x, a.y);
            glVertex2f(b.x, b.y);
        glEnd();
        glFlush();
    }

    void clip(){
        clip(a,b);
    }

    void clip(Point a, Point b)
    {
        if(w.outcode(a)==0 && w.outcode(b)==0) 
        {
            draw(green,a,b);
        }  
        else if((w.outcode(a)&w.outcode(b))==0)
        {
            Point p = a.middle(b);
            if(!a.equal(p) && !(b.equal(p)))
            {
                clip(a,p);
                clip(p,b);
            }
        }
    }
};

void display()
{
    Line l;
    w.draw();
    l.draw(blue);
    glFlush();
    l.clip();
    glFlush();
}
int main(int argc, char *argv[])
{
    glutInit(&argc, argv);
    glutCreateWindow("window");
    glutInitWindowSize(wi,wi);
    glutDisplayFunc(display);
    gluOrtho2D(-wi/2,wi/2,-wi/2,wi/2);
    glClearColor(1,1,1,1);
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(1,0,0);
    glutMainLoop();
}