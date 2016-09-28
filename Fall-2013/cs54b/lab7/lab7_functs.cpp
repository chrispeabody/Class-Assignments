//Name: CHRIS PEABODY
//Class: CS54 section B
//Date: 10/8/2013
//File: lab7_functs.cpp
//Purpose: To turn a given pixel to grayscale

#include <iostream>
#include "lab7.h"
using namespace std;

float rgbToGray(const Pixel p)
{
  float result;
  result = rgbToGray(p.m_red,p.m_green,p.m_blue);

  return result;
}

void output(const Pixel p, const float grayValue)
{
  int val = static_cast<int>(grayValue);
  cout<<"("<<p.m_red<<", "<<p.m_green<<", "<<p.m_blue<<")";
  cout<<" --> "<<val<<endl;

  return;
}

Pixel getPixel()
{
  Pixel result;
  cout<<"\nRed: ";
  cin>>result.m_red;
  cout<<"Green: ";
  cin>>result.m_green;
  cout<<"Blue: ";
  cin>>result.m_blue;
  cout<<endl;

  return result;
}

/*
I found it much easier to use floats than characters.
So I change the variable types throughout and it works perfectly
*/