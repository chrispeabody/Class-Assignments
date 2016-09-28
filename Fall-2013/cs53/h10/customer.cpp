//name: CHRIS PEABODY
//class: CS53, section A
//date: 11/11/2013
//file: customer.cpp
//purpose: implementation of customer class

#include "customer.h"
#include "business.h"
#include "product.h"

customer::customer(const string n, const float m)
{
  m_nam = n;
  m_mon = m;
  m_numPur = 0;
}

void customer::buy_something(business bus)
{
  product temp;
  //decide 50/50 if it wants something
  if(rand()%2)
  {
    //Choose one random product in the business
    temp = bus.m_items[rand()%(bus.m_numItems)];
    //see if can afford and have room
    if (m_numPur<POCKETSIZE && m_mon>=temp.m_price)
    {
      //copy product into array and decrement money
      m_mon-=temp.m_price;
      m_purchases[m_numPur]=temp;
      m_numPur+=1;

      //increase business's money
      bus.setMoney(bus.getMoney()+temp.m_price);

      //+15 happiness
      m_happ+=15;

      //cout<<m_nam<<" buys a "<<temp.m_name<<" for $"<<temp.m_price<<"."<<endl;
    }
    else
      m_happ-=10; //-10 happiness
  }

  return;
}

//Overloading insertion operator for customer
ostream& operator<<(ostream& os, customer cus)
{
  os<<cus.m_nam<<" has $"<<cus.m_mon<<", "<<cus.m_happ<<" happiness and has ";
  if(cus.m_numPur!=0)
  {
    for(int i=0; i<cus.m_numPur; ++i)
    {
      os<<cus.m_purchases[i].m_name;
      if (i==cus.m_numPur-1)
        os<<".";
      else
        os<<", ";
    }
  }
  else
    os<<"nothing.";
  os<<endl;

  return os;
}

void customer::chuck(customer cus)
{
  if (m_numPur>0)
  {
    //Successful!
    cout<<m_nam<<" throws a "<<m_purchases[m_numPur-1].m_name<<" at ";
    cout<<cus.m_nam<<"!"<<endl;
    m_numPur-=1;
    m_happ+=5;
    cus.m_happ-=20;
  }
  else
  {
    //Unsuccessful :(
    cout<<m_nam<<" checks his pockets but has nothing to throw!"<<endl;
    m_happ-=25;
  }
}

void customer::rob(customer cus)
{
  if(m_numPur<POCKETSIZE && cus.m_numPur>0)
  {
    //Successful!
    cout<<m_nam<<" steals a "<<cus.m_purchases[cus.m_numPur-1].m_name<<" from ";
    cout<<cus.m_nam<<"!"<<endl;
    m_purchases[m_numPur]=cus.m_purchases[cus.m_numPur-1];
    m_numPur+=1;
    cus.m_numPur-=1;
    m_happ+=25;
    cus.m_happ-=20;
  }
  else
  {
    //Unsuccesful :(
    if (m_numPur<POCKETSIZE)
    {
      cout<<m_nam<<" tries to steal from ";
      cout<<cus.m_nam<<", but they have nothing to steal!"<<endl;
    }
    else
    {
      cout<<m_nam<<" tries to steal from ";
      cout<<cus.m_nam<<", but they have no room in their pockets!"<<endl;
    }
  }
}