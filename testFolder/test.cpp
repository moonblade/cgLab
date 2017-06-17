#include<iostream>
#include<GL/glut.h>
#include<math.h>
#include<vector>
#define w2 250
#define white 0
#define red 1
#define blue 2
#define rads 30
using namespace std;


class point {
	public:
		int x,y;
		//point(){};
		point(int a=0,int b=0){
			x=a;
			y=b;
		}
};
void circle(point centre,int r){
		glBegin(GL_LINE_STRIP);
	for(int i=0;i<360;i++){
		float theta=i*3.14/180;
		glVertex2f(centre.x+r*cos(theta),centre.y+r*sin(theta));

	}
	glEnd();
}

void line(point a,point b){
	glBegin(GL_LINES);
	glVertex2f(a.x,a.y);
	glVertex2f(b.x,b.y);
	glEnd();
}
class node{
public:
	int id;
	point position;
	int state;

	node(int i,point p){
		id=i;
		position=p;
		state=white;
	}

	void draw(){
		//glBegin()
		switch(state){
			case white:glColor3f(0,1,0);break;
			case red:glColor3f(1,0,0);break;
			case blue:glColor3f(0,0,1);break;
		}
		circle(position,rads);
	}
	bool visited(){
		return state;
	}
};

class edge{
public:
	int u,v,wt;
	int state;
	edge(int x,int y,int z){
		u=x;
		v=y;
		wt=z;
		state=white;
	}
	void draw(vector<node> nodes){
		switch(state){
			case white:glColor3f(1,1,1);break;
			case red:glColor3f(1,0,0);break;
			case blue:glColor3f(0,0,1);break;
		}
		line(nodes[u].position,nodes[v].position);
	}
	bool has(int node){
		return u==node||v==node;
		
	}
	bool other(int node){
		if(u==node)
			return v;
		else return u;
	}
};

class graph{
public:
	vector<node>nodes;
	vector<edge>edges;
	graph(){
		int i=0;
		nodes.push_back(node(i++,point(0,0)));
		nodes.push_back(node(i++,point(-50,-50)));
		nodes.push_back(node(i++,point(-150,-150)));
		nodes.push_back(node(i++,point(-75,-150)));
		nodes.push_back(node(i++,point(50,-50)));
		nodes.push_back(node(i++,point(25,-150)));
		//edges.push_back(edge(0,1,0));
		//edges.push_back(edge(1,2,0));
		//edges.push_back(edge(1,3,0));
	//	edges.push_back(edge(0,4,0));
//		edges.push_back(edge(4,5,0));
	}
	void draw(){
		for(int i=0;i<nodes.size();i++){
			nodes[i].draw();
		}
		for(int i=0;i<edges.size();i++){
			edges[i].draw(nodes);
		}
		glFlush();

	}
}g;

void display(){
	g.draw();
	glFlush();
}

void init(){
	glutCreateWindow("graph");
	glutInitWindowSize(2*w2,2*w2);
	gluOrtho2D(-w2,w2,-w2,w2);
	glClear(GL_COLOR_BUFFER_BIT);
	glClearColor(0,0,0,1);
}

int main(int argc,char** argv){
	glutInit(&argc,argv);
	init();
	glutDisplayFunc(display);
	glutMainLoop();
	return 1;
}