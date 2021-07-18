#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;
struct Node
{
    int data;
    struct Node* next;
};

 class Stack{
     public:
     void Push(int x);
     int Pop();
     int Top();
     void create();
     int isEmpty();
     private:
     Node* tos;
 };
void Stack::create()//initialising top of stack with nullptr
{
    tos=nullptr;
}
 void Stack::Push(int x)//pushing an element into the stack
 {
     struct Node* newnode; 
     if(tos==nullptr)
     {
         tos=new Node[1];
         tos->data=x;
         tos->next=nullptr;
     }
     else
     {
     newnode=new Node[1];
     newnode->data=x;
     newnode->next=tos;
     tos=newnode;
     }
 }
int Stack::Pop()//poping out an element from the stack
{
    if(tos==nullptr)
    {
        return -1;
    }
    int x=tos->data;
    Node* temp=tos;
    tos=tos->next;
    temp->next=nullptr;
    free(temp);
    return x;
}
int Stack::Top()//returning the value of element at thetop of the stack
{
    if(tos==nullptr)
    {
        return -1;
    }
    return tos->data;
}
int Stack::isEmpty()//checking whether the stack is empty or not
{
    if(tos==nullptr)
    {
        return 1;
    }
    return 0;
}

class Graph{
    private:
    int v;     //number of vertices
    int** adjm;//adjacency matrix
    public:
    void  Constructor(int n);
    
    void operator +=(pair<int,int> p)
    {
        int i=p.first;
        int j=p.second;
        
            adjm[i][j]=1;
            adjm[j][i]=1;
        
    }
    void operator -=(pair<int,int> p)
    {
        int i=p.first;
        int j=p.second;
         
        adjm[i][j]=0;
        adjm[j][i]=0;
        
    }
    
    int cycledetecthelper(int s,int p,int* visited);
    int detectCycle();
    int components();
    int reach(int u, int v);
    
    } ;
 
 void  Graph::Constructor(int n)//assigns value 0 to every element in the adjancy matrix
 {
     int i=0,j=0;
     v=n;
     adjm=new int*[n];
     for(int k=0;k<n;k++)
     {
         adjm[k]=new int[n];
     }
     while(i<n)
     {
         j=0;
         while(j<n)
         {
             adjm[i][j]=0;
             j++;
         }
         i++;
     }
 }
int Graph::cycledetecthelper(int s,int p,int visited[] )//helper (recurisve)function with parameters as parent,source,visited elements array
{     
    visited[s] = 1; 
                
    for(int i=0;i<v;i++)
    { 
         
        if (!visited[i] &&adjm[i][s]==1) 
        { 
           if (cycledetecthelper(i,s,visited)) //recurisve step
           {
               return 1;
           }
        } 
  
        else
            if (i != p && visited[i]&& i!=s && adjm[i][s]) 
        { 
            return 1;
        } 
    } 
    return 0;
} 
int Graph::detectCycle()//this function tells that whether a grpah contains a cycle or not 
{ 
      
    int *visited = new int[v]; 
    for (int i = 0; i < v; i++) 
    {
        visited[i] = 0;
    }
   
    for (int i = 0; i < v; i++) 
    { 
         
          if (!visited[i] && cycledetecthelper(i, -1,visited)) 
          {
              return 1;
          }
    } 
    return 0; 
} 
 int Graph::components()//finds the number of connected components graph have
 {
     int visited[v];
     Stack st;
     st.create();
     int count=0,/*currver,*/check=0;
     for(int i=0;i<v;i++)
     {
         visited[i]=0;
     }
     
     for(int i=0;i<v;i++)
     {
          if(!visited[i]) 
       {
              count++;
         
          visited[i]=1;
              st.Push(i);
          
               for(int j=0;j<v;j++)
              {
                  if(adjm[i][j]==1 && !visited[j])
                 {
                    st. Push(j);
                    visited[j]=1;
                    break;
                  }
              }
            while(!st.isEmpty())
           {
              int p=st.Top();
              
              for(int k=0;k<v;k++)
              {
                  if(adjm[k][p]==1 && !visited[k])
                  {
                      
                      st.Push(k);
                      visited[k]=1;
                       check=1;
                      break;
                  }
              }
              
               if(check==0)
               {
                   st.Pop();
                  
               }
                 check=0;
             }
             
          }     
      }
       return count;  
 }

    int Graph::reach(int a, int b)//finds whether there exists a path between vertices a,b or not
    {
        if(adjm[a][b]==1)
        {
            return 1;
        }
        int visited[v],check=0;
     Stack st;
        st.create();
      for(int i=0;i<v;i++)
      {
         visited[i]=0;
       }
        visited[a]=1;
        st.Push(a);
        
         while(!st.isEmpty())
           {
              int p=st.Top();
              
              for(int k=0;k<v;k++)
              {
                  check=0;
                  if(adjm[k][p]==1 && !visited[k])
                  {
                      if(k==b)
                      {
                          return 1;
                      }
                      st.Push(k);
                      visited[k]=1;
                       check=1;
                      break;
                  }
              }
              
               if(check==0)
               {
                   st.Pop();
                  
               }
          }
        return 0;
    }

int main() {
   
    pair<int,int> p;
    int q,x;
    cin>>q;
    string str;
    Stack s;
    s.create();
    for(int i=0;i<q;i++)
    {
        cin>>str;

        if(str=="push")
        {
           cin>>x;
            s.Push(x);
        }
        if(str=="pop")
        {
            x=s.Pop();
            cout<<x<<endl;
        }
         if(str=="top")
         {
             x=s.Top();
             cout<<x<<endl;
         }
             if(str=="empty")
             {
                 x=s.isEmpty();
                 cout<<x<<endl;
             }
    }
    int n,m;
    cin>>n>>m;
    Graph g;
    g.Constructor(n);
    for(int i=0;i<m;i++)
    {
        cin>>str;
        if(str=="add")
        {
            cin>>p.first>>p.second;
            g+=p;

        }
        else
         if(str=="del")
         {
            cin>>p.first>>p.second;
            g-=p;
         }
        else
            if(str=="cycle")
            {
                x=g.detectCycle();
                cout<<x<<endl;
            }
        else
            if(str=="components")
            {
                x=g.components();
                cout<<x<<endl;
            }
        else
            if(str=="reach")
            {
                int a,b;
                cin>>a>>b;
                x=g.reach(a,b);
                cout<<x<<endl;
            }
    }
    return 0;
}
