//Name: CHRIS PEABODY
//Class: CS 53, section A
//Date: 9/21/2013
//File: h6.h
//Purpose: Let's users gamble away all their money at Moe's bar

#ifndef H6_H
#define H6_H

#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;

//------CONSTANTS------//

//Min and max random starting bank values
const int MIN_BANK = 200;
const int MAX_BANK = 1000;

//------PROTOTYPES------//

//Desc: Displays the menu and returns the choice
//Pre: None
//Post: numbers 1-4 will be returned with the user's answer
int displayMenu();

//Desc: Transfers funds from the bank to the game
//Pre: none
//Post: Money will be transfered
void transferFunds(int & bank, int & funds);

//Desc: Spins the tumblers and awards money
//Pre: none
//Post: Money will be taken or given based on spins
void spin(int & balance);

//Desc: Spins with an automatic loss
//Pre: none
//Post: a losing spin will happen
void cheat(int & balance);

//Desc: turns the numbers 1-4 to the chars a-d
//Pre: num must be from 1-4 (inclusive)
//Post: char will be a,b,c, or d
char convertNum(const int num);

//Desc: Outputs bank and game balances and says bye
//Pre: none
//Post: Game and bank balances will be shown
void goodbyes(int bank, int balance);

#endif