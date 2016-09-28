//Name: CHRIS PEABODY
//Class: CS54 section B
//Date: 9/17/2013
//Purpose: To allow the user to generate random numbers

#include <iostream>
#include <stdlib.h>
#include <time.h>
using namespace std;

int main()
{
  int sum = 0; //Sum of the numbers used for averaging
  int X; //Number of numbers to generate and average
  char ret; //used for checking if the program should return to beginning
  int num; //The var for storing the random number temporarily
  float avg; //the average!
  
  srand(time(NULL));
  cout<<"Welcome. Let's do some number generating, shall we?"<<endl;
  do
  {
    //Prompt for amount of numbers
    do
    {
      cout<<"How many numbers do you want generated?"<<endl;
      cin>>X;
    } while(X<1);
    
    //Generate numbers and find sum
    sum = 0;
    for(int n=0;n<=X;n++)
    {
      num=(rand()%(20))-10;
      sum+=num;
    }
    avg = sum/X; //do the averaging
    cout<<"You generated "<<X<<" numbers with an average of "<<avg<<"."<<endl;
    
    //Prompt for restarting
    do
    {
      cout<<"\nWould you like to generate more numbers? (Y/N)\nAnswer: ";
      cin>>ret;
    } while(ret!='y'&&ret!='n'&&ret!='Y'&&ret!='N');
  } while(ret!='N'&&ret!='n');
  return 0;
}
