//Chris Peabody - CS153
//3/19/2014
//file: pack3d.cpp
//purpose:

#include "abstractpackage.h"
#include "pack3d.h"
#include <iostream>
using namespace std;

float pack3d::getCharge() const
{
  return (m_x*m_y*m_z)*RATE_VOL+m_weight*RATE_3D;
}