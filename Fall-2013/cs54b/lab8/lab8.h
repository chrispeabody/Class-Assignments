//Name: CHRIS PEABODY
//Class: CS54 section B
//Date: 10/15/2013
//File: lab8.h
//Purpose: To sort arrays of numbers

#ifndef lab8_h
#define lab8_h

#include <iostream>
#include <ctime>
#include <cstdlib>
using namespace std;

//----TEMPLATES----//

//Desc: Swaps two values
//Pre: none
//Post: The two variables will swap values
template <typename T>
void swapVals(T & val1, T & val2)
{
  T temp = val1;
  val1 = val2;
  val2 = temp;

  return;
}

//Desc: finds the smallest index further in the array
//Pre: none
//Post: index of min number will be returned
template <typename T>
short smallestIndex(const T array[], const short start, const short end)
{
  short index, index_of_min = start;
  T min = array[start];
  for(index = start+1; index < end; index++)
  {
    if(array[index] < min)
    {
      min = array[index];
      index_of_min = index;
    }
  }

  return index_of_min;
}

//Desc: Sorts the array from least to greatest
//Pre: none
//Post: array is sorted
template <typename T>
void selection_sort(T array[], const short datasize)
{
  short nextSmall, index;
  cout<<endl; //TEST
  for(index=0; index < datasize-1; index++)
  {
    nextSmall = smallestIndex(array, index, datasize);
    swapVals(array[index], array[nextSmall]);
  }

  return;
}

//Desc: Displays all values in an array
//Pre: none
//Post: All values displayed
template <typename T>
void displayArray(const T array[], const int arraySize)
{
  cout<<endl;
  for(int i = 0; i < arraySize; i++)
  {
    cout<<array[i]<<endl;
  }
  cout<<endl;

  return;
}

//----PROTOTYPES----//

//Desc: fills the integer array with random values
//Pre: none
//Post: randomized ints will be between 0 and 30
void randomize(int array[], const int arraySize);

//Desc: fills the float array with random values
//Pre: none
//Post: randomized floats will be between 0 and 1 inclusive
void randomize(float array[], const int arraySize);

#endif