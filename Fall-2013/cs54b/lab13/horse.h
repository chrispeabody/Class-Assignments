//name: CHRIS PEABODY
//class: CS54 section B
//date: 11/19/2013
//file: horse.h
//purpose: header file for the horse struct

#ifndef HORSE_H
#define HORSE_H

#include <iostream>
using namespace std;

struct horse
{
  private:
    string m_name;
    char g;
  public:
    horse();
    horse(string n, char gend):m_name(n),g(gend){}
    void print();
};

#endif
