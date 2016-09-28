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

//Desc: picks a random item and gives it to a customer
//Pre: customer must have $40 and have open "pockets"
//Post: item will be added to the customer's array of items, money charged
//make_a_sale();

class business
{
private:
  string m_nam; //name of business
  float m_mon; //money in register
  string m_items[10];
  customer m_customers[10];
  short m_numItems;
  short m_numCustomers;
public: 
  business():m_nam(""),m_mon(0),m_numItems(0),m_numCustomers(0){}
  business(const string n, const float m);
  void print();
  void addCustomer(const customer c);
  void make_a_sale();

};

#endif