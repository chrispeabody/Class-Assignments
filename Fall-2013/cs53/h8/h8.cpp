//name: CHRIS PEABODY
//class: CS 53 section A
//date: 10/22/2013
//file: h8.cpp
//Purpose: To create Moe fables!

#include "h8.h"
#include <iostream>
#include <ctime>
#include <cstdlib>
#include <fstream>
#include <sstream>
#include <cstring>
using namespace std;

int main()
{
  string fable; //Fable filename
  char ans; //Used for y/n questions

  srand(time(NULL));

  do
  {
    cout<<"\nSo, Moe, are you ready to create a fable? (y/n): ";
    cin>>ans;
  } while (ans!='y'&&ans!='n');

  if (ans=='y')
  {
    do
    {
      //Randomize fable
      randomFable(fable);

      //Do replacing and saving to file
      replaceWords(fable);


      do
      {
        cout<<"\nWould you like to make another fable, Moe? (y/n): ";
        cin>>ans;
      } while (ans!='y'&&ans!='n');
    } while (ans=='y');
  }

  cout<<"\nSee yah later."<<endl;

  return 0;
}