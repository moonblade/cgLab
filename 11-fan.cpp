#include<GL/glut.h>
#include<iostream>
#include<vector>
#include<math.h>
#define pi 3.14
using namespace std;

// Point class, for x and y
struct Point
{
    int x, y;
    Point(int a=0, int b=0){x=a; y=b;}
};

// To get points on fan, instead of finding the points by hand, angle and radius to points
Point toRadial(int radius, float angle)
{
    angle = angle * pi / 180;
    return Point(radius*cos(angle), radius*sin(angle));
}

// Fan class, has body of fan and speed to rotate in
class Fan
{
public:
    // body of the fan
    vector<Point> body;
    // speed of fan, how much the rotation increases by
    int speed=1;

    Fan()
    {
        body.push_back(Point(0,0));
        body.push_back(toRadial(50, 0));
        body.push_back(toRadial(50, 30));
        body.push_back(Point(0,0));
        body.push_back(toRadial(50, 120));
        body.push_back(toRadial(50, 150));
        body.push_back(Point(0,0));
        body.push_back(toRadial(50, 240));
        body.push_back(toRadial(50, 270));
        body.push_back(Point(0,0));
    }

    void draw()
    {
        // Clear previous screen, rotatef rotates the screen each time draw is done
        glClear(GL_COLOR_BUFFER_BIT);
        glRotatef(speed,0,0,1);
        glColor3f(0,0,0);
        glBegin(GL_LINE_STRIP);
            for(int i=0;i<body.size();++i)
            {
                glVertex2f(body[i].x, body[i].y);
            }
        glEnd();
        glFlush();
    }
}fan;

// to change speed 0-9
void keyboard(unsigned char c, int x, int y)
{
    if(c>='0'&& c<='9')
    {
        fan.speed=c-'0';
    }
}


// idle function is called with a timer so that the animation is slowed down
void idle(int)
{
    fan.draw();
    // glutTimerFunc(delay, function, parameter to pass as int)
    glutTimerFunc(20, idle, 1);
}


// Dummy display
void display()
{
}

void init()
{
    glutInitWindowSize(500,500);
    glutInitWindowPosition(0,0);
    glutCreateWindow("glLab");
    glClearColor(1,1,1,1);
    glClear(GL_COLOR_BUFFER_BIT);
    glutDisplayFunc(display);
    glutKeyboardFunc(keyboard);
    glutTimerFunc(0, idle, 1);
    gluOrtho2D(-250,250,-250,250);
}

int main(int argc, char* argv[])
{
    glutInit(&argc, argv);
    init();
    glutMainLoop();
    return 0;
}