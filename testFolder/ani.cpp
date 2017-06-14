#include "iostream"
#include "GL/glut.h"
using namespace std;
 
class Fan{
public:

};

void display(){
	glFlush();
}

int main(int argc, char *argv[])
{
	glutInit(&argc,argv);
	glutCreateWindow("Window");
	glutInitWindowSize(500,500);
	glutInitWindowPosition(0,0);
	glClearColor(1,1,1,1);
	glClear(GL_COLOR_BUFFER_BIT);
	gluOrtho2D(-250,250,-250,250);
	glutDisplayFunc(display);
	glutMainLoop();
	return 0;
}