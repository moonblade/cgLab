// DOES NOT WORK
#include<iostream>
#include<vector>
#include<unistd.h>
#include<GL/glut.h>
using namespace std;

struct Point
{
    int x, y;
    Point(int a=0, int b=0)
    {
        x=a; y=b;
    }
};

class Window
{
    public:
    vector<Point> w;
    Window()
    {
        w.push_back(Point(0, 0));
        w.push_back(Point(200, 0));
        w.push_back(Point(200, 200));
        w.push_back(Point(0, 200));
    }

    void draw()
    {
        glColor3f(1,0,0);
        glBegin(GL_LINE_LOOP);
            for(int i=0;i<w.size();++i)
                glVertex2f(w[i].x, w[i].y);
        glEnd();
        glFlush();
    }

    int outcode(Point p)
    {
        int ret = 0;
        if(p.y>200)
            ret|=1;
        ret<<=1;
        if(p.y<0)
            ret|=1;
        ret<<=1;
        if(p.x>200)
            ret|=1;
        ret<<=1;
        if(p.x<0)
            ret|=1;
        cout<<"outcode "<<p.x<<" "<<p.y<<" "<<ret<<endl;
        return ret;
    }

    int edge(int outcode)
    {
        cout<<outcode<<endl;
        if(outcode&8)
            return 2;
        if(outcode&4)
            return 0;
        if(outcode&2)
            return 1;
        if(outcode&1)
            return 3;
    }

    Point findIntersection(Point p, Point q, int edge)
    {
        Point r;
        // (r.y - p.y) /  (q.y - p.y) = (r.x - p.x) / (q.x - p.x)
        switch(edge)
        {
            case 0:
                r.y = 0;
                r.x = (r.y - p.y) * (q.x - p.x) / (q.y - p.y) + p.x;
                return r;
            case 1:
                r.x = 200;
                r.y = (r.x - p.x) * (q.y - p.y) / (q.x - p.x) + p.y;
                return r;
            case 2:
                r.y = 200;
                r.x = (r.y - p.y) * (q.x - p.x) / (q.y - p.y) + p.x;
                return r;
            case 3:
                r.x = 0;
                r.y = (r.x - p.x) * (q.y - p.y) / (q.x - p.x) + p.y;
                return r;

        }
    }
}w;

class Line
{
    public:

    Point a, b;
    Line(Point k = Point(-10, -30), Point l=Point(230, 100))
    {
        a = k;
        b = l;
    }

    void draw()
    {
        glColor3f(0,1,0);
        glBegin(GL_LINES);
            glVertex2f(a.x, a.y);
            glVertex2f(b.x, b.y);
        glEnd;
        glFlush();
    }

    void draw(Point p, Point q)
    {
        cout<<p.x<<" "<<p.y<<" ";
        cout<<q.x<<" "<<q.y<<endl;
        glColor3f(1,0,0);
        glBegin(GL_LINES);
            glVertex2f(p.x, p.y);
            glVertex2f(q.x, q.y);
        glEnd;
        glFlush();
    }

    void clip(Window w)
    {
        clip(a,b,w);
    }

    vector<Point> clipped;
    void clip(Point a, Point b, Window w)
    {
        if(w.outcode(a)==0 && w.outcode(b)==0)
        {
            clipped.push_back(a);
            clipped.push_back(b);
        }

        else if(w.outcode(a)&w.outcode(b))
        {
            // discard
            cout<<a.x<<" "<<a.y<<endl;
            cout<<b.x<<" "<<b.y<<endl;
            cout<<w.outcode(a)<<" "<<w.outcode(b)<<endl;
            cout<<"here"<<endl;
            usleep(1000000);
        }

        else{
            Point newa, newb;
            newa = w.outcode(a)?w.findIntersection(a,b,w.edge(w.outcode(a))):a;
            newb = w.outcode(b)?w.findIntersection(a,b,w.edge(w.outcode(b))):b;
            cout<<newa.x<<" "<<newa.y<<endl;
            cout<<newb.x<<" "<<newb.y<<endl;
            clip(newa, newb, w);
        }
    }
}l;
void idle()
{
    w.draw();
    l.draw();
    l.clip(w);
    glColor3f(0,0,1);
    glBegin(GL_LINE_LOOP);
    for(int i=0;i<l.clipped.size();++i)
    {
        glVertex2f(l.clipped[i].x, l.clipped[i].y);
        cout<<l.clipped[i].x<<" "<< l.clipped[i].y<<endl;
    }
    glEnd();
    glFlush();
}

void keyboard(unsigned char c, int x, int y)
{
}

int main(int argc, char *argv[])
{
    glutInit(&argc, argv);
    glutCreateWindow("lab");
    glutInitWindowSize(500,500);
    glClearColor(0,0,0,1);
    glClear(GL_COLOR_BUFFER_BIT);
    gluOrtho2D(-250, 250, -250, 250);
    glutDisplayFunc(idle);
    // glutIdleFunc(idle);
    glutKeyboardFunc(keyboard);
    glutMainLoop();
}