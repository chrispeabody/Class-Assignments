//Chris Peabody
//2-6-2014
//CS153
//purpose: To test the gmatrix class
//file: driver.cpp

#include <iostream>
#include "gmatrix.h"
using namespace std;

int main()
{
  GMatrix kris(10, 3, 2, 3);
  GMatrix chris(2, 8, 4, 7);

  cout<<"A 10 by 3:"<<endl;
  cout<<kris<<endl;
  cout<<"A 2 by 8:"<<endl<<chris<<endl;

  kris = chris;
  cout<<"Setting first to equal second. Displaying first."<<endl<<kris<<endl;

  cout<<"Creating new matrix from first, displaying:"<<endl;
  GMatrix cris(kris);
  cout<<cris<<endl;

  return 0;
}
