#include<iostream>
#define n 4
using namespace std;
class matrix
{
    public:
    int m[n][n];
    int o[n][n];
    int a[n+1] = {2,3,6,4,5};
    matrix()
    {
        for(int i=0;i<n;++i){
            for(int j=i;j<n;++j)
                m[i][j]=65535;
            m[i][i]=0;
        }
    }

    int get(int i, int j)
    {
        return m[i][j];
    }

    int get(int i, int j, int k)
    {
        return m[i][k-1] + m[k][j] + a[i]*a[k]*a[j+1];
    }

    void calc()
    {
        for(int l=2;l<=n;++l)
        {
            for(int i=0;i<n-l+1;++i)
            {
                int j=i+l-1;
                for(int k=i+1;k<=j;++k)
                {
                    
                    // cout<<i<<k<<j<<" "<<get(i,j,k)<<endl;
                    if(get(i,j) > get(i,j,k))
                    {
                        o[i][j] = k;
                        m[i][j] = get(i,j,k);
                    }
                }
            }
        }
    }

    void print()
    {
        for(int i=0;i<n;++i)
        {
            for(int j=0;j<n;++j)
            {
                cout<<m[i][j]<<" ";
            }
            cout<<endl;
        }
        cout<<endl;
        
        for(int i=0;i<n;++i)
        {
            for(int j=0;j<n;++j)
            {
                cout<<o[i][j]<<" ";
            }
            cout<<endl;
        }
        cout<<endl;

    }

    void ord()
    {
        order(0, n-1);
    }
    void order(int i, int j)
    {
        if(i==j)
        {
            cout<<i;
            return;
        }
        cout<<"(";
        order(i, o[i][j]-1);
        order(o[i][j], j);
        cout<<")";
    }
}m;

int main()
{
    m.calc();
    m.print();
    m.ord();
}