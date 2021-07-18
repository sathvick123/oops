#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <bits/stdc++.h>

using namespace std;

class Graph
{
    private:
    int c,n;
    int* currency; //array to store colour of the currency 
    int** colour;  //array to store whether two colours can exchange thier currency
    double** adjm; //adjacency matrix to store the weights only when there is direct and valid edge

    public:
    void create(int N);//creates adjaceny matrix of required size and updates the size bits
    void colourcr(int col);//creates a colour matrix 
    void coldata(int a,int b);//updates the colour matrix of given indices
    void currency_updt(int i,int j);//updates the currency matrix of given index
    void addedge(int a,int b,double w);//adds only valid edge of given weight in adjacency matrix
    double max_product(int src,int dest,int mul);        
};
void Graph::colourcr(int col)
{
    c=col;
    colour=new int*[col];
    for(int i=0;i<col;i++)
    {
        colour[i]=new int[col];
    }
     for(int i=0;i<col;i++)
    {
        for(int j=0;j<col;j++)
        {
            if(j!=i)
            {
                colour[i][j]=0;
            }
            else
            {
                colour[i][j]=1;
            }
        }
    }
   
}
void Graph::create(int N)
{
    n=N;
    
    currency=new int[N];
    adjm=new double*[N];
    for(int i=0;i<N;i++)
    {
     adjm[i]=new double[N];
    }
    for(int i=0;i<N;i++)
    {
        for(int j=0;j<N;j++)
        {
            if(j!=i)
            {
                adjm[i][j]=-1;
            }
            else
            {
                adjm[i][j]=1;
            }
        }
    }
    
}
void Graph::currency_updt(int i,int j)//update the array by the input given from user
{
    currency[i]=j;
}

void Graph::coldata(int a,int b)
{
    colour[a][b]=1;
    colour[b][a]=1;
}

void Graph::addedge(int a, int b, double w)
{
    int i=currency[a];
    int j=currency[b];
     if(colour[i][j])//add edge only when the currencies can be transferable
     {
         
         adjm[a][b]=w;
         return;
         
     }
    return;
}

double Graph::max_product(int src,int dest,int mul)
{
     double dist[n];//array to store distance from source
    for (int i = 0; i < n; i++)
    {
        dist[i] = INT_MIN;//initialise distance from source to int_min
    }
    dist[src] = 1;
    
  for(int k=0;k<n-1;k++)
  {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) 
        {
            if(adjm[i][j]!=-1)
            {
                double weight=adjm[i][j];
            if ( dist[i]!=INT_MIN && dist[i]*weight >dist[j])
              {
                dist[j] = dist[i] * weight;
               }
            }    
        }
    }
  }
    
     if(dist[dest]==INT_MIN)
    {
        cout<<-1<<endl;//if the dest vertex is not updated it means there is no path from source 
        return -1;
    }
    
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) 
        {
            if(adjm[i][j]!=-1)
            {
                double weight=adjm[i][j];
            if (dist[i] != INT_MIN && dist[i]*weight >dist[j])
              {
                cout<<"INF"<<endl;
                return 0;
               }
            }    
        }
    }
    
    cout<<fixed<<setprecision(3)<<mul*dist[dest]<<endl;
    return 1;
  
}
int main() {
    
    
    Graph g;
    
    int C,m,N;
    cin>>C>>m;
    g.colourcr(C);
    for(int i=0;i<m;i++)
    {
        int a,b;
        cin>>a>>b;
        g.coldata(a,b);
    }
    cin>>N;
     g.create(N);
   
    for(int i=0;i<N;i++)
    {
        int a;
        cin>>a;
       g.currency_updt(i,a); 
    }
    for(int i=0;i<N;i++)
    {
        for(int j=0;j<N;j++)
        {
         double x;
         cin>>x;
            g.addedge(i,j,x);
        }
        
    }
    int q;
    cin>>q;
    for(int i=0;i<q;i++)
    {
        int a,b,c;
        cin>>a>>b>>c;
        g.max_product(a,b,c);
    }
    return 0;
}
