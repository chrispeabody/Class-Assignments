//name: CHRIS PEABODY
//class: CS 54 section B
//date: 10/22/2013
//file: lab9_functdef.cpp
//purpose: to mimic a login server

#include "lab9.h"
#include <iostream>
using namespace std;

void toAllCaps(char domain[])
{
  for (int i = 0; i<11; i++)
  {
    if (domain[i]>=97&&domain[i]<=122)
      domain[i]-=32;
  }

  return;
}

bool verifyUser(string user)
{
  bool result;

  if (user=="etnc6d"||user=="c_price"||user=="Amy_Briggs"||user=="lasanthi"
  ||user=="nateEloe!!")
    result = true;
  else
    result = false;

  return result;
}

bool verifyPass(string pass)
{
  return (pass==PASS)?true:false;
}