#include<iostream>
#include<math.h>
#include<vector>
#include<unistd.h>
#include<GL/glut.h>
#define w2 250
#define rad 30
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
};
void circle(Point center, int radius)
{
    glBegin(GL_LINE_STRIP);
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
    Node(int i, Point p){
        id=i;
        position = p;
        state=white;
    }
    void draw(){
        switch(state)
        {
            case white:glColor3f(1,1,1);break;
            case grey:glColor3f(1,0,0);break;
            case black:glColor3f(0,1,0);break;
        }
        circle(position, rad);
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
    }     
};
class Set{
public:
    vector<int> set;
    Set(){}
    Set(int i)
    {
        set.push_back(i);
    }
    Set unite(Set b)
    {
        Set c;
        for(int i=0; i<set.size(); ++i)
            c.set.push_back(set[i]);
        
        for(int i=0; i<b.set.size(); ++i)
            c.set.push_back(b.set[i]);
        return c;
    }
    int rep(int key)
    {
        for(int i=0;i<set.size();++i)
        {
            if(set[i]==key)
                return set[0];
        }
        return -1;
    }
};
class SetSet{
public:
    vector<Set> s;
    SetSet(int noOfNodes)
    {
        for(int i=0;i<noOfNodes;++i)
            s.push_back(Set(i));
    }
    int rep(int key)
    {
        for(int i=0;i<s.size();++i)
        {
            if(s[i].rep(key)>-1)
                return i;
        }
        return -1;
    }
    void unite(int node1, int node2)
    {
        int a=rep(node1);
        int b=rep(node2);
        Set k = s[a].unite(s[b]);
        s.erase(s.begin() + rep(node1));
        s.erase(s.begin() + rep(node2));
        s.push_back(k);
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
        edges.push_back(Edge(2,5,3));
        edges.push_back(Edge(5,4,2));
        edges.push_back(Edge(1,4,1));
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

    void sortEdges(){
        for(int i=0;i<edges.size();++i)
            for(int j=0;j<edges.size();++j)
                if(edges[i].wt<edges[j].wt)
                {
                    Edge temp = edges[i];
                    edges[i]=edges[j];
                    edges[j]=temp;
                }
        for(int i=0;i<edges.size();++i)
        {
            cout<<edges[i].wt<<" ";
        }
    }
    void kruskal(){
        SetSet s = SetSet(nodes.size());
        sortEdges();

        for(int i=0;i<edges.size();++i)
        {
            int urep = s.rep(edges[i].u);
            int vrep = s.rep(edges[i].v);
            if(urep!=vrep && urep>-1 && vrep>-1)
            {
                s.unite(edges[i].u, edges[i].v);
                edges[i].state=grey;
                nodes[edges[i].u].state=grey;
                nodes[edges[i].v].state=grey;
                draw();
                usleep(1000000);
            }
        }
    }

}g;
void display()
{
    g.draw();
    g.kruskal();
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