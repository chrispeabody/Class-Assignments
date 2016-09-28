//Name: CHRIS PEABODY
//Class: CS54 section B
//Date: 11/5/2013
//file: Speed_recorder.cpp
//purpose: the meat of our special class

#include <iostream>
#include "Speed_recorder.h"
using namespace std;

void Speed_recorder::addSpeed(const int speed)
{
  m_numEntries++;
  m_totSpeeds+=speed;
  m_avgSpeed=m_totSpeeds/m_numEntries;

  return;
}

int Speed_recorder::getId()
{
  return m_id;
}

int Speed_recorder::getTotalEntries()
{
  return m_numEntries;
}

float Speed_recorder::getAverageSpeed()
{
  return m_avgSpeed;
}