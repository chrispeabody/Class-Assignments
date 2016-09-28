//name: CHRIS PEABODY
//class: CS53, section A
//date: 11/11/2013
//file: h9.cpp
//purpose: driver for the customer and business classes

#include <iostream>
#include <ctime>
#include <cstdlib>
#include "customer.h"
#include "business.h"
using namespace std;

int main()
{
  srand(time(NULL)); //seed randoms

  cout<<endl;

  customer joe("Joe Blow", 9001);
  customer john("John Doe", 400);
  customer jane("Jane Doe", 340);

//TEST
  cout<<joe.getPur();

  business TTRWFM("Things-That-Rhyme-With-Frog Mart",666);
  TTRWFM.addCustomer(joe);
  TTRWFM.addCustomer(john);
  TTRWFM.addCustomer(jane);

  TTRWFM.make_a_sale();
  TTRWFM.make_a_sale();
  TTRWFM.make_a_sale();

//TEST
  cout<<joe.getPur();


  TTRWFM.print();

  joe.print();
  john.print();
  jane.print();

  cout<<endl;

  return 0;
}