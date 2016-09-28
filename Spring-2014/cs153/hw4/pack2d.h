//Chris Peabody - CS153
//3/19/2014
//file: pack2d.h
//purpose:

#ifndef PACK2D_H
#define PACK2D_H

#include "abstractpackage.h"
#include <iostream>
using namespace std;

const float RATE_2D = 0.05;

class pack2d : public AbstractPackage
{
  private:
    float m_x;
    float m_y;
  public:
    // Purpose: Default Constructor
    pack2d(string f, string t) : AbstractPackage(f, t) {}

    // Purpose: Returns the charge of a package.
    // -- VIRTUAL
    virtual float getCharge() const;

    // Purpose: Returns the package's sender.
    // -- VIRTUAL, INLINE
    virtual string getFrom() const {return m_from;}

    // Purpose: Returns the package's receiver.
    // -- VIRTUAL, INLINE
    virtual string getTo() const {return m_to;}

    // Purpose: Sets the dimensions of the package
    void setDim(float x, float y) {m_x = x; m_y=y;}
};

#endif