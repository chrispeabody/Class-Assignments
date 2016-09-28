//Name: CHRIS PEABODY
//Class: CS54 section B
//Date: 10/29/2013
//File: lab10.h
//Purpose: Decode encrypted messages from a file

#ifndef LAB10_H
#define LAB10_H

#include <iostream>
#include <fstream>
using namespace std;

//Desc: Takes in a file, shifts it, streams it to new file
//Pre: none
//Post: Output file will now have encrypted/decrypted version of input file
void cypher(string ifile, string ofile, int factor);

#endif