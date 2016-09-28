//CHRIS PEABODY
//8-26-2014
//algor.cpp
//Purpose: Find all groups (a,b,c) <= n where a^2+b^2=c^2

#include <iostream>
#include <cmath>
using namespace std;

int main()
{
  int n;
  float c;

  cout<<"What is N-> ";
  cin>>n;

  for (int a = 1; a <= n; a++)
  {
    for(int b = a; b <= n; b++)
    {
      c=sqrt(float(a*a+b*b));
      if (!(c-int(c)>0) && (c<=n)) //integer and <= n
        cout<<"a: "<<a<<" b: "<<b<<" c: "<<c;
    }
  }

  return 0;
}