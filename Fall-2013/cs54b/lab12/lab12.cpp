//name: CHRIS PEABODY
//class: CS54 section B
//date: 11/12/2013
//file: lab12.cpp
//purpose: 

#include <iostream>
#include "compound.h"
using namespace std;

int main()
{
  Compound one;
  Compound two;
  Compound three;
  Compound four;

  //output first without doing anything
  cout<<one<<endl;

  //prompt for second and third
  cout<<"Enter first compound: ";
  cin>>two;
  cout<<"Enter second compound: ";
  cin>>three;

  //Add second and third compounds together
  two+three;
  four=two;
  cout<<four<<endl;

  //multiply by 13.4
  four*13.4;

  cout<<four<<endl;

  return 0;
}