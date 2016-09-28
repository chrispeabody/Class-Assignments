//Name: CHRIS PEABODY
//Class: CS54 section B
//Date: 10/15/2013
//File: lab8.cpp
//Purpose: To sort arrays of numbers

#include <iostream>
#include <ctime>
#include <cstdlib>
#include "lab8.h"
using namespace std;

int main()
{
  srand(time(NULL));

  //Create and randomize arrays
  int ints[21];
  float floats[21];

  randomize(ints, 21);
  randomize(floats, 21);

  //Display arrays
  cout<<"\nIntegers:"<<endl;
  displayArray(ints, 21);
  cout<<"\nFloats:"<<endl;
  displayArray(floats, 21);

  //Sort and redisplay
  selection_sort(ints, 21);
  selection_sort(floats, 21);

  cout<<"\nSorting. . ."<<endl;

  cout<<"\nIntegers:"<<endl;
  displayArray(ints, 21);
  cout<<"\nFloats:"<<endl;
  displayArray(floats, 21);

  return 0;
}