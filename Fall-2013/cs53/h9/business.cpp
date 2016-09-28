//name: CHRIS PEABODY
//class: CS53, section A
//date: 11/11/2013
//file: business.cpp
//purpose: implementation of business class

#include "business.h"

business::business(const string n, const float m)
{
  string temp;

  m_nam = n;
  m_mon = m;
  m_numCustomers = 0;

  ifstream in;
  in.open("itemlist.txt");

  while(in>>temp)
  {
    m_items[m_numItems]=temp;
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
    cout<<"\t"<<m_items[i]<<endl;
  }

  return;
}

void business::addCustomer(const customer c)
{
  m_customers[m_numCustomers]=c;
  m_numCustomers++;

  return;
}

void business::make_a_sale()
{
  for(int i = 0; i < m_numCustomers; ++i)
  {
      if (m_customers[i].purchase(m_items[rand()%m_numItems]))
      {
        m_mon+=40;
      }
  }

  return;
}