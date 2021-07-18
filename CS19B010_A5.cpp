#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include<climits>
using namespace std;


int max(int a, int b, int c) { 
     if(a>=b && a>=c)
     {
         return a;
     }
        if(b>=a && b>=c)
        {
            return b;
        }
     return c;
}

class BLOOMBRAIN
{
    private:
    int* roomallot;
    int* visited;
     int num;
    
    public:
     void Create(int n);//creates visited array and initialises all its elements to 1

    long long int MergeSort(int inpt[],int temp[],int l,int r);
    long long int Merge(int inpt[],int temp[],int l,int m,int r);
    long long int Update(int* input,int n);
    
    void Join(int s);
    
    void Leave(int rno);
    
    int Occupied();
    
    int Max_sum_crossing_middle(int l, int m, int h);
    int MaxSubArraySum(int l, int h);
    int Play();
     
};

void BLOOMBRAIN::Create(int n)
{
    visited=new int[n];//creating an array to check in a paricular room whether a person is present or not 
    for(int i=0;i<n;i++)
    {
        visited[i]=1;
    }
}

long long int BLOOMBRAIN::MergeSort(int inpt[],int temp[], int l, int r)//uses 
{
    int m;
    long long int inversions = 0;
    if (r>l) {
        
        m = l+ (r-l)/2;
 
        inversions += MergeSort(inpt,temp,l,m);//number of inversions in left half
        inversions += MergeSort(inpt,temp,m+1,r);//number of inversions in right half

        inversions += Merge(inpt,temp,l,m+1,r);//number of inversions from left half to right half
    }
    return inversions;
}
 
long long int BLOOMBRAIN::Merge(int inpt[],int temp[],int l,int m,int r)
{
    int i, j, k;
  long long int inversion_t = 0;
 
    i = l; // index for left subarray
    j = m; // index for right subarray
    k = l; // index for resultant merged subarray
    
    while ( (i != m) && (j != r+1) )
    {
        if(inpt[i] > inpt[j])
        {
            temp[k] = inpt[j];
            j++;
            k++;
            inversion_t = inversion_t+(m- i);
            //since the elements in left half are sorted so there are m-i numbrs which are greater than inpt[j] 
        }
        
        else 
        {
            temp[k] = inpt[i];
            i++;
            k++;
        }
    }
    
     while (j <= r)//if the all elements in left half are inserted into the temp array
    {
        temp[k] = inpt[j];
         j++;
         k++;
    }
    
    while (i<= m-1)//if the all elements in right half are inserted into the temp array
    {
        temp[k] = inpt[i];
        i++;
        k++;
    }
    
      i=l;
    while(i<=r)
    {
        inpt[i] = temp[i];//temp array contains the elements in sorted order now inpt array is also storing the elements in sorted order
        i++;
    }
    return inversion_t;
}



long long int BLOOMBRAIN::Update(int* input,int n)
 {
    
     num=n;
     roomallot=new int[n];
     int* newarr=new int[n];//creating a new array which is used to store all visited elements sequentially from start to end
   
     int j=0; 
     
    for(int i=0;i<num;i++)
     {
         roomallot[i]=input[i];//stores all values in a private array 
         if(visited[i])
        {
            newarr[j]=input[i];
            j++;
        }
         
     }  
    int temp[j];
    
    return MergeSort(newarr,temp, 0, j- 1); 
    }

 void BLOOMBRAIN::Join(int s)
 {
     for(int i=num-1;i>=0;i--)
     {
         if(!visited[i])//checking  the hightest empty room
         {
             visited[i]=1;
             roomallot[i]=s;
             return;
         }
     }
 }

 void BLOOMBRAIN::Leave(int rno)
 {
    roomallot[rno]=0;    
    visited[rno]=0;
 }

 int BLOOMBRAIN::Occupied()
 {
   int count=0;
     for(int i=0;i<num;i++)
     {
         if(visited[i]) //though the element is zero if it is added or the element is updated for the first time then it is considered as visited
         {
             count++;
         }
     }
     return count;
 }

int BLOOMBRAIN::Max_sum_crossing_middle(int l, int m, int h)
{
    int total = 0,i=m;
    int leftpart = INT_MIN;
      while(i >= l)
     {
        total = total+roomallot[i];
     
          if (total > leftpart)
          { 
            leftpart = total;//calculating max sum from left to middle
           }
        i--;
     }
    
    total = 0;
    i=m+1;
    int rightpart = INT_MIN;
     while(i <= h) 
     {
        total = total + roomallot[i];
        if (total > rightpart)
        {
            rightpart = total;//caclulating maximum sum from middle+1 to right
        }
         i++;
      }
    
    return max(leftpart , rightpart , leftpart + rightpart);
}
 
int BLOOMBRAIN::MaxSubArraySum(int l, int h)//uses divide and conquer
{
 
    if (l == h)
    {
        return roomallot[l];// if there is only onelement present
    }
    
    int m =l + (h - l)/2;
 
    /*max of(sum of maxsubarray of left half part of array assuming middle element is not in the largest sum           
    subarray,sum of maxsubarray of right half part of array assuming middle element is not in the largest sum 
    subarray,maximum sum containing subarray assuming middle element in the maximum sum*/
    
    return max( MaxSubArraySum(l, m) , MaxSubArraySum(m + 1, h) , Max_sum_crossing_middle(l, m, h));
}

int BLOOMBRAIN::Play()
{
    return MaxSubArraySum(0,num-1);
}

int main() {
    int n,q,st,rn;
    cin>>n>>q;
    string str;
    
    BLOOMBRAIN center;
    center.Create(n);
    for(int i=0;i<q;i++)
    {
        cin>>str;
        if(str=="update")
        {
            int* arr=new int[n];
            for(int j=0;j<n;j++)
            {
                cin>>arr[j];    
            }
            
           cout<<center.Update(arr,n)<<endl;
            
        }
        if(str=="join")
        {
            cin>>st;
            center.Join(st);
        }
        if(str=="leave")
        {
            cin>>rn;
            center.Leave(rn);
        }
        if(str=="occupied")
        {
            
            cout<<center.Occupied()<<endl;
        }
        if(str=="play")
        {
            cout<<center.Play()<<endl;
        }
    }
    
    return 0;
}
