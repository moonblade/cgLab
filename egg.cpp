#include<iostream>
#include<vector>
#include<GL/glut.h>
#include<math.h>
#include<unistd.h>
using namespace std;

float eg[]={1,0,0};
float bac[]={1,1,1};
float chick[]={0,1,1};
float max(float a, float b)
{
    return a>b?a:b;
}

class Point{
    public:
        int x,y;
        Point(int a=0, int b=0){
            x=a;
            y=b;
        }
        void draw()
        {
            glVertex2f(x,y);
        }
        bool same(Point b)
        {
            return x==b.x&&y==b.y;
        }
        Point neg()
        {
            return Point(-x, -y);
        }
        Point translate(Point pos)
        {
            return Point(x+pos.x, y+pos.y);
        }
        Point rotate(Point about, int angle)
        {
            float theta = 3.14*angle/180;
            Point p = translate(about.neg());
            Point q;
            q.x = p.x * cos(theta) + p.y*sin(theta);
            q.y = (p.y*cos(theta)) +(-p.x*sin(theta));
            p=q;
            p = p.translate(about);
            return p;
        }
        void print()
        {
            cout<<x<<" "<<y<<endl;
        }
};
class eggPiece{
public:
    vector<Point> body;
    Point s, e;
    Point pos;
    float steph, dx, dy;
    eggPiece(){};
    eggPiece(vector<Point> b, Point a, Point c){
        body = b;
        s = a;
        e = c;

        pos = s;
        dx = e.x - s.x;
        dy = e.y - s.y;
        steph = max(abs(dx), abs(dy));
        dx/=steph;
        dy/=steph;
    }
    void step()
    {
        if(!pos.same(e))
        {
            pos.x+=dx;
            pos.y+=dy;
        }
    }
    void draw()
    {
        glColor3fv(bac);
        glBegin(GL_POLYGON);
            for(int i=0;i<body.size();++i)
            {
                body[i].translate(pos).draw();
            }
        glEnd();
        glColor3fv(eg);
        glBegin(GL_LINE_STRIP);
            for(int i=0;i<body.size();++i)
            {
                body[i].translate(pos).draw();
            }
        glEnd();
        glFlush();
    }
};
vector<eggPiece> egg;
void display()
{
    glFlush();
}
int i=0;
void step()
{
    for(int i=0;i<egg.size();++i)
    {
        egg[i].draw();
        egg[i].step();
    }
    usleep(200000);
    glClear(GL_COLOR_BUFFER_BIT);
}
void makeEgg()
{
    vector<Point> chick;
    chick.push_back(Point(0, 10));
    chick.push_back(Point(20, 10));
    chick.push_back(Point(20, 30));
    chick.push_back(Point(0, 30));
    chick.push_back(Point(0, 22));
    chick.push_back(Point(-5, 20));
    chick.push_back(Point(0, 18));
    chick.push_back(Point(0, 10));
    egg.push_back(eggPiece(chick, Point(20,-10), Point(10,-10)));

    vector<Point> temp;
    temp.push_back(Point(0,0));
    temp.push_back(Point(50,0));
    temp.push_back(Point(25,-25));
    temp.push_back(Point(0,0));
    egg.push_back(eggPiece(temp, Point(0,0), Point(0,0)));
    temp.clear();

    temp.push_back(Point(0,0));
    temp.push_back(Point(25,0));
    temp.push_back(Point(25,25));
    temp.push_back(Point(0,0));
    egg.push_back(eggPiece(temp, Point(0,0), Point(-50,50)));
    temp.clear();

    temp.push_back(Point(25,0));
    temp.push_back(Point(25,25));
    temp.push_back(Point(50,0));
    temp.push_back(Point(25,0));
    egg.push_back(eggPiece(temp, Point(0,0), Point(50,50)));


}
int main(int argc, char *argv[])
{
    makeEgg();
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