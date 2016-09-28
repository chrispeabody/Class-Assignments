//Chris Peabody - CS153
//3/19/2014
//file: pack4d.cpp
//purpose:

#include "abstractpackage.h"
#include "pack4d.h"
#include <iostream>
using namespace std;

float pack4d::getCharge() const
{
  return (m_x*m_y*m_z*m_t)*RATE_HVOL+m_weight*RATE_4D+HANDLING;
}