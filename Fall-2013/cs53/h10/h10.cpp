//name: CHRIS PEABODY
//class: CS53, section A
//date: 12/2/2013
//file: h10.cpp
//purpose: the main driver for the program

#include <iostream>
#include <ctime>
#include <cstdlib>
#include <fstream>
#include "customer.h"
#include "business.h"
using namespace std;

int main()
{
  srand(time(NULL)); //SEED THE GENERATOR!

  //DECLARE/INTITALIZE EVERYTHING
  int tempint; //used for random numbers in shuffling/interacting
  customer tempcus; //used in shuffing customers
  string tempstr; //used in setting names

  business MOE("Moe's Bar", 0, "moeproducts.txt");
  business CBG("Comic Book Store", 0, "cbgproducts.txt");

  const int STREETSIZE = 20;

  customer street[STREETSIZE];
  int streetnum = STREETSIZE; //number of people on street
  int cycles = 0; //number of times through

  int moehapp = 0; //team happiness
  int cbghapp = 0; //team happiness

  ifstream in;
  in.open("thepeople.txt");

  //POPULATE STREET for first time
  for(int i = 0; i<STREETSIZE; i++)
  {
    getline(in, tempstr, ',');
    tempstr.erase(0, 1);
    street[i].setName(tempstr);

    in>>tempint;
    street[i].setInclin(tempint);
  }

  //OUTPUT INITIAL PEOPLE
  for(int i = 0; i<STREETSIZE; i++)
    cout<<street[i];

  //REPEAT UNTIL OVER
  do
  {
    //GO INTO SHOPS
    for(int i=0; i<streetnum; i++)
    {
      if (street[i].getHapp()<10)
      {
        cout<<street[i].getName()<<" isn't so happy. To Shellbyville!"<<endl;
        if (street[i].getInclin()==1)
          cbghapp+=street[i].getHapp();
        else
          moehapp+=street[i].getHapp();
      }
      else if (street[i].getHapp()>90)
      {
        cout<<street[i].getName()
            <<" has reached Nirvana. They ascend into heaven."<<endl;
        if (street[i].getInclin()==1)
          cbghapp+=street[i].getHapp();
        else
          moehapp+=street[i].getHapp();
      }
      else
      {
        if (street[i].getInclin()==(-1))
          MOE.addCustomer(street[i]);
        else
          CBG.addCustomer(street[i]);
      }
    }

    streetnum = 0;
    cout<<endl;

    //BUY THINGS
    MOE.sell_something();
    CBG.sell_something();

    //GO INTO STREET
    MOE.customers_leave(street, streetnum);
    CBG.customers_leave(street, streetnum);

    //SHUFFLE ARRAY
    for(int i = 0; i<streetnum; i++)
    {
      tempint = rand()%streetnum; //choose random spot
      tempcus=street[tempint];
      street[tempint]=street[i];
      street[i]=tempcus; //swap current position with random spot
    }

    cout<<endl;

    //INTERACT

    for(int i = 0; i<streetnum; i++)
    {
      tempint = rand()%streetnum;
      if(street[i].getInclin()==street[tempint].getInclin())
        street[i].rob(street[tempint]);
      else
        street[i].chuck(street[tempint]);
    }
  
    cout<<endl;

    /*for(int i = 0; i<streetnum; i++)
      cout<<street[i];*/

    cycles+=1;
  } while (cycles<20 && streetnum>1);

  //SAY SURVIVORS
  cout<<"The sole survivor: ";
  if (streetnum==0)
  {
    cout<<"NO ONE."<<endl;
  }
  else
  {
    for(int i = 0; i<streetnum; i++)
    {
      cout<<street[i].getName();
      if (i==streetnum-1)
        cout<<"."<<endl;
      else
        cout<<" ...and also ";
    }
  }

  //SAY FINAL SCORES
  cout<<"Moe-goer's happiness totaled "<<moehapp<<endl;
  cout<<"Comic-bookie's happiness totaled "<<cbghapp<<endl;
  if (moehapp>cbghapp)
    cout<<"MOE'S TEAM WINS!"<<endl;
  else if (cbghapp>moehapp)
    cout<<"COMIC BOOK TEAM WINS!"<<endl;
  else
    cout<<"IT'S A TIE! ... wait it's a tie? Wow."<<endl;

  return 0;
}