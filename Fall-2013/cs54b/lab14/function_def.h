//name: CHRIS PEABODY
//class: CS54 section B
//date: 12/3/2013
//file: function_def.h
//purpose: to define the template functions required

#ifndef FUNCTION_DEF_H
#define FUNCTION_DEF_H

#include <iostream>
using namespace std;

//Desc: Will insert an element into the array where it fits
//Pre: given array must be in ascending order
//Post: The new array size is returned
template <typename T>
T insertToArray(T myArray[], const int size, const T element) 
{ 
  T tmp;
  bool notSwapped = true; 
  for (int i=0; i< size; i++) 
  { 
    if(myArray[i] >=element && notSwapped) 
    { 
      tmp = myArray[i]; 
      myArray[i] = element; 
      for (int j=size-1; j<i;j--) 
      { 
        myArray[j+1] = myArray[j]; 
      }
      myArray[i+1] = tmp;
      notSwapped = false; 
    } 
  }
  return size+1; 
}

//Desc: puts all the elements in the array into another array, in descending order
//Pre: source array must be in ascending order
//Post: destin[] will contain all the elements in descending order
template <typename T>
void descendingOrder(const T source[], const int size, T destin[])
{
  for (int i = 0; i < size; i++)
  {
    destin[i]=source[size-1-i];
  }

  return;
}

//Desc: Prints to the screen all elements in the array
//Pre: none
//Post: Elements printed on screen
template <typename T>
void printArray(const T myArray[], const int size)
{
  for(int i = 0; i < size; i++)
  {
    cout<<myArray[i];
    if (i!=size-1)
      cout<<", ";
    else
      cout<<endl;
  }

  return;
}

#endif