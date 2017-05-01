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

// Wheel class, has a radius and a center
class Wheel {
public:
    Point center;
    int radius;
    Wheel(){}
    Wheel(int x, int y, int r)
    {
        center=Point(x,y);
        radius=r;
    }

    // Draw the weel
    void draw(Point translate)
    {
        //simple way to get how much the wheel has rotated, - is the clockwise direction
        int rotation=-translate.x; 
        // push matrix is used so that only the wheel is rotated and none of the others are affected
        // push means save what all have been drawn till now so that they wont be affected.
        glPushMatrix();
        int newX = center.x + translate.x;
        int newY = center.y + translate.y;
        // rotate about center, TRT', The order needs to be reversed for it to work
        glTranslatef(newX, newY, 0);
        glRotatef(rotation, 0, 0, 1);
        glTranslatef(-newX, -newY, 0);

        glBegin(GL_LINE_LOOP);
            glVertex2f(newX,newY);
            for(int i=0;i<360;++i)
            {
                float theta = i * pi / 180;
                int x = newX + radius * cos(theta);
                int y = newY + radius * sin(theta);
                glVertex2f(x, y);
            }
        glEnd();
        glPopMatrix();
    }
};
// Cycle class, has body and wheels
class Cycle
{
public:
    // body of cycle
    vector<Point> body;
    Wheel a,b;
    Point translate;
    float rotation;

    // Where the cycle should move to
    vector<Point> path;
    int pathNow=1;

    Cycle(int y=0)
    {
        // path for the cycle
        path.push_back(Point(-200, 0));
        path.push_back(Point(-100, 0));
        path.push_back(Point(0, 100));
        path.push_back(Point(100, 0));
        path.push_back(Point(200, 0));

        // start the cycle at the start of path
        translate.y=y;
        translate.x=path[0].x;

        a=Wheel(0,0,10);
        b=Wheel(40,0,10);

        // A shitty body 
        body.push_back(Point(0,0));
        body.push_back(Point(10,20));
        body.push_back(Point(30,20));
        body.push_back(Point(40,0));
        body.push_back(Point(30,20));
        body.push_back(Point(20,0));
        body.push_back(Point(10,20));
        body.push_back(Point(20,0));
        body.push_back(Point(0,0));
    }

    void step(int k=1)
    {
        // increasing translate is the step
        Point currentPosition = Point(body[0].x + translate.x, body[0].y + translate.y);
        if(path[pathNow].x > currentPosition.x)
            translate.x+=k;
        if(path[pathNow].x < currentPosition.x)
            translate.x-=k;
        if(path[pathNow].y > currentPosition.y)
            translate.y+=k;
        if(path[pathNow].y < currentPosition.y)
            translate.y-=k;
        
        // find rot angle by inverse tan of path and current position
        rotation = atan2(path[pathNow].y - path[pathNow-1].y, path[pathNow].x - path[pathNow-1].x);

        // if you reach the end, go to next two points
        if(currentPosition.x == path[pathNow].x)
        {
            if(pathNow+1<path.size())
                pathNow++;
        }
    }

    void draw()
    {
        Point currentPosition = Point(body[0].x + translate.x, body[0].y + translate.y);
        // Clear previous screen
        glColor3f(0,0,0);
        
        glPushMatrix();
        glTranslatef(currentPosition.x, currentPosition.y, 0);
        glRotatef(rotation * 180 / pi,0,0,1);
        glTranslatef(-currentPosition.x, -currentPosition.y, 0);

        a.draw(translate);
        b.draw(translate);
        glBegin(GL_LINE_STRIP);
            for(int i=0;i<body.size();++i)
            {
                glVertex2f(body[i].x + translate.x, body[i].y + translate.y);
            }
        glEnd();
        glPopMatrix();
        glFlush();
    }
}cycle;

// idle function is called with a timer so that the animation is slowed down
void idle(int)
{
    
    glClear(GL_COLOR_BUFFER_BIT);
    cycle.draw();
    cycle.step(2);
    // glutTimerFunc(delay, function, parameter to pass as int)
    glutTimerFunc(50, idle, 1);
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