#include<iostream>
#include<math.h>
#include<GL/glut.h>
using namespace std;

int xc=0, yc=0, r=50;

void plot(int x, int y)
{
    glColor3f(1,0,0);
    glBegin(GL_POINTS);
        glVertex2f(x, y);
        glVertex2f(-x, y);
        glVertex2f(x, -y);
        glVertex2f(-x, -y);
        glVertex2f(y, x);
        glVertex2f(-y, x);
        glVertex2f(y, -x);
        glVertex2f(-y, -x);
    glEnd();
    glFlush();
}

void bres()
{
    int x = 0;
    int y = r;
    int p=3-2*r;
    while(x<y)
    {
        x++;
        plot(x,y);
        if(p<0)
        {
            p+=4*x+6;
        }else
        {
            p+=4*(x-y) + 10;
            y-=1;
        }
    }
}
void mid()
{
    int x=0;
    int y=r*2;
    int p=1-r*2;
    while(x<y)
    {
        x++;
        plot(x,y);
        if(p<0)
        {
            p+=2*x+1;
        }else{
            p+=2*(x-y)+1;
            y-=1;
        }
    }
}

void display()
{
    bres();
    mid();
    glFlush();
}
int main(int argc, char *argv[])
{
	glutInit(&argc,argv);
	glutInitWindowPosition(50,50);
	glutInitWindowSize(500,500);
	glutCreateWindow("LINE");
    gluOrtho2D(-250,250, -250, 250);
	glutDisplayFunc(display);
	glutMainLoop();
	return 0;
}