//CHRIS PEABODY
//4/15/2014
//file: arraystack.cpp
//purpose: fucntion defs for the array stack class

#include "abstractstack.h"
#include <iostream>
using namespace std;

template <typename T>
void arrayStack<T>::clear()
{
  m_top = 0;
}

template <typename T>
void arrayStack<T>::push(const T& x)
{ 
  if(m_top==m_max)
  {
    T* tmp = new T[m_max*2];
    for(int k=0; k<m_top; k++)
      tmp[k]=m_data[k];
    delete []m_data;
    m_data = tmp;
    m_max *= 2; 
  }

  m_data[m_top]=x;
  m_top++;
}

template <typename T>
void arrayStack<T>::pop()
{
  if (m_top>0)
    m_top--;

  if(m_top < m_max/4)
  {
    T* tmp = new T[m_max/2];
    for(int k=0; k<m_top; k++)
      tmp[k]=m_data[k];
    delete []m_data;
    m_data = tmp;
    m_max /= 2;
  }
}

template <typename T>
const T& arrayStack<T>::top() const throw ( Oops )
{
  if (m_top>0)
    return m_data[m_top-1];
  else
    throw Oops::Oops("Cannot find top() of empty stack!");
}

template <typename T>
bool arrayStack<T>::isEmpty() const
{
  return (m_top==0);
}
