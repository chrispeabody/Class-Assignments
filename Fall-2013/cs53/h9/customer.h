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
using namespace std;

//Desc: adds the items to the customer's list of items
//Pre: customer must have $40, and have room in his "pockets"
//Post: the customer's next open slot will have the new item
//bool purchase(const string item);

//Desc: shows the name of the customer
//Pre: none 
//Post: returns the name
//string getName(){return m_nam;}

//Desc: shows the money value of the customer
//Pre: none
//Post: returns the money value
//float getMoney(){return m_mon;}

//Desc: TEST
//Pre:  TEST
//Post: TEST
//float getPur(){return m_numPur;}

//Desc: mutator for the customer's money value 
//Pre: none
//Post: m_mon will be equal to the input
//void setMoney(const float m){m_mon = m; return;}

//Desc: Shows the customer's name, money, and items purchased
//Pre: none
//Post: none
//void print();

class customer
{
private:
  string m_purchases[20];
  short m_numPur; //number of purchases
  float m_mon; //amount of money
  string m_nam; //name
public:
  customer(){m_mon=rand()%256+4;}
  customer(const string n, const float m);
  bool purchase(const string item);
  string getName(){return m_nam;}
  float getMoney(){return m_mon;}
  float getPur(){return m_numPur;}
  void setMoney(const float m){m_mon = m; return;}
  void print();
};

#endif