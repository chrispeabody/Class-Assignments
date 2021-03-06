//Name: CHRIS PEABODY
//Class: CS 53, section A
//Date: 9/21/2013
//Purpose: Let's users gamble away all their money at Moe's bar

#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;

//Min and max starting bank values
const int MIN_BANK = 200;
const int MAX_BANK = 1000;

int main()
{
  int num1, num2, num3; //slot tumbler values
  int bank, balance=0; //bank and game balance
  bool chkb = false; //If players have checked balance yet
  int m_ans; //Menu answers
  int ans; //all other answers (recycled)
  
  srand(time(NULL));
  
  //generate bank balance
  bank = (rand()%(MAX_BANK+1-MIN_BANK))+MIN_BANK;
  
  cout<<"\nWelcome to the ATM slot machine!"<<endl;
  
  do
  {
    do
    {
      cout<<"\nWhat would ya like to do?\n\t1. Check Bankk balance"<<endl;
      cout<<"\t2. Transfer funds to game\n\t3. Play\n\t4. Leave & cash out"<<endl;
      cout<<"Answer: ";
      cin>>m_ans;
    } while(m_ans!=1&&m_ans!=2&&m_ans!=3&&m_ans!=4);
    
    switch (m_ans)
    {
      case 1:
        cout<<"\nYour Bankk balance: $"<<bank<<endl;
      
        chkb = true; //The balance has been checked
        break;
      case 2:
        if (chkb==false)
        {
          cout<<"\nYou gotta check your balance before transfering funds!"<<endl;
        }
        else
        {
          do
          {
            cout<<"\nHow much money would you like to transfer?\nAnswer:";
            cin>>ans;
          } while (ans<0);
       
          //transfer
          bank-=ans;
          balance+=ans;
          cout<<"\n$"<<ans<<" transferred."<<endl;
        }
        break;
      case 3:
        if (balance<5)
        {
          cout<<"\nYou gotta transfer more funds before playing!"<<endl;
        }
        else
        {
          cout<<"\nYou pull the lever. . ."<<endl;
          
          num1 = (rand()%4)+1;
          num2 = (rand()%4)+1;
          num3 = (rand()%4)+1;
          
          cout<<"You spun "<<num1<<num2<<num3<<"!"<<endl;
          
          if(num1==num2&&num1==num3)
          {
            cout<<"You've won $30! Congratulations!"<<endl;
            balance+=30;
          }
          else
          {
            if (num1==num2||num1==num3||num2==num3)
            {
              cout<<"You've won $1!"<<endl;
              balance+=1;
           
            }
            else
            {
              cout<<"There were no matches. That will cost you $5."<<endl;
              balance-=5;
            }  
          }
          cout<<"\nYour balance is now $"<<balance<<"."<<endl;
        }
        break;  
    }
    
  } while(m_ans!=4);
  
  cout<<"\nYour final balance is $"<<balance<<"."<<endl;
  cout<<"\nYour bank balance is $"<<bank<<"."<<endl;
  cout<<"\nThanks for playing!"<<endl;
  
  return 0;
}
