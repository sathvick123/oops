#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include<bits/stdc++.h>
using namespace std;

struct node //structure to store vertex and weight at one place
{
    int vertex;
    int weight;
};

class Graph
{
    public:
    void create(int ver);
    void AddV();
    void AddE(int a,int b,int w);
    void DelE(int a,int b);
    protected:
    int V;                  //number of vertices
    vector<node>array[1000];//array of vectors to store adjancy list 
    bool check=false;  
};

void Graph::AddV()//increment vertex count by 1
{
    V++;
    check=false;
}

void Graph::create(int ver)//assign the given input number of vertices to the class variable
{
    V=ver;    
}

void Graph::AddE(int a,int b,int w)//add an edge between vertices a and b of weight w 
{
    check=false;
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
 
void Graph::DelE(int a,int b)//delete an edge between vertices a and b
{
        check=false;
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

struct data{
    int Weight;    
    int v1;
    int v2;
    };

bool compare(data a,data b)//comparing structures taking weights as first first criteria
{
    if(a.Weight==b.Weight)
    {
      if(a.v1==b.v1) 
      {
          return a.v2<b.v2;
      }
        return a.v1<b.v1;
    }
    return a.Weight<b.Weight;
}

class MST: public Graph
{
  public:
  void Prims(int ver);
  
  int cycledetecthelper(int s,int p,int visited[] );
  int detectCycle();
  void Kruskal();
  
  int TreeUptodate();
  void DisplayTree();
  
  private:
  vector<node>minst[1000];
    
};

void MST::Prims(int ver)
{
    if(ver>V-1)//if the input vertex is greater than v-1 then it is error
    {
        cerr<<"error";
    }
    
    for(int i=0;i<1000;i++)//making the list clear
    {
    minst[i].clear();
    }
    
    int sum=0;
    check=true;
    struct node temp;
 
    priority_queue<pair<int,int>,vector<pair<int,int>>,greater<pair<int,int>>> pq;//to use the priority queue as minheap

    vector<int> value(V, INT_MAX);
     value[ver]=0;
   
    vector<int> parent(V, -1);
 
    vector<bool> included_in_mst(V, false);
 
    pq.push(make_pair(0, ver));
    value[ver] = 0;
    int i=0;
    
    while (i!=V)
    {
        int u = pq.top().second;
        int w=pq.top().first;
       
        pq.pop();
       if(included_in_mst[u])
       {
         continue;
       }
        
        if(w!=0)
        {
        temp.vertex=parent[u];
        temp.weight=value[u];
        minst[u].push_back(temp);
        
        temp.vertex=u;
        minst[parent[u]].push_back(temp);
        }
       
        if(!included_in_mst[u])
        {
        sum=sum+w; //if the edge is not included in mst 
        }
        
        included_in_mst[u] = true;  // Include vertex in mst
         i++;
         if(i==V)
        {
            break;
         }
        for (auto i = array[u].begin(); i != array[u].end(); ++i)//updatating value array for all vertices that are adjacent to u and not included in mst
        {
            int v = (*i).vertex;
            int weigh = (*i).weight;
 
            if (included_in_mst[v] == false && value[v] > weigh)
            {
                value[v] = weigh;//update the value since it has the value intmax initially 
                pq.push(make_pair(value[v], v));
                parent[v] = u;
            }
        }
        
    }
    
      cout<<sum<<endl;
}

int MST::cycledetecthelper(int s,int p,int visited[] )//helper (recurisve)function with parameters as parent,source,visited elements array
{     
    visited[s] = 1;           
    for(auto i=minst[s].begin();i!=minst[s].end();i++)
    { 
         node temp = *i;
        
        if (!visited[temp.vertex]) 
        { 
           if (cycledetecthelper(temp.vertex,s,visited)) //recurisve step
           {
               return 1;
           }
        } 
  
        else
            if (temp.vertex != p  && temp.vertex!=s) 
        { 
            return 1;
        } 
    } 
    return 0;
} 

int MST::detectCycle()//this function tells that whether a grpah contains a cycle or not 
{ 
      
    int *visited = new int[V]; 
    for (int i = 0; i < V; i++) 
    {
        visited[i] = 0;
    }
   
    for (int i = 0; i < V; i++) 
    { 
         
          if (!visited[i] && cycledetecthelper(i, -1,visited)) 
          {
              return 1;
          }
    } 
    return 0; 
} 

void MST::Kruskal()
{
    check=true;//for treeuptodate function
    int sum=0;
    for(int i=0;i<1000;i++)//clearing the data present for using it freshly
    {    
       minst[i].clear();
    }
    vector<data>edgdata;
    struct data temp;
    struct node temp1;
    int k=0;
    for(int i=0;i<V;i++)
    {
       for(auto j=array[i].begin();j!=array[i].end();j++)
      {
        temp.v1=i;
        temp.v2=(*j).vertex;
        temp.Weight=(*j).weight;
           if(temp.v1<temp.v2)
           {
            edgdata.push_back(temp);
               k++;             //counting number of edges
           }
      }
    }
     sort(edgdata.begin(), edgdata.end(),compare);//sorting according to weights
    int i=0,j=0;
    while(i<k)
    {
        temp=edgdata[j];
        j++;
        i++;
        
         temp1.vertex=temp.v2;
         temp1.weight=temp.Weight;
        minst[temp.v1].push_back(temp1);//pushing the required edge into minst which means edge is added to minimum spanning tree if it doesnt form cylce
                
          temp1.vertex=temp.v1;                      
        minst[temp.v2].push_back(temp1);

        if(detectCycle() )//if the added edge forms cycle then it should not be added
        {
            minst[temp.v1].pop_back();
            minst[temp.v2].pop_back();
        }
        else//if the added edge doenot form cycle then it should be in minimum spainning tree
        {           
            sum=sum+temp.Weight;
        }
    }
     
    cout<<sum<<endl;
}

int MST::TreeUptodate()
{
    if(check)
    {
        return 1;
    }
    return 0;
}
    void MST::DisplayTree()
{
    
    vector<data>edgdata;
    data temp;
    int k=0;
    for(int i=0;i<V;i++)
    {
       for(auto j=minst[i].begin();j!=minst[i].end();j++)
      {
        temp.v1=i;
        temp.v2=(*j).vertex;
        temp.Weight=(*j).weight;
           if(temp.v1<temp.v2)
           {
            edgdata.push_back(temp);
               k++;
           }
      }
    }
    
    sort(edgdata.begin(), edgdata.end(),compare);//sorting the edges according to weights
    
    for(int i=0;i<k;i++)
    {
        cout<<edgdata[i].v1<<" "<<edgdata[i].v2<<" "<<edgdata[i].Weight<<endl;
    }
    
}

int main() {
       int n,q;
       string str;
       cin>>n>>q;
       MST obj;
    
    obj.create(n);
    
       for(int i=0;i<q;i++)
       {
           cin>>str;
        if(str=="ADDV")
        {
            obj.AddV();
        }
        else
        if(str=="ADDE")
        {
            int u,v,w;
            cin>>u>>v>>w;
            obj.AddE(u,v,w);
        }
        else
        if(str=="DELE")
        {
            int u,v;
            cin>>u>>v;
            obj.DelE(u,v);
        }
        else
         if(str=="Prims")
         {
             cin>>n;
             obj.Prims(n);
         }
         else
          if(str=="Kruskal")
          {
              obj.Kruskal();
          }
         else
           if(str=="TreeUptodate")
           {
               if(obj.TreeUptodate())
               {
                   cout<<"YES"<<endl;
               }
               else
               {
                   cout<<"NO"<<endl;
               }
           }
         else
           if(str=="DisplayTree")
           {
              obj.DisplayTree();
           }
       }
    return 0;
}
