//Chris Peabody
//3-26-2015
//hw1.cpp
//purpose: determine what token categories the input belongs too

#include <iostream>
#include <ctype.h>
using namespace std;

bool isKeyword(string text)
{
  return (text == "if" || text == "else" || text == "for" || text == "while");
}

bool isIdentifier(string text)
{
  int state = 0, i = 0;

  while(i<text.length())
  {
    switch (state)
    {
      case 0:
        if (isalpha(text[i]))
          state = 1;
        else
          return false;
        break;
      case 1:
        if (isalnum(text[i]) || text[i] == '_')
          state = 1;
        else
          return false;
        break;
    }
    i++;
  }

  if (state != 1)
    return false;

  return true;
}

bool isInteger(string text)
{
  int state = 0, i = 0;

  while(i<text.length())
  {
    switch (state)
    {
      case 0:
        if (isdigit(text[i]))
          state = 2;
        else if (text[i] == '+' || text[i] == '-')
          state = 1;
        else
          return false;
        break;
      case 1:
        if (isdigit(text[i]))
          state = 2;
        else
          return false;
        break;
      case 2:
        if (isdigit(text[i]))
          state = 2;
        else
          return false;
        break;
    }
    i++;
  }

  if (state != 2)
    return false;

  return true;
}

int isIntDecSci(string text)
{
  int state = 0, i = 0;

  while(i<text.length())
  {
    switch (state)
    {
      case 0:
        if (isdigit(text[i]))
          state = 2;
        else if (text[i] == '+' || text[i] == '-')
          state = 1;
        else
          return -1;
        break;
      case 1:
        if (isdigit(text[i]))
          state = 2;
        else
          return -1;
        break;
      case 2:
        if (isdigit(text[i]))
          state = 2;
        else if (text[i] == '.')
          state = 3;
        else
          return -1;
        break;
      case 3:
        if (isdigit(text[i]))
          state = 4;
        else
          return -1;
        break;
      case 4:
        if (isdigit(text[i]))
          state = 4;
        else if (text[i] == 'E')
          state = 5;
        else
          return -1;
        break;
      case 5:
        if (isdigit(text[i]))
          state = 7;
        else if (text[i] == '+' || text[i] == '-')
          state = 6;
        else
          return -1;
        break;
      case 6:
        if (isdigit(text[i]))
          state = 7;
        else
          return -1;
        break;
      case 7:
        if (isdigit(text[i]))
          state = 7;
        else
          return -1;
        break;
    }
    i++;
  }

  //each type check
  if (state == 2)
    return 1; //INT
  else if (state == 4)
    return 2; //DEC
  else if (state == 7)
    return 3; //SCI
  else 
    return -1; //INVALID
}

int main()
{
  int N, count = 1; //number of inputs to process
  string input;

  cout<<"Welcome to the lexical analyser 3002!\nHow many inputs should we process? ";
  cin>>N;

  cout<<N<<endl;

  while (count <= N)
  {
    cout<<count<<": ";
    cin>>input;

    if(isKeyword(input))
      cout<<"Keyword."<<endl;
    else if (isIdentifier(input))
      cout<<"Indentifier."<<endl;
    else if (isIntDecSci(input) == 1)
      cout<<"Integer."<<endl;
    else if (isIntDecSci(input) == 2)
      cout<<"Decimal."<<endl;
    else if (isIntDecSci(input) == 3)
      cout<<"Scientific."<<endl;
    else
      cout<<"Invalid!"<<endl;

    cout<<endl;
    count++;
  }

  return 0;
}

