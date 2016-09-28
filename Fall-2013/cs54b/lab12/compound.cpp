//name: CHRIS PEABODY
//class: CS54 section B
//date: 11/12/2013
//file: compound.cpp
//purpose: implementation of compound class

#include <iostream>
#include "compound.h"
using namespace std;

Compound::Compound()
{
  m_name = "unknown";
  m_kg = 0;
  for(int i = 0; i < ELEMENT_COUNT; ++i)
  {
    m_elements[i] = 0;
  }
}

Compound Compound::operator*(const float amount)
{
  m_kg*=amount;

  return *this;
}

Compound& Compound::operator+(const Compound& other)
{
  m_name = m_name+"-"+other.m_name;
  for(int i = 0; i < ELEMENT_COUNT; ++i)
    m_elements[i]+=other.m_elements[i];
  
  m_kg = m_kg+other.m_kg;

  return *this;
}

ostream& operator<<(ostream& stream, Compound& value)
{
  stream<<value.m_name<<" ("<<value.m_kg<<") ";
  for(int i = 0; i < ELEMENT_COUNT; ++i)
  {
    if (value.m_elements[i]>0)
    {
      stream<<i<<" "<<value.m_elements[i]<<", ";
    }
  }

  return stream;
}

istream& operator>>(istream& stream, Compound& value)
{
  int numElements; //TEMP variables
  int location;
  int num;

  stream>>value.m_name;
  stream>>numElements;
  for(int i = 0; i < numElements; ++i)
  {
    stream>>location;
    stream>>num;
    value.m_elements[location]=num;
  }
  stream>>value.m_kg;

  return stream;
}