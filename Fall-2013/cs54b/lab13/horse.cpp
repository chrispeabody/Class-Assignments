//name: CHRIS PEABODY
//class: CS54 section B
//date: 11/19/2013
//file: horse.cpp
//purpose: implementation for the horse struct

#include "horse.h"
#include <iostream>
using namespace std;

horse::horse()
{
  
}

void horse::print()
{
  cout << m_name << " (" << g << ")";
  return;
}