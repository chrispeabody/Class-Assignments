//Chris Peabody - CS153
//3/19/2014
//file: pack4d.h
//purpose:

#ifndef PACK4D_H
#define PACK4D_H

#include "abstractpackage.h"
#include <iostream>
using namespace std;

const float RATE_HVOL = 0.01;
const float RATE_4D = 3.14;
const float HANDLING = 42.42;

class pack4d : public AbstractPackage
{
  private:
    float m_x;
    float m_y;
    float m_z;
    float m_t;
    float m_weight;
  public:
    // Purpose: Default Constructor
    pack4d(string f, string t) : AbstractPackage(f, t) {}

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
    void setDim(float x, float y, float z, float t, float w)
    {
        m_x=x;
        m_y=y;
        m_z=z;
        m_t=t;
        m_weight=w;
    }
};

#endif