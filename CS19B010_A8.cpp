#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;
int minimum(int a,int b,int c) //finds the minimum of the three integers a,b,c
{
  return min(min(a,b),c);
}
class EDD
{
  private:
  string s1,s2;
  int edit[101][101];
  int check=0;                  //check bit to find whether compdist is performed before dist or not
  int check_assign=0;           //check bit to find whether assign is performed before the required functions
  
  public:
 
  void assign(string a,string b);
  int compdist();
  int dist();
  void table();
};

void EDD::assign(string a, string b)//assigns the given input strings to private class variables
{
  check=0;
  check_assign=1;
  s1=a;
  s2=b;
}

int EDD::compdist()
{
  if(check_assign==0)           //if the strings are not initialised exception need to be thrown
  {
   throw  "strings not found!";
  }
  check=1;
  check_assign==0;
  int m=s1.size();
  int n=s2.size();
  
  int ins,del,rep;
   for(int j=0;j<n+1;j++)
   {
     edit[0][j]=j;              //when size of first string is 0 and second string is j it requires j steps to edit
   }
   
   for(int i=1;i<m+1;i++)
   {
     edit[i][0]=i;              //when size of second string is 0 and first string is i it requires i steps to edit
   
      for(int j=1;j<n+1;j++)
     {
      ins=edit[i][j-1]+1;       //when first string is smaller than second by one letter that letter insertion need to be done
      
      del=edit[i-1][j]+1;        //when first string is larger than second by one letter that letter deletion need to be done
        
         if(s1[i-1]==s2[j-1])
        {
          rep=edit[i-1][j-1];   //if the last letter that we see is same then no change is required
        }
        
         else
        {
          rep=edit[i-1][j-1]+1;  //if the last letter is not same then to edit that one step is to be done
        }
        
        edit[i][j]=minimum(ins,del,rep);
      } 
      
   }
   return edit[m][n];
}
int EDD::dist()
{
  if(check_assign==0)               //if the strings are not initialised exception need to be thrown
  {
   throw  "strings not found!";
  }
  check_assign==0;
  if(check==1)
  {
   int m=s1.size();
   int n=s2.size();
   return edit[m][n];
  }
  return compdist();

}

void EDD::table()                   //printing the edit array
{
    if(check_assign==0)             //if the strings are not initialised exception need to be thrown
  {
   throw  "strings not found!";
  }
  check_assign==0;
   int m=s1.size();
   int n=s2.size();
   if(check==1)
   {
     for(int i=1;i<m+1;i++)
     {
      for(int j=1;j<n+1;j++)
      {
        cout<<edit[i][j]<<" ";
      }
      cout<<endl;
     }
     return;
   }
   compdist();
         for(int i=1;i<m+1;i++)
     {
      for(int j=1;j<n+1;j++)
      {
        cout<<edit[i][j]<<" ";
      }
      cout<<endl;
     }
   
}

int main() {
    /* Enter your code here. Read input from STDIN. Print output to STDOUT */
     EDD obj;
   //  obj.create();
     string inpt,in1,in2;
     int q;
     cin>>q;
     for(int i=0;i<q;i++)
     {
       cin>>inpt;
       
        if(inpt=="assign")
       {
         cin>>in1>>in2;
         obj.assign(in1,in2);
       }
       else
        if(inpt=="compdist")
       {
         try{
         obj.compdist();
         }
         catch(const char* msg)
         {
           cout<<msg<<endl;
         }
       }
       
       else
        if(inpt=="dist")
        {
         try{
         int d=obj.dist();
          cout<<d<<endl;
        }
         catch(const char* msg)
         {
           cout<<msg<<endl;
         }
        
        }
       else
        if(inpt=="table")
        {
         try{
         obj.table();
         }
         catch(const char* msg)
         {
           cout<<msg<<endl;
         }
         
        }
     }
    return 0;
}
