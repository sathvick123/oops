#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

class Minesweeper{
    private:
    int **a,n,m;
    int blocksrevealed;
    int **visited;
   
    public:
    void create(int N,int M);//creates the input matrices and assigns values of n,m from the input
    void mineadder(int x);//makes the element of the given index as -1,it means -1 describes the mine is present
    int minechecker(int x,int y);
    
};

 void Minesweeper::create(int N,int M)
 {
     n=N;
     m=M;
     blocksrevealed=0;
     a=new int*[n];
     visited=new int*[n];
     for(int i=0;i<n;i++)
     {
         a[i]=new int[n];
         visited[i]=new int[n];
     }
     for(int i=0;i<n;i++)
     {
         for(int j=0;j<n ;j++)
         {
             a[i][j]=-2;
             visited[i][j]=0;
         }
     }
 }

void Minesweeper::mineadder(int x)
{
    int i=x/n;
    int j=x%n;
    a[i][j]=-1;//tells that mine is present at index i,j
}

int Minesweeper::minechecker(int x,int y)
{
    if(a[x][y]==-1)//if the given idex has a mine then the player has lost the game and it is shown by the return status -1
    {
        return -1;
    }
    if(visited[x][y]==1)//if the given element is already visited then return the blocksrevealed at present
    {
        return blocksrevealed;
    }
    visited[x][y]=1;//marking the input as visited
    blocksrevealed++;
     
    int mc=0;
    
    for(int i=x-1;i<=x+1;i++)
    {
        for(int j=y-1;j<=y+1;j++)
        {
          if(i>=0 && i<=n-1 && j>=0 && j<=n-1 )
          {
             if(a[i][j]==-1)
            {
               mc++;//counting the number of neighbouring mines
            } 
          }
        }
        
    }
    if(mc!=0)
    {
        a[x][y]=mc;
        return blocksrevealed;
    }
    
    for(int i=x-1;i<=x+1;i++)
    {
        for(int j=y-1;j<=y+1;j++)
        {
          if(i>=0 && i<=n-1 && j>=0 && j<=n-1 )
          {
              
              if(!visited[i][j])
              {    
                minechecker(i,j);
              }
              
          }
            
        }
    }
    
    return blocksrevealed;
}
int main() {
    int N,M;
    cin>>N>>M;
    Minesweeper obj;
    obj.create(N,M);
    for(int i=0;i<M;i++)
    {
            int min;
            cin>>min;
          obj.mineadder(min);
    }
    int inpt1,inpt2,res;
    
    while(cin>>inpt1>>inpt2)
    {
       
      res=obj.minechecker(inpt1,inpt2);
    
        if(res==-1)
        {
            cout<<"Lost"<<endl;
        }
        else
        if(res==N*N-M)
        {
            cout<<"Won"<<endl;
        }
        
        else
        {
            cout<<res<<endl;
        }
       
    }
}