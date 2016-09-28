//Name: CHRIS PEABODY
//Class: CS54 section B
//Date: 10/8/2013
//File: lab7.cpp
//Purpose: To convert a given pixel to grayscale

#include <iostream>
#include "lab7.h"
using namespace std;

int main()
{
  char ans; //Used to handle y/n prompts
  Pixel pix; //the pixel used throughout

  do
  {
    pix = getPixel();
    output(pix,rgbToGray(pix));

    do
    {
      cout<<"\nWould you like to enter another pixel? (y/n)\nAnswer: ";
      cin>>ans;
    } while(ans!='y'&&ans!='n');
  } while(ans!='n');

  return 0;
}