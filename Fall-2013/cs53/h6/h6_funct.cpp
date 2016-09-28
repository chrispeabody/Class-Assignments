//Name: CHRIS PEABODY
//Class: CS 53, section A
//Date: 9/21/2013
//File: h6_funct.cpp
//Purpose: Let's users gamble away all their money at Moe's bar

#include <iostream>
#include <cstdlib>
#include <ctime>
#include "h6.h"
using namespace std;

int displayMenu()
{
	int ans;
	  do
    {
      cout<<"\nWhat would ya like to do?\n\t1. Check Bankk balance"<<endl;
      cout<<"\t2. Transfer funds to game\n\t3. Play\n\t4. Leave & cash out"<<endl;
      cout<<"Answer: ";
      cin>>ans;
    } while(ans!=1&&ans!=2&&ans!=3&&ans!=4);

    return ans;
}

void transferFunds(int & bank, int & funds)
{
	int ans; //the amount
	do
  {
    cout<<"\nHow much money would you like to transfer?\nAnswer:";
    cin>>ans;
  } while (ans<0);
     
  if (bank>=ans)
  {  
  	//transfer
  	bank-=ans;
  	funds+=ans;
  	cout<<"\n$"<<ans<<" transferred."<<endl;
  }
  else
  	cout<<"\nNot enough funds in the bank for that!"<<endl;

  return;
}

void spin(int & balance)
{
	int num1, num2, num3; //slot tumbler values
	char char1, char2, char3; //tumblers in letter form
  int spins; //the amount of times to spin
  int initialBalance = balance; //Saves initial balance
  static int spinCount = 0; //number of total spins ever

  //prompts for spin amount
  do
  {
  	cout<<"\nHow many times would you like to spin?\nAnswer: ";
  	cin>>spins;
	} while(spin<0);

	//Checks funds to see if enough for 100% loss
	if (balance<(spins*5))
	{
		cout<<"\nYou don't have enough funds to assure you can pay for the losses."<<endl;
		cout<<"Transfer more or choose less spins."<<endl;
	}
	else
	{
		cout<<"\nYou pull the lever. . ."<<endl<<endl;
	  for(int i=0; i<spins; i++)
	  {
	  	if (spinCount>5&&(balance-initialBalance)>0)
	  	{
	  		cheat(balance);
	  		spinCount++; //update spin counter
	  	}
	  	else
	  	{
		  	spinCount++; //Update spin counter
			  
			  //Randomizes tumblers        
			  num1 = (rand()%4)+1;
			  num2 = (rand()%4)+1;
			  num3 = (rand()%4)+1;

			  //Turns the nums to chars
			  char1 = convertNum(num1);
			  char2 = convertNum(num2);
			  char3 = convertNum(num3);

			  //Output the spin in char form
			  cout<<"Spin: ["<<char1<<char2<<char3<<"] ";
			  
			  //Checks to see if any numbers match, and gives/takes money
			  if(num1==num2&&num1==num3)
			  {
			    cout<<"Won $30";
			    balance+=30;
			  }
			  else
			  {
			    if (num1==num2||num1==num3||num2==num3)
			    {
			      cout<<"Won $1";
			      balance+=1;
			   
			    }
			    else
			    {
			      cout<<"Lost $5";
			      balance-=5;
			    }  
			  }
			}
			//Show net gain
			if ((balance-initialBalance)>=0)
				cout<<"\t(+"<<(balance-initialBalance)<<")"<<endl;
			else
				cout<<"\t("<<(balance-initialBalance)<<")"<<endl;
		}
		//show final balance after spins
		cout<<"\nBalance: $"<<balance<<endl;
	}
}

void cheat(int & balance)
{
	int num1, num2, num3; //slot tumbler values
	char char1, char2, char3; //tumblers in letter form

	num1 = (rand()%4)+1;
  num2 = (rand()%4)+1;
  num3 = (rand()%4)+1;

  //Make num2 not equal num1
  while(num2==num1)
  {
  	num2 = (rand()%4)+1;
  }

  //Make num3 not equal num1 or num2
  while(num3==num2||num3==num1)
  {
  	num3 = (rand()%4)+1;
  }
  //Turns the nums to chars
  char1 = convertNum(num1);
  char2 = convertNum(num2);
  char3 = convertNum(num3);

  //Output the spin in char form
	cout<<"Spin: ["<<char1<<char2<<char3<<"] ";

	//Loss was automatic so show loss message/balance
	cout<<"Lost $5";
	balance-=5;

	return;
}

char convertNum(const int num)
{
	char newChar;
	switch(num)
	{
		case 1:
			newChar = 'A';
			break;
		case 2:
			newChar = 'B';
			break;
		case 3:
			newChar = 'C';
			break;
		case 4:
			newChar = 'D';
			break;
	}

	return newChar;
}

void goodbyes(int bank, int balance)
{
	cout<<"\nYour final balance is $"<<balance<<"."<<endl;
  cout<<"\nYour bank balance is $"<<bank<<"."<<endl;
  cout<<"\nThanks for playing!"<<endl;

  return;
}