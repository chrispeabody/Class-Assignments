//name: CHRIS PEABODY
//class: CS54 section B
//date: 11/19/2013
//file: cat.h
//purpose: header for the cat struct

#ifndef CAT_H
#define CAT_H

#include <iostream>
using namespace std;

struct cat
{
  private:
    string m_name;
    char g;
  public:
    cat();
    cat(string n, char gend):m_name(n),g(gend){}
    void print();
};

#endif
