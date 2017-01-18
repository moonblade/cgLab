/*
Algorithm DDA Line
------------------
to draw line from sx, sy to ex, ey
find step, ie max change in either x or y
step = maximum(|ex-sx|,|ey-sy|)

find change per unit x and per unit y of step
dx = (ex-sx)/step
dy = (ey-sy)/step

change by dx and dy at every step starting from sx,sy
x = sx
y = sy
for i in 1 to step
	print(x,y)
	x += dx
	y += dy


Algorith Bressenham
-------------------
to draw line from sx, sy to ex, ey
dx = ex - sx
dy = ey - sy

if(ex-sx>0)
	inc=1
else
	inc=-1

p = 2*dx - dy
x=sx
y=sy
while(x<=ex)
	plot(x,y)
	x+=1
	if p<0
		p+=2*dy
	else
		y+=inc
		p+=2*(dy-dx)

 */
#include<iostream>
#include<math.h>
#include<GL/glut.h>
using namespace std;
float startx,starty;
float endx,endy;
void displayLine(void)
{
	glClearColor(1,1,1,1);
    glClear(GL_COLOR_BUFFER_BIT);
    glLineWidth(2.5);
	glColor3f(0.0,0.0,0.0);
	glBegin(GL_LINES);
	{
        glVertex3f(startx, starty, 0);
        glVertex3f(endx, endy, 0);
	}
	glEnd();
	glFlush();
}
float max(float a, float b)
{
	if (a>b)
		return a;
	return b;
}
void displayDDALine(void)
{
	glClearColor(1,1,1,1);
    glClear(GL_COLOR_BUFFER_BIT);
    glLineWidth(2.5);
	glColor3f(0.0,0.0,0.0);
	gluOrtho2D(0 , 250 , 0 , 250);

	float step=max(abs(startx-endx),abs(starty-endy));
	float dx=(endx-startx)/step;
	float dy=(endy-starty)/step;
	float x=startx;
	float y=starty;

	glBegin(GL_POINTS);
	{
		for(int i=0;i<step;++i)
		{
			glVertex2f(x,y);
			// cout<<x<<" "<<y<<endl;
			x+=dx;
			y+=dy;
		}	
	}
	glEnd();
	glFlush();
}

void displayBressenhamLine(void)
{
	glClearColor(1,1,1,1);
    glClear(GL_COLOR_BUFFER_BIT);
    glLineWidth(2.5);
	glColor3f(0.0,0.0,0.0);
	gluOrtho2D(0 , 250 , 0 , 250);

	float dx = endx - startx;
	float dy = endy - starty;

	float inc=1;
	if(endx-startx<0)
		inc=-1;

	float p = 2*dx - dy;
	float x=startx;
	float y=starty;
	glBegin(GL_POINTS);
	{
		while(x<=endx){
			glVertex2f(x,y);
			x+=1;
			if(p<0)
				p+=2*dy;
			else{
				y+=inc;
				p+=2*(dy-dx);
			}
		}
	}
	glEnd();
	glFlush();
}

int main(int argc, char *argv[])
{
	startx=0;
	starty=0;
	endx=75;
	endy=50;

	glutInit(&argc,argv);
	glutInitWindowPosition(50,50);
	glutInitWindowSize(500,500);
	glutCreateWindow("LINE");
	// glutDisplayFunc(displayLine);
	// glutDisplayFunc(displayDDALine);
	glutDisplayFunc(displayBressenhamLine);
	glutMainLoop();
	return 0;
}