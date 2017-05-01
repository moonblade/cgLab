#include<iostream>
#include<vector>
#include<set>
#include<math.h>
#include<unistd.h>
#include<GL/glut.h>
#define white 1
#define grey 2
#define black 3
#define rad 20
#define sleepTime 1000*1000
using namespace std;
class Point
{
    public:
    int x, y;
    Point(int a=0, int b=0){
        x=a; 
        y=b;
    }
};

int color[3];
int* getColor(int code)
{
    if(code==white)
    {
        color[0]=0;
        color[1]=1;
        color[2]=0;
    }
    else if(code==grey)
    {
        color[0]=0;
        color[1]=0;
        color[2]=1;
    }
    else if(code==black)
    {
        color[0]=1;
        color[1]=0;
        color[2]=0;
    }
    return color;
}

void circle(Point center, int radius=rad)
{
    glBegin(GL_LINE_LOOP);
        for(int i=0;i<360; ++i)
        {
            float theta = i * 3.14 / 180;
            glVertex2f(center.x + radius*cos(theta), center.y + radius*sin(theta));
        }
    glEnd();
}

void line(Point one, Point two)
{
    glBegin(GL_LINES);
        glVertex2f(one.x, one.y);
        glVertex2f(two.x, two.y);
    glEnd();
}

class Node
{  
    public:
    int state;
    int id;
    Point position;
    void draw()
    {
        int *color = getColor(state);
        glColor3f(color[0], color[1], color[2]);
        circle(position);
    }
    void print()
    {
        cout<<id<<" : "<<position.x<<" "<< position.y<<endl;
    }
    Node(int i, Point pos)
    {
        id = i;
        position= pos;
        state=white;
    }
};

class Edge
{
    public:
    int state;
    Node* u, *v;
    int ui, vi;
    int wt;
    void draw()
    {
        int* color = getColor(state);
        glColor3f(color[0], color[1], color[2]);
        line(u->position, v->position);
    }
    Edge(Node* ua, Node* va, int uia, int via, int wta)
    {
        state=white;
        u=ua;
        v=va;
        ui=uia;
        vi=via;
        wt=wta;
    }
    bool has(int node)
    {
        return ui==node || vi==node;
    }
    int other(int node)
    {
        if (ui==node)
            return vi;
        else
            return ui;
    }
};

class Graph
{
    public:
    vector<Node> v;
    vector<Edge> e;
    set<int> visitedNodes;
    Graph(){
        int i=0;
        v.push_back(Node(i++, Point(-200, 0)));
        v.push_back(Node(i++, Point(0, 0)));
        v.push_back(Node(i++, Point(200, 0)));
        v.push_back(Node(i++, Point(0, 200)));
        v.push_back(Node(i++, Point(200, 200)));
        v.push_back(Node(i++, Point(0, -200)));
        v.push_back(Node(i++, Point(200, -200)));
        v.push_back(Node(i++, Point(-200, -200)));

        e.push_back(Edge(&v[1], &v[2],1,2,  200));
        e.push_back(Edge(&v[0], &v[1],0,1,  200));
        e.push_back(Edge(&v[1], &v[3],1,3,  200));
        e.push_back(Edge(&v[2], &v[4],2,4,  200));
        e.push_back(Edge(&v[2], &v[6],2,6,  200));
        e.push_back(Edge(&v[5], &v[6],5,6,  200));
        e.push_back(Edge(&v[1], &v[5],1,5,  200));
    }

    bool visited(int i)
    {
        return visitedNodes.find(i)!=visitedNodes.end();
    }
    void draw()
    {
        glClear(GL_COLOR_BUFFER_BIT);
        for(int i=0; i< v.size(); ++i)
            v[i].draw();
        {
        }
        for(int i=0; i< e.size(); ++i)
        {
            e[i].draw();
        }
        glFlush();
    }

    int findEdge(int u, int v)
    {
        for(int i=0;i<e.size();++i)
        {
            if(e[i].has(u) && e[i].has(v))
                return i;
        }
    }

    vector<int> neighbours(int node)
    {
        vector<int> neigh;
        for(int i=0;i<e.size();++i)
        {
            if(e[i].has(node))
                neigh.push_back(e[i].other(node));
        }
        return neigh;
    }

    void dfs(int n)
    {
        if(visited(n))
            return;
        visitedNodes.insert(n);
        v[n].state=grey;
        draw();
        usleep(sleepTime);
        vector<int> neigh = neighbours(n); 
        for (int i=0; i<neigh.size(); ++i)
        {
            int edge = findEdge(n, neigh[i]);
            e[edge].state=grey;
            dfs(neigh[i]);
            draw();
        }
        // usleep(sleepTime);
        v[n].state=black;
        draw();
        usleep(sleepTime);
    }

    void dfsWrapper()
    {
        for(int i=0;i<v.size();++i)
        {
            dfs(i);
        }
    }


}g;

void display()
{
    g.dfsWrapper();
}

int main(int argc, char *argv[])
{
    glutInit(&argc, argv);
    glutInitWindowSize(500,500);
    glClearColor(0,0,0,1);
    glLineWidth(5);
    glClear(GL_COLOR_BUFFER_BIT);
    glutCreateWindow("Lab");
    glutDisplayFunc(display);
    gluOrtho2D(-250, 250, -250, 250);
    glutMainLoop();
    return 1;
}