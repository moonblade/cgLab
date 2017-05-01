#include<iostream>
#include<vector>
#include<GL/glut.h>
using namespace std;

class Point
{
    public:
    int x, y;
    Point(int a=0,int b=0){
        x=a;
        y=b;
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

    bool inside(Point p, int edge)
    {
        switch(edge)
        {
            case 0:
                return p.y>0;
            case 1:
                return p.x<200;
            case 2:
                return p.y<200;
            case 3:
                return p.x>0;
        }
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

class Polygon
{
    public:
    vector<Point> poly;
    Polygon(){
        poly.push_back(Point(-10,-30));
        poly.push_back(Point(180,20));
        poly.push_back(Point(180,20));
        poly.push_back(Point(230,100));
        poly.push_back(Point(100,230));
    }

    void draw()
    {
        glColor3f(0,0,1);
        glBegin(GL_LINE_LOOP);
            for(int i=0;i<poly.size();++i)
                glVertex2f(poly[i].x, poly[i].y);
        glEnd();
        glFlush();
    }

    vector<Point> clip(Window w){
        vector<Point> out = poly;
        for(int j=0;j<w.w.size(); ++j)
        {
            vector<Point> in = out;
            out.clear();
            Point s = in[in.size()-1];
            for(int i=0;i<in.size();++i)
            {
                Point p = in[i];
                if(w.inside(p,j))
                {
                    if(!w.inside(s,j))
                    {
                        out.push_back(w.findIntersection(s,p,j));
                    }
                    out.push_back(p);
                }else if(w.inside(s,j))
                    out.push_back(w.findIntersection(s,p,j));
                s=p;
            }
        }
        return out;
    }
}p;

void display()
{
    p.draw();
    w.draw();
}

void keyboard(unsigned char c, int x, int y)
{
    glClear(GL_COLOR_BUFFER_BIT);
    w.draw();
    p.poly = p.clip(w);
    p.draw();
}
int main(int argc, char *argv[])
{
    glutInit(&argc, argv);
    glutInitWindowSize(500, 500);
    glutCreateWindow("lab");
    gluOrtho2D(-250, 250, -250, 250);
    glClearColor(0,0,0,1);
    glClear(GL_COLOR_BUFFER_BIT);
    glutDisplayFunc(display);
    glutKeyboardFunc(keyboard);
    glutMainLoop();
}