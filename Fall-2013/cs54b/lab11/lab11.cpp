//Name: CHRIS PEABODY
//Class: CS54 section B
//Date: 11/5/2013
//file: lab11.cpp
//purpose: track typing speeds for a company

#include <iostream>
#include "Speed_recorder.h"
using namespace std;

int main()
{
  int id;
  int numToEnter;
  int currentEntry;
  char ans;

  do
  {
    cout<<"\nEnter your company's ID number: ";
    cin>>id;
    
    Speed_recorder comp(id);

    do
    {
      cout<<"\nHow many entries do you want to enter?\nEntries: ";
      cin>>numToEnter;
      cout<<endl;

      for(int i = 1; i <= numToEnter; i++)
      {
        cout<<"Entry #"<<comp.getTotalEntries()+1<<": ";
        cin>>currentEntry;
        comp.addSpeed(currentEntry);
      }

      cout<<"\nCompany: "<<comp.getId()<<endl;
      cout<<"Average Speed: "<<comp.getAverageSpeed()<<endl<<endl;

      do
      {
        cout<<"Would you like to add more entries?\n(y/n): ";
        cin>>ans;
      } while(ans!='y'&&ans!='n');

    } while(ans=='y');

    do
    {
      cout<<"\nWould you like to create a new company list?\n(y/n): ";
      cin>>ans;
    }while(ans!='y'&&ans!='n');

  } while(ans=='y');

  return 0;
}