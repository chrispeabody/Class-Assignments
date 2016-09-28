//Name: CHRIS PEABODY
//Class: CS54 section B
//Date: 10/15/2013
//File: lab8_funct.cpp
//Purpose: To sort arrays of numbers

#include <iostream>
#include <ctime>
#include <cstdlib>
#include "lab8.h"
using namespace std;

//Int randomize
void randomize(int array[], const int arraySize)
{
  for(int i = 0; i < arraySize; i++)
  {
    array[i] = (rand()%30);
  }

  return;
}

//Float randomize
void randomize(float array[], const int arraySize)
{
  for(int i = 0; i < arraySize; i++)
  {
    array[i] = (float)rand()/(float)RAND_MAX;
  }

  return;
}