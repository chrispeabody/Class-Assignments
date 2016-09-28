//name: CHRIS PEABODY
//class: CS54 section B
//date: 12/3/2013
//file: lab14
//purpose: a driver for the lab

#include <iostream>
#include "function_def.h"
using namespace std;

int main()
{
  const int MAX = 10;

  int myArray1[MAX]= {1, 2, 3, 4, 5, 6, 7}; 
  float myArray2[MAX]= {2.1, 4.5, 6.9, 8.4, 9.1};
  char myArray3[MAX] = {'C', 'D', 'G', 'K', 'L', 'O', 'O', 'U'};

  int descArr1[MAX];
  float descArr2[MAX];
  char descArr3[MAX];

  cout<<"The normal arrays: "<<endl;
  printArray(myArray1, 7);
  printArray(myArray2, 5);
  printArray(myArray3, 8);

  insertToArray(myArray1, 7, 7);
  insertToArray(myArray2, 5, (float)1.2);
  insertToArray(myArray3, 8, 'S');

  cout<<"The inserted arrays: "<<endl;
  printArray(myArray1, 8);
  printArray(myArray2, 6);
  printArray(myArray3, 9);

  descendingOrder(myArray1, 8, descArr1);
  descendingOrder(myArray2, 6, descArr2);
  descendingOrder(myArray3, 9, descArr3);

  cout<<"Descending order arrays: "<<endl;
  printArray(descArr1, 8);
  printArray(descArr2, 6);
  printArray(descArr3, 9);

  return 0;
}