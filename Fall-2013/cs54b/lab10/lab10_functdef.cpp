//Name: CHRIS PEABODY
//Class: CS54 section B
//Date: 10/29/2013
//File: lab10_functdef.cpp
//Purpose: Decode encrypted messages from a file

#include "lab10.h"
#include <iostream>
#include <fstream>
using namespace std;

void cypher(string ifile, string ofile, int factor)
{
  char current; //current char being handled

  ifstream input;
  input.open(ifile.c_str());

  ofstream output;
  output.open(ofile.c_str());

  current = input.get();
  while(!input.eof())
  {
    if (isupper(current))
    {
      current += factor;
      if (current < 65)
        current += 26;
      if (current > 90)
        current -=26;
    }

    output<<current;

    current = input.get();
  }

  return;
}