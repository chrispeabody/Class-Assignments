//Name: CHRIS PEABODY
//Class: CS54 section B
//Date: 10/29/2013
//File: lab10.cpp
//Purpose: Decode encrypted messages from a file

#include "lab10.h"
#include <iostream>
#include <fstream>
using namespace std;

int main()
{

  string ifile, ofile; //The file to open
  int factor; //The number to shift by

  cout<<"\nGreetings. Let's begin, shall we?"<<endl;

  cout<<"\nWhat file do you want to decode?\nFilename: ";
  cin>>ifile;

  cout<<"\nWhat file do you want to send to?\nFilename: ";
  cin>>ofile;

  cout<<"\nWhat is the cypher shift factor?\nFactor: ";
  cin>>factor;

  cypher(ifile, ofile, factor);

  cout<<"\nProcessing complete."<<endl;

  cypher("bonus.txt","bonusout.txt",-4);

  return 0;
}
