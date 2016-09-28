//name: CHRIS PEABODY
//class: CS54 section B
//date: 11/19/2013
//file: cat.cpp

#include "cat.h"
#include <iostream>
using namespace std;

cat::cat()
{
  
}

void cat::print()
{
  cout << m_name << " (" << g << ")";
  return;
}