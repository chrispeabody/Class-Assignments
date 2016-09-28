//name: CHRIS PEABODY
//class: CS53, section A
//date: 11/11/2013
//file: customer.h
//purpose: definition of customer class

#ifndef CUSTOMER_H
#define CUSTOMER_H

#include <iostream>
#include <ctime>
#include <cstdlib>
#include "product.h"
using namespace std;

//Desc: decides if they want to buy something, if so, randomly chooses an item
//      if they have enough money, they buy it, give the money to the business,
//      and increase happinesss. If not, they decrease happiness
//Pre: none
//Post: happiness will change based on course of action
//void buy_something(business bus);

//Desc: chucks an item at given customer, unless they don't have an item
//Pre: none
//Post: if item exists, it will be thrown and happiness will be increased
//      otherwise, happiness will be decreased
//void chuck(customer cus);

//Desc: takes an item from given customer, if possible
//Pre: none
//Post: if the given customer has an item and the calling one has
//      room in his pockets, the item will be added and his happiness
//      will be increased. Otherwise happiness is decreased
//void rob(customer cus);

//Desc: shows the inclination value of the customer
//Pre: none
//Post: returns m_inclin
//int getInclin(){return m_inclin;}

//Desc: shows the name of the customer
//Pre: none 
//Post: returns the name
//string getName(){return m_nam;}

//Desc: shows the money value of the customer
//Pre: none
//Post: returns the money value
//float getMoney(){return m_mon;}

//Desc: shows the happiness value of the customer
//Pre: none
//Post: returns m_happ
//int getHapp(){return m_happ;}

//Desc: mutator for the customer's money value 
//Pre: none
//Post: m_mon will be equal to the input
//void setMoney(const float m){m_mon = m; return;}

//Desc: mutator for the customer's name value
//Pre: none
//Post: m_nam will be equal to the input
//void setName(const string n){m_nam = n; return;}

//Desc: overloaded insertion operator for the class
//Pre: none
//Post: will print the name, inclination, happiness, and items of the customer
//friend ostream& operator<<(ostream& os, customer cus);

const int POCKETSIZE = 20;

class business;

class customer
{
private:
  product m_purchases[POCKETSIZE]; //All the purchases they have
  short m_numPur; //number of purchases
  float m_mon; //amount of money
  string m_nam; //name
  int m_happ; //The customer's happiness (0-100)
  int m_inclin; //the customer's inclination (-1 for Moe's, 1 for CBG)
public:
  customer(){m_mon=rand()%256+4; m_happ=rand()%81+10;}
  customer(const string n, const float m);
  void buy_something(business bus);
  void chuck(customer cus);
  void rob(customer cus);
  int getInclin(){return m_inclin;}
  string getName(){return m_nam;}
  float getMoney(){return m_mon;}
  int getHapp(){return m_happ;}
  void setMoney(const float m){m_mon = m; return;}
  void setInclin(const int i){m_inclin = i; return;}
  void setName(const string n){m_nam = n; return;}
  friend ostream& operator<<(ostream& os, customer cus);
};

#endif