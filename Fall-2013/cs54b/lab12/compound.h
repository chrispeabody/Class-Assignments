//name: CHRIS PEABODY
//class: CS54 section B
//date: 11/12/2013
//file: compound.h
//purpose: definition of compound class

#include <iostream>
using namespace std;

const int ELEMENT_COUNT = 112;

class Compound
{
  private:
    string m_name;
    int m_elements[ELEMENT_COUNT];
    float m_kg;

    public:
    // Desc: Default Constructor
    // Pre: None
    // Post: Name is initialized to "unknown, mass is initialized to zero, and
    //    all elements are initialized to zero.
    Compound();

    // Desc: multiplies kilogram value by the number sent
    // Pre: none
    // Post: returns the result of multiplying the kilogram value of the compound
    //    by the number passed to the function
    Compound operator*(const float amount);

    // Desc: "combines" the passed compound with the calling one
    // Pre: none
    // Post: The result's name is in firstcompound-secondcompound format
    //    each array value is that of the two compound's array values added
    //    the kilogram value is the sum of the two compound's kilogram values
    Compound& operator+(const Compound& other);

    // Desc: outputs the compound
    // Pre: none
    // Post: outputs the name, the kilogram value, and the list of elements
    //    and number of atoms of each in the compound
    friend ostream& operator<<(ostream& stream, Compound& value);

    // Desc: reads in a compound
    // Pre: compound is in form [name X a 1 b 2 ... k]
    // Post: will read the values into the compound
    friend istream& operator>>(istream& stream, Compound& value);
};