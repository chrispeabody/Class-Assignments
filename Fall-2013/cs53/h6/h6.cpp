//Name: CHRIS PEABODY
//Class: CS 53, section A
//Date: 9/21/2013
//File: h6.cpp
//Purpose: Let's users gamble away all their money at Moe's bar

#include <iostream>
#include <cstdlib>
#include <ctime>
#include "h6.h"
using namespace std;

int main()
{
  int bank, balance=0; //bank and game balance
  bool chkb = false; //If players have checked balance yet
  int ans; //handles answers
  
  srand(time(NULL));
  
  //generate bank balance
  bank = (rand()%(MAX_BANK+1-MIN_BANK))+MIN_BANK;
  
  cout<<"\nWelcome to the ATM slot machine!"<<endl;
  
  do
  {
    ans = displayMenu();

    switch (ans)
    {
      case 1:
        cout<<"\nYour Bankk balance: $"<<bank<<endl;
      
        chkb = true; //The balance has been checked
        break;
      case 2:
        if (chkb==false)
          cout<<"\nYou gotta check your balance before transfering funds!"<<endl;
        else
          transferFunds(bank, balance);
        break;
      case 3:
        if (balance<5)
          cout<<"\nYou gotta transfer more funds before playing!"<<endl;
        else
          spin(balance); //Spins and cheats if needed
        break;  
    }
    
  } while(ans!=4);
  
  goodbyes(bank, balance);
  
  return 0;
}
