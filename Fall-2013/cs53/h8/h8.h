//name: CHRIS PEABODY
//class: CS 53 section A
//date: 10/22/2013
//file: h8.h
//Purpose: To create Moe fables!

#ifndef H8_H
#define H8_H

#include <iostream>
#include <ctime>
#include <cstdlib>
#include <fstream>
#include <sstream>
#include <cstring>
using namespace std;

//----CONST----//
const int NUM_FABLES = 5; //Handles amount of fables available

//file names
const char LIST1[]="list1.txt";
const char LIST2[]="list2.txt";
const char MOERALS[]="moe-rals.txt";
const char MOERANTS[]="moe-rants.txt";
const char MOEFABLES[]="MoeFables.txt";

//----PROTOYPES----//

//Desc: Turns the fable variable into a random fable filename
//Pre: none
//Post: fable will be in the format "fable[number].txt"
void randomFable(string & fable);


//Desc: gets a random data piece from a given file
//Pre: none
//Post: the array sent in will contain the random data piece
void getRandData(const char file[], char arr[]);

//Desc: Find the subjects to replace in a file
//Pre: first item must be in "The [subject1] and the [subject2] fable" format
//Post: subject1 and subject2 will be set to respetive strings
void findSubjects(const string file, char subject1[], char subject2[]);

///Desc: Replaces words and saves file with fable
//Pre: None
//Post: MoeFables.txt will contain all fables made in the session
void replaceWords(const string file);

#endif