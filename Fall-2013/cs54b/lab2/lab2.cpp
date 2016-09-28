//Name: CHRIS PEABODY
//Section: B
//Date: 9/3/2013
//Description: This program aims to aid in the ordering of pizza and soda
//for Miners College in their annual picnic

#include <iostream>
using namespace std;

const short P = 8; //P is the assumed number of slices in a pizza

int main()
{
  short n; //n is the number of pizzas ordered in last year's picnic
  short m; //m is the number of participants in last year's picnic
  float spp; //spp is the number of slices per person in last year's picnic
  
  short part; //part is the number of participants THIS year
  short piz; //piz is the number of pizzas required THIS year 
  short soda; //soda is the number of soda bottles required THIS year
  float cost; //the total cost for this year's picnic
  float x; //x is the cost per pizza
  float y; //y is the cost of a one-liter soda bottle
  
  cout<<"Welcome! Lovely day we're having.";
  cout<<"\n\nHow many pizzas were ordered last year?\nPizzas: ";
  cin>>n;
  cout<<"\n\nHow many people came to the picnic last year?\nPeople: ";
  cin>>m;
  
  //8 slices per pizza, divided among the people
  spp = (P*n)/m;
  cout<<"\n\nLast year each person had an average of " << spp << " slices.";
  
  //Add 50 participants to the number from last year to figure out this year
  part = m+50;
  cout<<"\n\nThis year 50 more participants are expected, ";
  cout<<"for a total of " << part << " participants.";
  
  cout<<"\n\nThe cost of a pizza: ";
  cin>>x;
  cout<<"\n\nThe cost of a bottle of soda: ";
  cin>>y;
  
  //Each pizza will feed 4 people, so you need one pizza for every 4 people
  piz = static_cast<int>(part/4);
  //Each soda will feed 3 people, etc.
  soda = static_cast<int>(part/3);
  //NOTE TO SELF: This shaves off decimals -> not entirely efficient
  
  //Total up the cost
  cost = (x*piz)+(y*soda);
  
  cout<<"\n\nFor this year you will need "<<piz<<" pizzas, "<<soda<<" bottles";
  cout<<" of soda, and $"<<cost<<" to pay for it all!";
  cout<<"\n\nHave a nice day!";
  
  return 0; 
}




