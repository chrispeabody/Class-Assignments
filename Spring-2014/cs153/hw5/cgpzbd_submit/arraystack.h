//CHRIS PEABODY
//4/15/2014
//file: arraystack.h
//purpose: header for the array stack class

#ifndef ARRAYSTACK_H
#define ARRAYSTACK_H

#include <iostream>
#include "abstractstack.h"
using namespace std;

//SEE ABSTRACT STACK TO SEE FUNCTION DOCUMENTATION
template <typename T>
class arrayStack : public AbstractStack<T>
{
private:
  int m_top;
  int m_max;
  T* m_data;
public:
  arrayStack() : m_top(0), m_max(0), m_data(NULL) {};
  virtual void clear();
  virtual void push(const T& x);
  virtual void pop();
  virtual const T& top() const throw ( Oops );
  virtual bool isEmpty() const;
};

#include "arraystack.hpp"

#endif
