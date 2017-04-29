#include <iostream>
#include <GL/glut.h>
#include <vector>
using namespace std;
int n,outn;
class Point{
public:
	int x,y;
	Point(){}
	Point(int p,int q){
		x=p;
		y=q;
	}
};

vector<Point>o;

Point w[4] = {{20,10},{20,80},{80,80},{80,10}};
Point in[10],outVer[10];

bool isInside(Point p){
        if((p.x>=w[0].x) && (p.x<=w[2].x))       
            if((p.y>=w[0].y)&&(p.y<=w[2].y))
                return true;               
        return false;       
}

void addVertex(Point p){
	outVer[outn] =p;
	outn++;
}

Point getIntersection(Point s,Point p, int i){
	Point in;
	float m;
	if(w[i].x==w[(i+1)%4].x){
		m = (s.y-p.y)/(s.x-p.x);
		in.x = w[i].x;
		in.y=in.x*m+s.y;
	}
	else{           
        m=(p.y-s.y)/(p.x-s.x);   
        in.y=w[i].y;
        in.x=(in.y-s.y)/m;       
    }  
    return in;
}

void clip(Point in[],int n){
	Point p,s,ins;
	for(int i=0; i<4; i++){
		outn = 0;
		s=in[n-1];
		for(int j=0; j<n; j++){
			p=in[j];
			if(isInside(p)){
				if(isInside(s)){
					// addVertex(s);
					addVertex(p);
				}
				else{
					ins = getIntersection(s,p,i);
					addVertex(ins);
					addVertex(p);
				}
			}
			else{
				if(isInside(s)){
					ins = getIntersection(s,p,i);
					addVertex(ins);
				}
				else{
					// ins = getIntersection(s,p,i);
					// Point ins1 = getIntersection(s,p,(i+1)%4);
					// addVertex(ins);
					// addVertex(ins1);
				}
			}
			s=p;
		}
		in=outVer;
		n=outn;

	}
	for(int i=0;i<outn;i++)
		cout<<outVer[i].x<<" " <<outVer[i].y<<endl;
	

}

void display(){
	glColor3f(1,0,0);
	glBegin(GL_LINE_LOOP);
		for(int i=0; i<4; i++)
			glVertex2f(20,10);
			glVertex2f(20,80);
			glVertex2f(80,80);
			glVertex2f(80,10);
	glEnd();
	glColor3f(0,1,0);
	glBegin(GL_LINE_LOOP);
		for(int i=0; i<n; i++)
			glVertex2f(in[i].x,in[i].y);
	glEnd();
	clip(in,n);
	glColor3f(1,1,1);

	glBegin(GL_LINE_LOOP);
		for(int i=0; i<outn; i++){
			glVertex2f(outVer[i].x,outVer[i].y);
			
		}
	glEnd();

	glFlush();
}
int main(int argc, char *argv[]){
	// int n;
	cout<<"Enter no of points in the polygon";
	cin>>n;
	cout<<"Enter points"<<endl;
	for(int i=0; i<n; i++){
		cin>>in[i].x>>in[i].y;
	}
	for(int i=0; i<n; i++){
		cout<<in[i].x<<in[i].y;
	}
	glutInit(&argc,argv);
	glutInitWindowSize(500,500);
	glutInitWindowPosition(0,0);
	glutCreateWindow("Polygon Clipping");
	gluOrtho2D(0,100,0,100);
	glClearColor(0,0,0,0);
    glClear(GL_COLOR_BUFFER_BIT);
   
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}