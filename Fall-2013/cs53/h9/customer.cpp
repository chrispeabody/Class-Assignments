//name: CHRIS PEABODY
//class: CS53, section A
//date: 11/11/2013
//file: customer.cpp
//purpose: implementation of customer class

#include "customer.h"

customer::customer(const string n, const float m)
{
  m_nam = n;
  m_mon = m;
  m_numPur = 0;
}

bool customer::purchase(const string item)
{
  bool success = false;

  if (m_mon>=40)
  {
    if (m_numPur<20)
    {
      m_mon-=40;
      m_purchases[m_numPur]=item;
      m_numPur++;
      cout<<m_numPur; //TEST
      success = true;
    }
  }
  
  return success;
}

//THERE IS TROUBLE HERE
//THE m_numPur VARIABLE IS ALWAYS ZERO? NO ITEMS OUTPUT
void customer::print()
{
  cout<<"\n"<<m_nam<<" has $"<<m_mon<<" and purchases ";
  for(int i = 0; i <= m_numPur; ++i)
  {
    cout<<m_numPur<<m_purchases[0]; //TEST
    cout<<m_purchases[i];
    cout<<" ";
  }

  return;
}