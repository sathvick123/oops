#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

template <class T> class Vector{
    private:
     size_t capacity=0;
     size_t currentSize;
     T* vec;
        
    public:
     
     Vector(size_t c);
     Vector(size_t c, T x);
     Vector();
     ~Vector();
     size_t Capacity();
     size_t Size();
     void push(T x);
     void pop();
     T front();
     T back();
     T operator[](size_t i);
     int partition(int low, int high);
     void quicksort(int low, int high);
     void sort();
     void swap(T* a,T* b);
     void printarray();
         
    protected:
    size_t partition();
    };
 
template <class T> Vector<T>::Vector(size_t c)//create a vector of capacity c
{
    vec=new T[c];
    capacity=c;
    currentSize = 0;
}
template <class T> Vector<T>::Vector(size_t c, T x)//create a vector of capacity c and initialise all values to x
{
    vec=new T[c];   
    capacity=c;
    for(size_t i=0;i<c;i++)
    {
        vec[i]=x;
    }
    currentSize = c;
}
template <class T>Vector<T>::Vector()//create a vector of capacity 1 and type T
{
    vec=new T[1];
      capacity=1;   
    currentSize =0;
}
template <class T>Vector<T>::~Vector()//destructor function
{
 delete [] vec;
}
template <class T>size_t Vector<T>::Capacity()//returns the capacity of the array
{
    return capacity;
}
template <class T>size_t Vector<T>::Size()//returns the current size of the array
{
    return currentSize;
}    
template <class T>void Vector<T>::push(T x)
{
  if(capacity==currentSize)
  {
      capacity=2*capacity;
      T* ptr=new T[capacity];
      for(size_t i=0;i<currentSize;i++)
      {
          ptr[i]=vec[i];
      }
       delete[] vec;
      vec=ptr;
      vec[currentSize]=x;
      currentSize++;
  }
    else
    {
      vec[currentSize]=x;
      currentSize++;
    }
}    

template <class T>void Vector<T>::pop()
{
    if(currentSize==0)
    {
        return;
    }
    currentSize=currentSize-1;
}

template <class T>T Vector<T>::front()//returns the first element in the array if present
{
    if(currentSize==0)
    {
        return -1;
    }
    return vec[0];
}   

template <class T>T Vector<T>::back()//returns last element in the array if present
{
    if(currentSize==0)
    {
        return -1;
    }
    return vec[currentSize-1];
}   

template <class T>T Vector<T>::operator[](size_t i)
{
    if(i>=currentSize)
    {
        return -1;
    }
    return vec[i];
}
 template <class T>void Vector<T>::swap(T* a, T* b) 
{ 
    T t = *a; 
    *a = *b; 
    *b = t; 
}
template <class T>int Vector<T>:: partition (int low, int high) 
{ 
    T pivot = vec[low]; // pivot 
    int i = low ; // Index of smaller element and indicates the right position of pivot found so far
 
    for (int j = low+1; j <= high ; j++) 
    { 
        // If current element is smaller than the pivot 
        if (vec[j] <= pivot) 
        { 
            i++;    // increment index of smaller element 
            swap(&vec[i],&vec[j]);
        } 
    } 
           
            swap(&vec[i],&vec[low]);
    return i; 
} 

template <class T>void Vector<T>:: quicksort(int low, int high) //quicksort function
{ 
    if (low < high) 
    { 
        int pi = partition(low, high); 

        quicksort(low, pi - 1); 
        quicksort(pi + 1, high); 
    } 
} 
 
template <class T>void Vector<T>:: printarray() //printing the resluting sorted array
{ 

    for (size_t i = 0; i < currentSize; i++) 
    {
     cout << vec[i] << " "; 
    }
    cout<<endl;
}

template <class T>void Vector<T>:: sort()//sort function without any parameters
{
    quicksort(0,currentSize-1);
    printarray();
} 

int Convert(string s,size_t p,size_t l)// converts string to integer starting from index p to l
{
 
    int res =0;
      for(size_t i= p;i<l;i++)
     {
        res = res*10 + s[i]-'0';
     }
    return res;
}


int main() {
    
    string s;
    getline(cin,s);//reads thefirst line of the input
     int q;
     cin>>q;

     size_t p=0,k=0;
    int c=0;
    for(size_t i=0;i<s.size();i++)
    {
        if(s[i] == ' ')
        {
            if(p==0)
            {
                p=i;//finds the index of first space 
            }
            else if(k==0)
            {
                k= i;//finds the index of second space
            }
            c++;//finds number of spaces
        }
     
    }
    
   if(s.size() == 6 || s.size() == 7)
   {
       Vector<int> v;
       int i=0;
       while(i<q)
    {
        string str;
        cin>>str;
        int res ;
        if(str == "push")
        {
            int x;
            cin>>x;
            v.push(x);
        }
       else 
           if(str == "pop")
        {
          v.pop();  
        }
        else
            if(str == "front")
        {
            res = v.front();
            cout<<res<<endl;
        }
        else
            if(str == "back")
        {
            res = v.back();
            cout<<res<<endl;
        }
        else 
            if(str == "capacity")
        {
           res = v.Capacity();
            cout<<res<<endl;
            
        }
       else 
           if(str == "size")
       {
            res = v.Size();
            cout<<res<<endl;
       }
       else 
           if(str == "element")
       {
           int x;
           cin>>x;
           res = v[x];
           cout<<res<<endl;   
       }
       else
       {
           v.sort();
       }
           i++;
    }
   }
    
   else if((c==1 && s.size()!= 7) ||  (c==2 && k == s.size()-1))
    {
       int r=0;
       if(c==1)
       {
         r = Convert(s,7,s.length());
       }
       
        Vector<int> v(r);
 
   for(int i=0;i<q;i++)
     {
        string str;
        cin>>str;
        int res ;
        if(str == "push")
        {
            int x;
            cin>>x;
            v.push(x);
        }
       else if(str == "pop")
        {
          v.pop();  
        }
        else if(str == "front")
        {
            res = v.front();
            cout<<res<<endl;
        }
        else if(str == "back")
        {
           size_t res = v.back();
            cout<<res<<endl;
        }
        else if(str == "capacity")
        {
           size_t res = v.Capacity();
            cout<<res<<endl;
            
        }
       else if(str == "size")
       {
           size_t res = v.Size();
            cout<<res<<endl;
       }
       else if(str == "element")
       {
           int x;
           cin>>x;
          int res = v[x];
           cout<<res<<endl;
           
       }
       else
       {
           v.sort();
       }
     }
    }
    else
    {
      int t=0;
        
        int r = Convert(s,p+1,k);
        if(c==2)
        {
            t= Convert(s,k+1,s.length());
        }
     
        Vector<int> v(r,t);
 
   for(int i=0;i<q;i++)
    {
        string str;
        cin>>str;
        int res ;
        if(str == "push")
        {
            int x;
            cin>>x;
            v.push(x);
        }
       else 
           if(str == "pop")
        {
          v.pop();  
        }
        else 
            if(str == "front")
        {
            res = v.front();
            cout<<res<<endl;
        }
        else 
            if(str == "back")
        {
           res = v.back();
            cout<<res<<endl;
        }
        else 
            if(str == "capacity")
        {
           size_t r = v.Capacity();
            cout<<r<<endl;   
        }
       
       else 
           if(str == "size")
       {
           size_t r = v.Size();
            cout<<r<<endl;
       }
       
       else 
           if(str == "element")
       {
           
           int x;
           cin>>x;
           res = v[x];
           cout<<res<<endl;
           
       }
       
       else
       {
           v.sort();
       }
     }
    }
   
    return 0;
}