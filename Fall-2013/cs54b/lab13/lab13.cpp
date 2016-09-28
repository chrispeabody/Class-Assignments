//name: CHRIS PEABODY
//class: CS54 section B
//date: 11/19/2013
//file: lab13.cpp
//purpose: The driver file for lab 13

#include "cat.h"
#include "horse.h"
#include "farm.h"
#include <iostream>
using namespace std;


int main()
{
  string tempN; //temp name
  char tempG; //temp gender

  farm <horse>horseFarm;
  cout<<"Creating a horse farm. . ."<<endl<<endl;
  cout<<"Enter a horse \"Name (M/F)\" or enter \"no\" for no more entries";
  
  cout<<"\nHorse: ";
  cin>>tempN;
  while (tempN!="no")
  {
    cin>>tempG;
    horse tempH(tempN, tempG); //temp horse
    horseFarm.addAnimal(tempH);

    cout<<"Horse: ";
    cin>>tempN;
  }

  farm <cat>catFarm;
  cout<<"Creating a cat farm. . ."<<endl<<endl;
  cout<<"Enter a cat \"Name (M/F)\" or enter \"no\" for no more entries";

  cout<<"\nCat: ";
  cin>>tempN;
  while (tempN!="no")
  {
    cin>>tempG;
    cat tempC(tempN, tempG); //temp cat
    catFarm.addAnimal(tempC);

    cout<<"Cat: ";
    cin>>tempN;
  }

  cout<<"Horses: ";
  horseFarm.printAnimals();
  cout<<"Cats: ";
  catFarm.printAnimals();

  return 0;
}