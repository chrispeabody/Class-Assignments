//name: CHRIS PEABODY
//class: CS54 section B
//date: 11/19/2013
//file: farm.h
//purpose: header for the farm template class

#ifndef FARM_H
#define FARM_H

#include <iostream>
using namespace std;

const int MAX = 50;

template <class T_animal>
class farm
{
  public:
    farm():m_herdSize(0){}
    void addAnimal(T_animal anim);
    void printAnimals();
  private:
    T_animal my_herd[MAX];
    int m_herdSize;
};

template <class T_animal>
void farm<T_animal>::addAnimal(T_animal anim)
{
  if (m_herdSize<MAX)
  {
    my_herd[m_herdSize] = anim;
    m_herdSize++;
  }
}

template <class T_animal>
void farm<T_animal>::printAnimals()
{
  for(int i=0; i < m_herdSize; i++)
  {
    my_herd[i].print();
    if (i==m_herdSize-1)
    {
      cout<<". "<<endl;
    }
    else
    {
      cout<<", ";
    }
  }
}

#endif