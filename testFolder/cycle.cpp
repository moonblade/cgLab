#include<iostream>
#include<vector>
#include<GL/glut.h>
#include<math.h>
#include<unistd.h>
using namespace std;
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
class cycle
{
public:
    vector<Point> body;
    Point w[2];
    Point position;
    int rotation = 0;
    int rad;
    cycle()
    {
        body.push_back(Point(0,0));
        body.push_back(Point(50,0));
        body.push_back(Point(100,0));

        rad=20;
        w[0] = Point(0,0);
        w[1] = Point(100,0);

    }

    void drawWheel(Point p)
    {
        glBegin(GL_LINE_STRIP);
        for(int i=0;i<360;++i)
        {
            float theta = 3.14*i/180;
            Point q(rad*cos(theta),rad*sin(theta));   
            q = q.translate(position);
            q = q.translate(p);
            q = q.rotate(body[1].translate(position), rotation);
            q.draw();
            Point center = p.translate(position).rotate(body[1].translate(position), rotation);
            if((i+position.x)%30==0)
                center.draw();
        }
        glEnd();
    }

    void draw()
    {
        glBegin(GL_LINE_STRIP);
        for(int i=0;i<body.size(); ++i)
        {
            Point q = body[i].translate(position);
            q = q.rotate(body[1].translate(position), rotation);
            q.draw();
        }
        glEnd();

        drawWheel(w[0]);
        drawWheel(w[1]);
    }
}c;

void display()
{
    c.draw();
    glFlush();
}
int i=0;
void step()
{
    glClear(GL_COLOR_BUFFER_BIT);
    i++;
    if(i<50)
    {
        c.position.x++;
    }
    else if(i<100)
    {
        c.rotation=-45;
        c.position.x++;
        c.position.y++;
    }
    
    else if(i<150)
    {
        c.rotation=45;
        c.position.x++;
        c.position.y--;
    }
    
    else
    {
        c.rotation=0;
        c.position.x++;
    }


    c.draw();
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