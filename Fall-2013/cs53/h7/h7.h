//Name: CHRIS PEABODY
//Class: cs53 section B
//Date: 10/16/2013
//File: h7.h
//Purpose: Let users play a dart game in the bar

#ifndef h7_h
#define h7_h

#include <iostream>
#include <cstdlib>
#include <ctime>
#include <cmath>
using namespace std;

//----CONST----//

//min and max beers consumed
const int MIN_BEERS = 3;
const int MAX_BEERS = 16;
const int DISTANCE = 13;
const int SHOTS = 14;
const float DEG_TO_RAD = 0.017453;
const string SOUNDS[]={"Ding ding ding!","Buurp!","Hey hey!","Hmmmm!","DOH!"};
const int MAX_DRUNK = 55; //The max of the random drunk distances (score) *10

//----PROTOTYPES----//

//Desc: Finds the number of beers the users drank
//Pre: none
//Post: returns number of beers consumed
int getBeers();

//Desc: Fires SHOT amounts of random shots, and adds the distances to an array
//Pre: none
//Post: the array scores[] will be filled with distances
void play(const string sounds[], float scores[], int beers);

//Desc: Randomizes distances
//Pre: none
//Post: puts random distances between 0 and MAX_DRUNK into the array
void play(float scores[]);

//Desc: Divides number of beers by 2 to find score
//Pre: none
//Post: prints a score equal to beers*0.5
void showScores(const int beers);

//Desc: averages distances and divides by beers to get score
//Pre: none
//Post: prints out a score equal to average distances/beer
void showScores(const float score[], const int beers);

//Desc: Creates a handicap score
//Pre: none
//Post: prints a score equal to a summation of the average and specific scores
void showScores(const float score[]);

#endif