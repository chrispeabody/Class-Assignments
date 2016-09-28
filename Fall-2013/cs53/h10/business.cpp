//name: CHRIS PEABODY
//class: CS53, section A
//date: 11/11/2013
//file: business.cpp
//purpose: implementation of business class

#include "business.h"

business::business(const string n, const float m, const string file)
{
  product tempprod;
  string tempstr;
  float tempflo;

  m_nam = n;
  m_mon = m;
  m_numCustomers = 0;
  m_numItems = 0;

  ifstream in;
  in.open(file.c_str());

  while(in>>tempflo)
  {
    tempprod.m_price = tempflo;
    getline(in, tempstr, '\n');
    tempstr.erase(0, 1);
    tempprod.m_name = tempstr;
    m_items[m_numItems]=tempprod;
    m_numItems++;
  }
}

void business::print()
{
  cout<<m_nam<<endl<<endl;

  cout<<"Customers"<<endl;
  for(int i = 0; i < m_numCustomers; ++i)
  {
    cout<<"\t"<<m_customers[i].getName()<<endl;
  }

  cout<<"\nItems"<<endl;
  for(int i = 0; i < m_numItems; ++i)
  {
    cout<<"\t"<<m_items[i].m_name<<endl;
  }

  return;
}

void business::addCustomer(const customer c)
{
  m_customers[m_numCustomers]=c;
  m_numCustomers++;

  return;
}

void business::sell_something()
{
  for(int i = 0; i < m_numCustomers; ++i)
    m_customers[i].buy_something(*this);
  return;
}

void business::customers_leave(customer street[], int& num)
{
  for (int i = 0; i < m_numCustomers; i++)
  {
    street[num+i]=m_customers[i];
  }

  num+=m_numCustomers;
  m_numCustomers=0;
  
  return;
}