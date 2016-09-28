//Name: CHRIS PEABODY
//Class: cs53 section B
//Date: 10/16/2013
//File: h7_functdef.cpp
//Purpose: Let users play a dart game in the bar

#include <iostream>
#include <cstdlib>
#include <ctime>
#include "h7.h"
#include <cmath>
using namespace std;

int getBeers()
{
  int result;
  do
  {
    cout<<"\nNumber of beers bought: ";
    cin>>result;
  } while (result<=0);

  return result;
}

void play(const string sounds[], float scores[], int beers)
{
  float degx, degy, radx, rady, xcoord, ycoord, dis;

  for(int i = 0; i < SHOTS; i++)
  {
    //Between -2*beers and +2*beers in degrees
    degx = (rand()%((2*beers)-(-2*beers)))+(-2*beers);
    degy = (rand()%((2*beers)-(-2*beers)))+(-2*beers);

    //Turn degrees to radians
    radx = degx*DEG_TO_RAD;
    rady = degy*DEG_TO_RAD;

    //Find x, y coordinates according to formulas
    xcoord = DISTANCE*sin(radx)/cos(radx);
    ycoord = DISTANCE*sin(rady)/cos(rady)*cos(radx);

    dis = sqrt((xcoord*xcoord)+(ycoord*ycoord));

    cout<<"x: "<<xcoord<<" y: "<<ycoord<<"\tScore: "<<dis<<"\t";
    //Output correct sound
    if (dis<=1)
      cout<<sounds[0]; //Ding ding ding
    else if (dis<=2)
      cout<<sounds[1]; //Buuuurp
    else if (dis<=3)
      cout<<sounds[2]; //Hey hey
    else if (dis<=4)
      cout<<sounds[3]; //Hmmmmmmmm
    else
      cout<<sounds[4]; //DOH
    cout<<endl;

    scores[i] = dis;
  }

  return;
}

void play(float scores[])
{
  float dis;

  for (int i = 0; i < SHOTS; i++)
  {
    dis = (rand()%MAX_DRUNK)/10;

    cout<<"Score: "<<dis<<endl;
    scores[i] = dis;
  }

  return;
}
  

//Below min score
void showScores(const int beers)
{
  int score = static_cast<int>(beers*0.5);
  cout<<"Your score is "<<score<<"."<<endl;

  return;
}

//REGULAR
void showScores(const float score[], const int beers)
{
  float sum = 0;
  float avg;
  float totscore;

  for (int i = 0; i < SHOTS; i++)
    sum+=score[i];

  avg = sum/SHOTS;

  totscore = avg/beers;
  cout<<"\nYour final overall score is "<<totscore<<endl;

  return;
}

//HANDICAP
void showScores(const float score[])
{
  float scoresum = 0;
  float sum = 0;
  float avg;
  float totscore;

  for (int i = 0; i < SHOTS; i++)
    scoresum+=score[i];

  avg = scoresum/SHOTS;

  for (int i=0; i < SHOTS; i++)
    sum += pow((avg - score[i]),2);

  totscore = sum/SHOTS;
  cout<<"\nYour handicap score is "<<totscore<<endl;

  return;
}