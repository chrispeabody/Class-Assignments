//name: CHRIS PEABODY
//class: CS 54 section B
//date: 10/22/2013
//file: lab9.h
//purpose: to mimic a login server

#ifndef lab9_h
#define lab9_h

#include <iostream>
using namespace std;

//----CONST----//
const string PASS = "9a$$w0R6";

//----PROTOTYPES----//

//Desc: turns the input to all capitols
//Pre: none
//Post: char array will contain all caps after
void toAllCaps(char domain[]);

//Desc: Checks if username is in database
//Pre: none
//Post: returns true if the username is valid (false otherwise)
bool verifyUser(string user);

//Desc: Checks if the password is correct
//Pre: none
//Post: Returns true if the password is correct (false otherwise)
bool verifyPass(string pass);

#endif
