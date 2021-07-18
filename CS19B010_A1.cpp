#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;
 
   void reverse_upto_index_d(int *a,int d)//this function reverses the values in an array from starting index to index d
     {
         for(int i=0;i<d/2;i++)
         {
             int temp=a[d-i-1];
             a[d-i-1]=a[i];
             a[i]=temp;
         }
     }

class matrix
{
  public:  
    
    void Special_Sum();
    void Mod_Multiplication();
    void Matrix_Right_Shift(matrix b,int k);
    void special_Matrix_Addition(matrix b,int x);
    void creatematrix(int size);
    void insertelement(int i,int j,int x);
    int getelements(int i,int j);
    private:
       int **p;
       int size;
};
     
    void matrix::insertelement(int i, int j, int x)//inserts an element in the array
    {
      p[i][j]=x;
    }
   int matrix::getelements(int i,int j)//returns the element at index(i,j)
   {
      return p[i][j];
   }
   void matrix::creatematrix(int n)//creates a 2dimensional matrix
   {
       size=n;//assigns the value n to size
      p = new int*[n];
    for(int i=0;i<n;i++)
    {
        p[i] = new int[n];
    }
       
   }
   void matrix::Special_Sum()
   {
       int count=0;
     for(int i=0;i<size;i++)
     {
         int sum=0;
      for(int j=0;j<size;j++)
      {
        if((i+j)%2==0)
        {
            sum=sum+p[i][j];
        }
          else
          {
              sum=sum+p[j][i];
          }
      }
         
         cout<<sum;
         if(count!=size-1)//number of commas are  equal to size-1
         {
             cout<<",";
             count++;
         }
     }
       cout<<endl;
   }
   void matrix::Mod_Multiplication()
   {
     long long int product=1;
       for(int i=0;i<size;i++)
       {
         if(i%3==0)
         {
             int max=p[i][0];
             for(int j=1;j<size;j++)
             {
                if(p[i][j]>max)
                {
                    max=p[i][j];//getting maximum element from the loop
                }
             }
             product=product*max;
         }
          if(i%3==1)
         {
             int min=p[i][0];
             for(int j=1;j<size;j++)
             {
                if(p[i][j]<min)
                {
                    min=p[i][j];//getting minimum element from the loop
                }
             }
             product=product*min;
         }
          if(i%3==2)
          {
              int sum=0;
              for(int j=0;j<size;j++)
              {
                  sum=sum+p[i][j];
              }
              sum=sum/size;
              product=product*sum;
          }
       }
       cout<<product<<endl;
   }
    
 void matrix::Matrix_Right_Shift(matrix b,int k)
     {
      
         int arr[size*size],c[size][size],d[size*size];
           
          for(int i=0;i<size;i++)
          {    
           for(int j=0;j<size;j++)
           {
             c[i][j]=b.getelements(i,j);
           }
           }
       for(int i=0;i<size;i++)
       {
           for(int j=0;j<size;j++)
           {
               arr[i*size+j]=p[i][j];//taking the 2d array into 1d form for rotation
               d[i*size+j]=c[i][j];//taking the 2d array into 1d form for rotation
           }
       }
        reverse_upto_index_d(arr,size*size-k);
        reverse_upto_index_d((arr+size*size-k),k);
        reverse_upto_index_d(arr,size*size);
        
        reverse_upto_index_d(d,size*size-k);
        reverse_upto_index_d((d+size*size-k),k);
        reverse_upto_index_d(d,size*size);
        for(int i=0;i<size*size;i++)
        {
            cout<<arr[i]+d[i]<<" ";
            if((i+1)%size==0)
            {
                cout<<endl;//to print in the form of 2d array
            }
        }
     }
    void matrix::special_Matrix_Addition(matrix b,int x)
    {
       if(x==1)
       {
         int y;
           for(int i=0;i<size;i++)
           {
             for(int j=0;j<size;j++)
             {
                y=p[j][i]+b.getelements(i,j);
                cout<<y<<" "; 
             }
               cout<<endl;
           }
       }
        if(x==2)
        {
            int y;
           for(int i=0;i<size;i++)
           {
             for(int j=0;j<size;j++)
             {
                y=p[i][j]+b.getelements(j,i);
                 cout<<y<<" ";
             }
               cout<<endl;
           }
        }
    }



int main() {
    
    int q,n,x;
    cin>>q>>n;
    matrix matr;
    matrix matr1;
    matr.creatematrix(n);
    matr1.creatematrix(n);
    for(int i=0;i<n;i++)
    {
     for(int j=0;j<n;j++)
     {
         cin>>x;
       matr.insertelement(i,j,x);//inserting elements into the class
     }
    }
    for(int i=0;i<n;i++)
    {
     for(int j=0;j<n;j++)
     {
         cin>>x;
       matr1.insertelement(i,j,x);//inserting elements into the class
     }
    }
    
    string str;
    
    for(int i=0;i<q;i++)
    {
      cin>>str;
        if(str=="SPSUM")
        {
            matr.Special_Sum();
        }
        if(str=="MOD")
        {
            matr.Mod_Multiplication();
        }
        if(str=="MRS")
        {
          int k;
            cin>>k;
            matr.Matrix_Right_Shift(matr1,k);
        }
        if(str=="MADD")
        {
            int p;
            cin>>p;
            matr.special_Matrix_Addition(matr1,p);
        }
    }
    return 0;
}