//name: CHRIS PEABODY
//class: CS53, section A
//date: 11/11/2013
//file: business.h
//purpose: definition of business class

#ifndef BUSINESS_H
#define BUSINESS_H

#include <iostream>
#include <ctime>
#include <cstdlib>
#include <fstream>
#include "customer.h"
using namespace std;

//Desc: shows the business's name, customers, and items
//Pre: none
//Post: name, items, customers cout'd to console
//void print();

//Desc: puts customer in the business's array of customers
//Pre: none
//Post: customer added to next open spot
//addCustomer(const customer c);

//Desc: makes all customers call their buy_something() function
//Pre: none
//Post: buy_something() called for each customer
//sell_something();

//Desc:
//Pre:
//Post:
//void customers_leave(customer street[], int& num);

//Desc: getter for the name value
//Pre: none
//Post: returns m_nam
//string getName(){return m_nam;}

//Desc: getter for the money value
//Pre: none
//Post: returns m_mon
//float getMoney(){return m_mon;}

//Desc: mutator for the money value
//Pre: none
//Post: m_mon will be set to input
//void setMoney(const float m){m_mon = m; return;}

const int ARRSIZE = 10;

class business
{
private:
  string m_nam; //name of business
  float m_mon; //money in register
  product m_items[ARRSIZE];
  customer m_customers[ARRSIZE];
  short m_numItems;
  short m_numCustomers;
public: 
  business():m_nam(""),m_mon(0),m_numItems(0),m_numCustomers(0){}
  business(const string n, const float m, const string file);
  void print();
  void addCustomer(const customer c);
  void sell_something();
  void customers_leave(customer street[], int& num);
  string getName(){return m_nam;}
  float getMoney(){return m_mon;}
  void setMoney(const float m){m_mon = m; return;}
  friend void customer::buy_something(business bus);
};

#endif