#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include<bits/stdc++.h> 

using namespace std;
  class Matrix{
    public:
    int binarySearch(int x,int k);
    int* matrixSearch(int x);    
    void creatematrix(int r,int c);
    void insertelement(int i,int j,int x);
      
    protected:
    int **a;
    int m,n;
};

    
    void Matrix::insertelement(int i, int j, int x)//inserts an element in the array
    {
      a[i][j]=x;
    }
 

    void Matrix::creatematrix(int r,int c)//creates a 2dimensional matrix
   {
       m=r;
       n=c;
      a = new int*[m];
    for(int i=0;i<m;i++)
    {
        a[i] = new int[n];
    }
       
   }

 int Matrix::binarySearch(int x,int k)//searches for a maximum index j in kth row such that a[k][j]<=x
 {
     int l=0,r=n-1;
     if(a[k][0]>x)
     {
         return -1;
     }
     if(a[k][n-1]<=x)
     {
         return n-1;
     }
     
      while (l <= r) 
    {     
      int m = l + (r-l)/2; 
  
      if (a[k][m] <= x && a[k][m+1] > x)  
      {
         return m;   
      }
      if (a[k][m] <= x)  
      {
         l = m + 1;  
      }
      else 
      {
         r = m - 1;
       }   
    } 
 
     return m;
 }
       
 int* Matrix::matrixSearch(int x)//returns the index i,j for a[i][j]=x if x is not present then it returns -1,-1
 {
   int *arr=new int[2];
     arr[0]=-1;
     arr[1]=-1;
     for(int i=0;i<m;i++)
     {
           int l=0,r=n-1;
     
        while (l <= r) 
      {     
        int m = l + (r-l)/2; 
  
        if (a[i][m] == x && a[i][m-1]!=x)  
        {
           arr[0]=i;
            arr[1]=m;
          return arr;   
        }
        if (a[i][m] < x)  
        {
          l = m + 1;  
        }
         else 
        {
          r = m - 1;
        }   
       } 
 
     }
     return arr;
 }

class MatrixMedian: public Matrix//by writing public here all the public variables in derived class will be public in the derived class and protected will be protected
{
 public:
 int upperbound(int x,int k);
 int FindMedian();  

};
 
      
int MatrixMedian:: upperbound(int x,int k)//this function finds the smallest index such that x<a[k][j]
{

    
    if(binarySearch(x,k)==n-1)
    {
    return -1;
    }
       return binarySearch(x,k)+1;
    
}

int  MatrixMedian::FindMedian() //find the median 
{ 
    
    int min = a[0][0], max = a[0][n-1],i=1; 
    
    while(i<m) 
    { 
        // Finding the minimum element in the array 
        if (a[i][0] < min) 
        { 
            min = a[i][0]; 
        }
        // Finding the maximum element in the array
        if (a[i][n-1] > max) 
        {
            max = a[i][n-1]; 
         }
         i++;
    }
    
    int reqindex = (m * n ) / 2; 
    
    while (min != max) 
    { 
        int mid = min + (max - min) / 2; 
        int place = 0,i=0; 
  
        while (i < m) 
        {
            int x=upperbound(mid,i );
            if(x==-1)
            {
                x=n;
            }
         place += x ;
            i++;
        }
        
         if (place <= reqindex) 
          {
             min = mid + 1;
          }

        else
          {
            max = mid;
          }
        
    } 
    return max; 
} 

int main() {
    
       int m,n;
       cin>>m>>n;
       MatrixMedian obj;
       obj.creatematrix(m,n);
    
       for(int i=0;i<m;i++)
       {
           for(int j=0;j<n;j++)
           {
               int x;
             cin>>x;
             obj.insertelement(i,j,x);  
           }
       }
       int q;
       cin>>q;
       string str;
       
        int res=0,i=0;
        while(i<q)
        {
            cin>>str;
            if(str=="BS")
            {
                int c,d;
                cin>>c>>d;
               res= obj.binarySearch(c,d);
                cout<<res<<endl;
            }
            if(str=="Median")
            {
                res=obj.FindMedian();
                cout<<res<<endl;
            }
            if(str=="MS")
            {
                int p;
                cin>>p;
                int* ptr=obj.matrixSearch(p);
                
                cout<<ptr[0]<<" "<<ptr[1]<<endl;
            }
            i++;
        }
    return 0;
}
