//Name: CHRIS PEABODY
//Class: CS53 Section B
//Date: 9/11/2013
//Purpose: To filter who can and cannot enter moe's bar

#include <iostream>
using namespace std;

//The cost per beer and liquor respectively
const float BEER = 2.00;
const float LIQUOR = 4.25;

int main()
{
  //Variables!
  string name;  //Patron's name
  string ans;   //Answers to word questions -recycled
  float num;    //Answers to numerical questions -recycled
  int drinks; //the number of drinks they can buy
  
  //Numbers will print correctly!
  cout.setf(ios::fixed);
  cout.setf(ios::showpoint);
  cout.precision(2);
  
  //Welcome message
  cout<<"\nWelcome to Moe's Bar, stranger."<<endl;
  do
  {
    //Name prompt and answer
    cout<<"\nWhat's your name? First only.\nName: ";
    cin>>name;
    
    //Check if it's barney, otherwise move on
    if (name=="Barney")
      cout<<"\nC'mon in Barney."<<endl;
    else
    {
      //teetotaler prompt and answer
      do
      {
        cout<<"\n"<<name<<", you're not a teetotaler, are you? (y/n)"<<endl;
        cout<<"Answer: ";
        cin>>ans;
      } while(ans!="y"&&ans!="n");
      
      if (ans=="y")
        cout<<"\nGet out of here. We don't like your kind!"<<endl;
      else
      {
        cout<<"\nThat's a relief."<<endl;
        //age prompt and answer
        do
        {
          cout<<"\nSay, "<<name<<", how old are you?\nAnswer: ";
          cin>>num;
        } while(num<1||num>120);
        
        if (num<21)
        {
          cout<<"\nI believe you're a little young to drink, ";
          cout<<name<<"."<<endl;        }
        else
        {
          cout<<"\nGood, "<<name<<". Just one more thing then."<<endl;
          //drink prompt and answer
          do
          {
            cout<<"\nWhat do you like to drink, "<<name<<"?"; 
            cout<<" (beer or liquor or soda?)\nAnswer: ";
            cin>>ans;
          } while(ans!="beer"&&ans!="liquor"&&ans!="soda");
          
          if (ans=="soda")
            cout<<"\nWe don't soyrv you sissies in dis place!"<<endl;
          else
          {
            cout<<"\nA good choice!"<<endl;
            
            //assuming they are smart enough to put in a number at all
            cout<<"\nHow much money do you have, "<<name<<"?\nAnswer: ";
            cin>>num;
            
            //check which drink type they chose, and calculate the drinks #
            if(ans=="beer")
              drinks = static_cast<int>(num/BEER); // Money/Beer cost
            else //assumes liquor was chosen
              drinks = static_cast<int>(num/LIQUOR); //Money/Liquor cost
            
            if (drinks==0)
              cout<<"\nGet outta here you bum!"<<endl;
            else
            {  
              cout<<"\nWith that you could buy "<<drinks<<" drinks!"<<endl;
              
              //drink number promt and answer
              cout<<"\nSo, "<<name<<", how many drinks do you plan on buying?";
              cout<<"\nAnswer: ";
              cin>>num;
            
              if (num<drinks)
              {
                cout<<"\nCome back when you want to spend all of your money!";
                cout<<endl;
              }
              else
                cout<<"\nEnough questions, come on in, "<<name<<"."<<endl;
            }
          }
        }
      }  
    }
    //ask for more people
    do
    {
      cout<<"\nAnybody else there?? (y/n)\nAnswer: ";
      cin>>ans;
    } while(ans!="y"&&ans!="n");
  } while(ans=="y");
  
  //No more people
  cout<<"\nMy work here is done, then."<<endl;
  
  return 0;
}
