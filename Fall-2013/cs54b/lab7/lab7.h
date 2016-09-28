//Name: CHRIS PEABODY
//Class: CS54 section B
//Date: 10/8/2013
//File: lab7.h
//Purpose: To convert a given pixel to grayscale

#ifndef lab7_h
#define lab7_h

#include <iostream>
using namespace std;

//CONSTANTS
const float MULRED = 0.2126;   //red to gray multiple
const float MULGREEN = 0.7152; //green to gray multiple
const float MULBLUE = 0.0722;  //blue to gray multiple

//STRUCTURES
struct Pixel
{
  float m_red;
  float m_green;
  float m_blue;
};

//TEMPLATED FUNCTION
template <typename T>
T rgbToGray(const T red, const T green, const T blue)
{
  return (red*MULRED)+(green*MULGREEN)+(blue*MULBLUE);
}

//PROTOTYPES

//Desc: Takes in a pixel and puts it's values into the template function
//Pre: Pixel p's RGB values must be initialized
//Post: The grayscale value from the pixel's RGB is returned
float rgbToGray(const Pixel p);

//Desc: Shows the pixel's RGB value and it's grayscale value
//Pre: none
//Post: Outputs the RGB and grayscale values
void output(const Pixel p, const float grayValue);

//Desc: Obtains the rgb values for a pixel from the user
//Pre: none
//Post: A pixel with an RGB value will be returned
Pixel getPixel();

#endif