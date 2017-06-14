#include<iostream>
#include<math.h>
#include<vector>
#include<unistd.h>
#include<GL/glut.h>
#define w2 250
#define rad 30
#define max 99
#define white 0
#define grey 1
#define black 2
using namespace std;
class Point{
    public:
    int x,y;
    Point(int a=0, int b=0)
    {
        x=a; y=b;
    }
    Point middle(Point b)
    {
        return Point((x+b.x)/2, (y+b.y)/2);
    }
};
void circle(Point center, int radius)
{
    glBegin(GL_TRIANGLE_FAN);
    for(int i=0;i<360; ++i)
    {
        float theta = i*3.14/180;
        glVertex2f(center.x + radius*cos(theta), center.y + radius*sin(theta));
    }
    glEnd();
}
void line(Point a, Point b)
{
    glBegin(GL_LINES);
        glVertex2f(a.x, a.y);
        glVertex2f(b.x, b.y);
    glEnd();
}
class Node{
public:
    int id;
    Point position;
    int state;
    int pi;
    int dist;
    Node(int i, Point p){
        id=i;
        position = p;
        state=white;
        dist=max;
    }
    void draw(){
        switch(state)
        {
            case white:glColor3f(1,1,1);break;
            case grey:glColor3f(1,0,0);break;
            case black:glColor3f(0,1,0);break;
        }
        circle(position, rad);

        glColor3f(0,0,1);
        glRasterPos2i(position.x, position.y-5);
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, dist%10+'0');
        glRasterPos2i(position.x-18, position.y-5);
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, (dist/10)%10+'0');
    }
    bool visited(){
        return state;
    }
};

class Edge
{
public:
    int wt,u,v;
    int state;
    Edge(int x, int y, int w)
    {
        wt=w;
        u=x;
        v=y;
        state=white;
    } 
    void draw(vector<Node> nodes){
        switch(state)
        {
            case white:glColor3f(1,1,1);break;
            case grey:glColor3f(1,0,0);break;
            case black:glColor3f(0,1,0);break;
        }
        line(nodes[u].position, nodes[v].position);
        glColor3f(0,0,1);
        Point middle = nodes[u].position.middle(nodes[v].position);
        glRasterPos2i(middle.x, middle.y);
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, wt+'0');
    }  

    bool tighten(int node, vector<Node> &nodes)
    {
        int oth = other(node);
        if(nodes[oth].state!=black && nodes[oth].dist>nodes[node].dist + wt)
        {
            nodes[oth].dist = nodes[node].dist + wt;
            nodes[oth].pi = node;
            nodes[oth].state = grey;
            return true;
        }
        return false;
    }
    bool has(int node)
    {
        return u==node||v==node;
    } 

    int other(int node)
    {
        if(u==node)
            return v;
        else return u;
    }  
};
class Graph{
    public:
    vector<Node> nodes;
    vector<Edge> edges;
    Graph(){
        int i=0;
        nodes.push_back(Node(i++,Point(0,0)));
        nodes.push_back(Node(i++,Point(100,0)));
        nodes.push_back(Node(i++,Point(200,0)));
        nodes.push_back(Node(i++,Point(0,-100)));
        nodes.push_back(Node(i++,Point(100,-100)));
        nodes.push_back(Node(i++,Point(200,-100)));
        edges.push_back(Edge(0,1,2));
        edges.push_back(Edge(1,2,3));
        edges.push_back(Edge(0,4,5));
        edges.push_back(Edge(0,3,1));
        edges.push_back(Edge(3,4,4));
        // edges.push_back(Edge(2,5,3));
        edges.push_back(Edge(5,4,2));
        edges.push_back(Edge(1,4,1));
    }

    int getMinGrey(){
        int min = 99;
        int mini = -1;
        for(int i=0;i<nodes.size();++i)
            if(nodes[i].dist<min && nodes[i].state==grey){
                mini=i;
                min=nodes[i].dist;
            }
        return mini;
    }

    void draw(){
        for(int i=0;i<nodes.size();++i)
        {
            nodes[i].draw();
        }
        for(int i=0;i<edges.size();++i)
        {
            edges[i].draw(nodes);
        }
        glFlush();
    }

    void djikstra(int a)
    {
        nodes[a].state=grey;
        nodes[a].dist=0;
        draw();
        usleep(1000000);
        int p;
        while((p=getMinGrey())>-1)
        {
            for(int i=0;i<edges.size();++i)
            {
                if(edges[i].has(p))
                {
                    if(edges[i].tighten(p, nodes))
                    {
                        draw();
                        usleep(1000000);
                    }
                }
            }
            nodes[p].state=black;
            draw();
            usleep(1000000);
        }        
    }
}g;
void display()
{
    g.draw();
    g.djikstra(2);
    glFlush();
}
void idle(){

}
int main(int argc, char *argv[])
{
    glutInit(&argc, argv);
    glutCreateWindow("window");
    glutInitWindowSize(2*w2,2*w2);
    gluOrtho2D(-w2,w2,-w2,w2);
    glClearColor(0,0,0,1);
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(1,0,1);
    glutDisplayFunc(display);
    glutIdleFunc(idle);
    glutMainLoop();
    return 1;
}