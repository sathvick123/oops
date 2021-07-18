#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <queue>
#include <bits/stdc++.h>

using namespace std;

struct node //structure to store vertex and weight at one place
{
    int vertex;
    int weight;
};
template <class Type>

class Graph
{
    public:
    void create(int ver);
    void AddV();
    void AddE(int a,int b,Type w);
    void DelE(int a,int b);
    void BFS(int a);
    void SSP(int src);
    
    private:
    int V;                  //number of vertices
    vector<node>array[1000];//array of vectors to store adjancy list 
    
};

template <class Type>
void Graph<Type>::AddV()//increment vertex count by 1
{
    V++;
}

template <class Type>
void Graph<Type>::create(int ver)//assign the given input number of vertices to the class variable
{
    V=ver;
}

template <class Type>
void Graph<Type>::AddE(int a,int b,Type w)//add an edge between vertices a and b of weight w 
{
    struct node temp;
    temp.vertex=b;
    temp.weight=w;
    
    if(a>=V || b>=V)      //if the vertex number is greater than or equal to the number of vertices error message is need to be printed since vertex number ranges from 0 to V-1
    {
        cerr<<"error";
        return;
    }
    
    auto count=array[a].begin();
    
    for(auto j=array[a].begin();j<array[a].end();j++)//to insert the node into the vector in a sorted order
    {
        if(j->weight < w)
        {
            count++;
        }
        if(j->weight==w)
        {
            if(j->vertex > b)
            {
                count++;
            }
        }
    }
    
     array[a].insert(count,temp);
     temp.vertex=a;
     count=array[b].begin();
    
    for(auto j=array[b].begin();j<array[b].end();j++)//to insert the node into the vector in a sorted order
    {
        if(j->weight <w)
        {
            count++;
        }
        if(j->weight==w)
        {
            if(j->vertex > a)
            {
                count++;
            }
        }
    }
     array[b].insert(count,temp);
}
 
template <class Type>
void Graph<Type>::DelE(int a,int b)//delete an edge between vertices a and b
{
    
        auto i=array[a].begin();
        auto j=array[a].end();
    for( i=array[a].begin();i<array[a].end();i++)
    {
        struct node temp=*i;
        
        if(b==temp.vertex)
        {
            array[a].erase(i);
            break;
        }
     
    }
    
       if(i==j)//if there is no edge between the vertices error message is need to be printed  
      {
        cerr<<"error";
        return;
      }
    
     for( i=array[b].begin();i<array[b].end();i++)
    {
         struct node temp=*i;
        if(a==temp.vertex)
        {   
            array[b].erase(i);
            break;
        }
     }
    
}

template <class Type>
void Graph<Type>::BFS(int a) 
{ 
    queue<int> q; 
    bool visited[V];//taking visited array of size=number of vertices
    for(int i=0;i<V;i++)
    {
        visited[i]=false;//marking all of them as false that is  not visited
    }
    q.push(a); 
    visited[a] = true; //marking the pushed vertex as visited
  
    while (!q.empty()) 
    { 
        int vertex = q.front();    
        cout << vertex << " "; 

          q.pop(); 
        
        for (auto i = array[vertex].begin(); i != array[vertex].end(); i++) 
        { 
            
            if (!visited[i->vertex]) 
            { 
                q.push(i->vertex); //pushing the adjacent unvisited vertices into the queue
                visited[i->vertex] = true; //marking it as visited
            }
            
        }
            
    }
    cout<<endl;
} 

template <class Type>
void Graph<Type>::SSP(int source)//single source shortest path 
{ 
    priority_queue<pair<int,int > > pqueue; 
  
    vector<int> distance(V, INT_MAX);//intitialising all vertices distances from source to int_max  
  
    pqueue.push(make_pair(0, source)); 
    distance[source] = 0; //making distance from source to source as 0
  
    while (!pqueue.empty()) 
    { 
        int u = pqueue.top().second; 
        pqueue.pop(); 
  
        for (auto i = array[u].begin(); i != array[u].end(); ++i) 
        { 
            int v = (*i).vertex; 
            int Weight = (*i).weight; 
            
            if (distance[v] > distance[u] + Weight) //comparing the distance of v from source and updating if it is larger than other
            {  
                distance[v] = distance[u] + Weight; 
                pqueue.push(make_pair(distance[v], v)); 
           
            } 
        } 
    } 
    int i=0;
    while (i != V) 
    {
        cout<<distance[i]<<" ";
        i++;
    }
    cout<<endl;
}

int main() {
    int v,q;
    cin>>v>>q;
    string str;
    Graph<int> g;
    
    g.create(v);
    
    for(int i=0;i<q+2;i+=1)
    {
        cin>>str;
        if(str=="ADDV")
        {
            g.AddV();
        }
        else
        if(str=="ADDE")
        {
            int u,v,w;
            cin>>u>>v>>w;
            g.AddE(u,v,w);
        }
        else
        if(str=="DELE")
        {
            int u,v;
            cin>>u>>v;
            g.DelE(u,v);
        }
        else
            if(str=="BFS")
            {
                int a;
                cin>>a;
                g.BFS(a);
            }
        else
            if(str=="SSP")
            {
                int b;
                cin>>b;
                g.SSP(b);
            }
    }
    
    return 0;
}
