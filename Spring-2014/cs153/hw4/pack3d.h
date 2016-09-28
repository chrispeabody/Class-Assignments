//Chris Peabody - CS153
//3/19/2014
//file: pack3d.h
//purpose:

#ifndef PACK3D_H
#define PACK3D_H

#include "abstractpackage.h"
#include <iostream>
using namespace std;

const float RATE_VOL = 0.02;
const float RATE_3D = 2.71;

class pack3d : public AbstractPackage
{
  private:
    float m_x;
    float m_y;
    float m_z;
    float m_weight;
  public:
    // Purpose: Default Constructor
    pack3d(string f, string t) : AbstractPackage(f, t) {}

    // Purpose: Returns the charge of a package.
    // -- VIRTUAL
    virtual float getCharge() const;

    // Purpose: Returns the package's sender.
    // -- VIRTUAL, INLINE
    virtual string getFrom() const {return m_from;}

    // Purpose: Returns the package's receiver.
    // -- VIRTUAL, INLINE
    virtual string getTo() const {return m_to;}

    // Purpose: Sets the dimensions/weight of the package
    void setDim(float x, float y, float z, float w) {m_x=x; m_y=y; m_z=z; m_weight=w;}
};

#endif