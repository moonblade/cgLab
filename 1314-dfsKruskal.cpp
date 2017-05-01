#include<iostream>
#include<vector>
#include<set>
#include<math.h>
#include<unistd.h>
#include<queue>
#include<GL/glut.h>
#define white 1
#define grey 2
#define black 3
#define rad 20
#define sleepTime 1000*1000
#define max 100
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
    bool visited;
    int state;
    int dist;
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
        visited=false;
        dist=max;
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

        e.push_back(Edge(&v[1], &v[2],1,2,  23));
        e.push_back(Edge(&v[0], &v[1],0,1,  31));
        e.push_back(Edge(&v[1], &v[3],1,3,  24));
        e.push_back(Edge(&v[2], &v[4],2,4,  18));
        e.push_back(Edge(&v[2], &v[6],2,6,  5));
        e.push_back(Edge(&v[5], &v[6],5,6,  9));
        e.push_back(Edge(&v[1], &v[5],1,5,  3));
        e.push_back(Edge(&v[5], &v[7],5,7,  1));
        e.push_back(Edge(&v[0], &v[7],0,7,  10));
        e.push_back(Edge(&v[3], &v[4],3,4,  4));
    }

    void draw()
    {
        glClear(GL_COLOR_BUFFER_BIT);
        for(int i=0; i< v.size(); ++i)
        {
            v[i].draw();
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
        if(v[n].visited)
            return;
        v[n].visited=true;
        v[n].state=grey;
        draw();
        usleep(sleepTime);
        vector<int> neigh = neighbours(n); 
        for (int i=0; i<neigh.size(); ++i)
        {
            // int edge = findEdge(n, neigh[i]);
            // e[edge].state=grey;
            dfs(neigh[i]);
        }
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

    void bfs(int n){
        if(v[n].visited)
            return;
        v[n].visited=true;
        queue<int> Q;
        Q.push(n);
        while(!Q.empty())
        {

        }
    }

    // For kruskal
    vector<int> A;
    set<set<int> > S;
    vector<Edge> sortedEdgeList;
    set<set<int> >::iterator findRep(int node)
    {
        for(auto it = S.begin(); it!=S.end(); ++it)
        {
            int rep = *(it->begin());
            for(auto i= it->begin(); i!=it->end(); ++ i)
            {
                if ((*i)==node)
                    return it;
            }
        }
    }

    void kruskal()
    {
        for(int i=0; i<v.size();++i)
        {
            // makeset i
            set<int> s;
            s.insert(i);
            S.insert(s);
        }
        // sort edges
        vector<Edge> temp = e;
        int size=temp.size();
        for(int i=0;i<size; ++i)
        {
            int min=0;
            for(int j=0;j<temp.size();++j)
            {
                if(temp[j].wt<temp[min].wt)
                    min=j;
            }
            sortedEdgeList.push_back(temp[min]);
            temp.erase(temp.begin()+min);
        }
        // for each, if not in same set, union
        for(int i=0;i<sortedEdgeList.size();++i)
        {
            Edge edge= sortedEdgeList[i];
            set<set<int> >::iterator one = findRep(edge.ui);
            set<set<int> >::iterator two = findRep(edge.vi);
            if(one!=two)
            {
                // merge sets and push
                set<int> s;
                for(auto it = one->begin(); it!=one->end();++it)
                {
                    s.insert(*it);
                }
                
                for(auto it = two->begin(); it!=two->end();++it)
                {
                    s.insert(*it);
                }

                S.insert(s);
                S.erase(one);
                S.erase(two);
                int u = edge.ui;
                int v = edge.vi;
                A.push_back(findEdge(u,v));
                e[findEdge(u,v)].state=grey;
                draw();
                usleep(sleepTime);
            }
        }
        for(int i=0;i<A.size();++i)
        {
            e[A[i]].state=grey;
        }
        draw();
    }

}g;

void display()
{
    g.kruskal();
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