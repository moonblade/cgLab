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
        ret<<=1;
        return ret;
    }

}w;

class Line
{
    public:

    Point a, b;
    Line(Point k = Point(10, 30), Point l=Point(230, 100))
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

    void clip(Point a, Point b, Window w)
    {
        if(w.outcode(a)==0 && w.outcode(b)==0)
        {
            cout<<"inside ";
            cout<<a.x<<" "<<a.y<<" ";
            cout<<b.x<<" "<<b.y<<endl;
            draw(a,b);
        }

        else if(w.outcode(a)&w.outcode(b)!=0)
        {
            // discard
            cout<<a.x<<" "<<a.y<<endl;
            cout<<b.x<<" "<<b.y<<endl;
            cout<<w.outcode(a)<<" "<<w.outcode(b)<<endl;
            cout<<"here"<<endl;
            usleep(1000000);
        }

        else{
            Point mid;
            mid.x = (a.x + b.x)/2;
            mid.y = (a.y + b.y)/2;
            cout<<mid.x<<" "<<mid.y<<endl;
            if(mid.x==a.x || mid.y==a.y)
                return;
            clip(a, mid, w);
            clip(mid, b, w);
        }
    }
}l;
void idle()
{
    w.draw();
    l.draw();
    l.clip(w);
}

void keyboard(unsigned char c, int x, int y)
{
    l.clip(w);
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