//Chris Peabody - CS153
//3/19/2014
//file: pack2d.cpp
//purpose:

#include "abstractpackage.h"
#include "pack2d.h"
#include <iostream>
using namespace std;

float pack2d::getCharge() const
{
  return m_x*m_y*RATE_2D;
}