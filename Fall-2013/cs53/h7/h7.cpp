//Name: CHRIS PEABODY
//Class: cs53 section B
//Date: 10/16/2013
//File: h7.cpp
//Purpose: Let users play a dart game in the bar

#include <iostream>
#include <cstdlib>
#include <ctime>
#include <cmath>
#include "h7.h"
using namespace std;

int main()
{ 
  int beers;
  float scores[SHOTS];
  char ans;

  srand(time(NULL));
  cout.setf(ios::fixed);
  cout.setf(ios::showpoint);
  cout.precision(1);

  cout<<"\nWelcome to Moe's Darts!"<<endl;
  do
  {
    beers = getBeers();

    if (beers < MIN_BEERS)
      showScores(beers);
    else if (beers <= MAX_BEERS)
    {
      play(SOUNDS,scores,beers);
      showScores(scores, beers);
      showScores(scores);
    }
    else
    {
      play(scores);
      showScores(scores);
    }

    do
    {
      cout<<"\nWould you like to play again? (y/n)\nAnswer: ";
      cin>>ans;
    } while(ans!='y'&&ans!='n');
  } while(ans=='y');

  return 0;
}