//name: CHRIS PEABODY
//class: CS 53 section A
//date: 10/22/2013
//file: h8_functions.cpp
//Purpose: To create Moe fables!

#include "h8.h"
#include <iostream>
#include <ctime>
#include <cstdlib>
#include <fstream>
#include <sstream>
#include <cstring>
using namespace std;

void randomFable(string & fable)
{
  int num = rand()%(NUM_FABLES)+1;

  //Used to to turn num into a string
  ostringstream convert;
  convert<<num;

  //turn fable to file name
  fable = "fable" + convert.str() + ".txt";

  return;
}


void getRandData(const char file[], char arr[])
{
  int numItems = 0, randomItem;
  ifstream in;
  
  in.open(file);

  //find amount of items in file
  while(in.getline(arr, 200, '\n'))
    numItems++;
  
  in.close();

  //Pick random spot in list
  randomItem = rand()%(numItems)+1;

  in.open(file);

  //move to correct location
  for(int i=0; i < randomItem-1; i++)
    in.ignore(500, '\n');

  //Extract random piece
  in.getline(arr, 200, '\n');

  in.close();
  return;
}

void findSubjects(const string file, char subject1[], char subject2[])
{
  //The blank and the blank fable
  ifstream in;
  in.open(file.c_str());
  in.ignore(500, ' ');
  in.getline(subject1, 19, ' ');
  in.ignore(500, ' ');
  in.ignore(500, ' ');
  in.getline(subject2, 19, ' ');
  in.close();

  return;
}

void replaceWords(const string file)
{
  static int count=0; //Fable #
  count++;
  char subject1[20]; //Orginal subjects
  char subject2[20];
  char current[20]; //The string being looked at at any given moment
  char ranItem[20]; //For replacing words after The or A
  char ranRant[200]; //For getting a random rant
  char ranMoeral[200]; //For getting a random moeral
  char punct = '0'; //Handles punctuation at end of words

  //Choose new subjects, make sure their not the same
  char newSub1[20];
  char newSub2[20];
  getRandData(LIST1, newSub1);
  getRandData(LIST1, newSub2);
  while (strcmp(newSub1,newSub2)==0)
    getRandData(LIST1, newSub2);

  findSubjects(file, subject1, subject2);
  
  ifstream in;
  in.open(file.c_str());

  static ofstream out(MOEFABLES);

  out<<"Moe's Fable #"<<count<<endl;
  out.put('\n');
  //FOR EACH WORD
  while (in>>current)
  {
    //CHECK IF THERE'S PUNCT AT THE END
    if (ispunct(current[strlen(current)-1]))
    {
      punct=current[strlen(current)-1];
      //TAKE OUT PUNCTUATION FOR NOW
      current[strlen(current)-1]='\0';
    }
    else
      punct='0';

    //IF THE OR A...
    if (!strcmp(current,"The")||!strcmp(current,"the")
      ||!strcmp(current,"A")||!strcmp(current,"a"))
    {
      //...SAY THE OR A AND PUT A SPACE
      out<<current<<" ";
      //LOOK AT THE NEXT WORD
      in>>current;

      //IF IT'S NOT A KEYWORD...
      if(current!=subject1&&current!=subject2)
      { 
        //...CHECK IF IT HAS PUNCTUATION AT END (Again)
        if (ispunct(current[strlen(current)-1]))
        {
          punct=current[strlen(current)-1];
          //TAKE OUT PUNCTUATION FOR NOW
          current[strlen(current)-1]='\0';
        }
        else
          punct='0';
        
        //OUTPUT RANDOM WORD
        getRandData(LIST2,ranItem);
        out<<ranItem;

      } //OTHERWISE REPLACE KEYWORDS
      else if (current==subject1)
        out<<newSub1;
      else if (current==subject2)
        out<<newSub2;
    }
    else
    {
      //IF JUST REGULAR WORD, OUTPUT IT
      out<<current;
    }

    //PUT PUNCT BACK IF IT WAS THERE
    if (punct!='0')
      out<<punct;
    if (punct=='.')
      //1 in 4 chance to put in a moe-rant
      if ((rand()%3+1)==1)
      {
        getRandData(MOERANTS, ranRant);
        out<<" "<<ranRant;
      }

    out<<" ";
  }
  
  out<<endl; //These endl's not showing up?
  getRandData(MOERALS, ranMoeral);
  out<<"The Moe-ral of the story: "<<ranMoeral<<endl<<endl;

  return;
}