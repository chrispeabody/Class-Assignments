//Name: CHRIS PEABODY
//Class: CS54 Section B
//Date: 9/10/2013
//Purpose: To become more familiar with branching logic

#include <iostream>
using namespace std;

int main()
{
  char choice;
  long num;
  
  //welcome message
  cout<<"\nWelcome sire."<<endl;
  do
  {
    do
    {
      //prompt user
      cout<<"\nWhat would you like to accomplish today m'lord?"<<endl;
      cout<<"a) Find whether a number is divisible by 3"<<endl;
      cout<<"b) Inquire about the news"<<endl;
      cout<<"c) Retire to your quarters"<<endl;
      cout<<"\nEnter the letter: ";
      cin>>choice;
    } while ((choice!='a')&&(choice!='b')&&(choice!='c'));
    //check if a valid option was chosen
  
    //if option a
    if (choice=='a')
    {
        cout<<"Enter a number, sire.\nNumber: ";
        cin>>num;
        if ((num%3)==0)
        {
          cout<<"\nGood news, m'lord. The number is divisible by 3!"<<endl;
        }
        else
        {
          cout<<"\nGood news, m'lord. The number is NOT divisible by 3!"<<endl;
        }
    }
    else if (choice=='b') //if option b
    {
      cout<<"\nThe peasants are revolting on this lovely day."<<endl;
    }     
  } while (choice!='c');
  
  cout<<"Goodbye your majesty."<<endl;
  return 0;
}
