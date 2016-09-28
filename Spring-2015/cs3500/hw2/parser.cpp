//Chris Peabody
//4-28-2015
//filename: parser.cpp
//CS3200

#include <iostream>
#include <cstdlib>
using namespace std;

string chunk;

void is_Relation();
void is_AddOperator();
void is_MulOperator();

void is_Expression();
void is_SimpleExpression();
void is_Term();
void is_Factor();

void is_Assignment();
void is_IncStatement();
void is_RetStatement();
void is_IfStatement();
void is_LoopStatement();
void is_PrintStatement();

void is_Statement();
void is_StatementSequence();

void is_ParamSequence();
void is_RoutineDeclaration();

//*********************LEXICAL ANALYZER*********************//

bool isKeyword(string text)
{
  return (text == "is" || 
    text == "+" || 
    text == "-" || 
    text == "*" ||
    text == "/" ||
    text == "or" ||
    text == "and" ||
    text == "neg" ||
    text == "(" ||
    text == ")" || 
    text == "lt" ||
    text == "gt" ||
    text == "eq" ||
    text == "$" ||
    text == "!" ||
    text == "print" ||
    text == "inc" ||
    text == "ret" ||
    text == "if" ||
    text == "fi" ||
    text == "ex" ||
    text == "loop" ||
    text == "pool" ||
    text == "prog" ||
    text == "blip" ||
    text == "blorp");
}

bool isIdentifier(string text)
{
  int state = 0, i = 0;

  if (isKeyword(text))
    return false;

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
        if (isalnum(text[i]))
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

int isIntOrDec(string text)
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
  else 
    return -1; //INVALID
}

bool isString(string text)
{
  int state = 0, i = 0;
  while(i<text.length())
  {
    switch (state)
    {
      case 0:
        if (text[i] == '"')
          state = 1;
        else
          return false;
        break;
      case 1:
        if (isalnum(text[i]))
          state = 1;
        else if (text[i] == '"')
          state = 2;
        else
          return false;
        break;
      case 2:
        if (i<text.length())
          return false;
        break;
    }
    i++;
  }

  return (state == 2);
}

//*****************RECURSIVE DECENT*********************//

void nextChunk()
{
  cin>>chunk;

  return;
}

void fail()
{
  cout<<"INVALID!"<<endl;
  exit(0);
}

void is_Relation()
{
  if (chunk == "lt" || chunk == "gt" || chunk == "eq")
    nextChunk();
  else
    fail();
}

void is_AddOperator()
{
  if (chunk == "+" || chunk == "-" || chunk == "or")
    nextChunk();
  else
    fail();
}

void is_MulOperator()
{
  if (chunk == "*" || chunk == "/" || chunk == "and")
    nextChunk();
  else
    fail();
}

//Factor :=  integer | decimal | string | identifier | ( Expression ) | neg Factor
void is_Factor()
{
  if (isIntOrDec(chunk) == 1 || isIntOrDec(chunk) == 2 || isString(chunk) || isIdentifier(chunk))
    nextChunk();
  else if (chunk == "(")
  {
    nextChunk();
    is_Expression();
    if (chunk == ")")
      nextChunk();
    else
      fail();
  }
  else if (chunk == "neg")
  {
    nextChunk();
    is_Factor();
  }
  else
    fail();
}

//Term := Factor { MulOperator Factor }
void is_Term()
{
  is_Factor();
  while (chunk == "*" || chunk == "/" || chunk == "and")
  {
    is_MulOperator();
    is_Factor();
  }
} 

//SimpleExpression := Term { AddOperator Term }
void is_SimpleExpression()
{
  is_Term();
  while (chunk == "+" || chunk == "-" || chunk == "or")
  {
    is_AddOperator();
    is_Term();
  }
}

//Expression := SimpleExpression [ Relation SimpleExpression ]
void is_Expression()
{
  is_SimpleExpression();

  if (chunk == "lt" || chunk == "gt" || chunk == "eq")
  {
    is_Relation();
    is_SimpleExpression();
  }
}

//Assignment := identifier is Expression !
void is_Assignment()
{
  if(isIdentifier(chunk))
  {
    nextChunk();
    if (chunk == "is")
    {
      nextChunk();
      is_Expression();
      if (chunk == "!")
        nextChunk();
      else
        fail();
    }
    else
      fail();
  }
  else 
    fail();
}

//IncStatement := inc identifier !
void is_IncStatement()
{
  if (chunk == "inc")
  {
    nextChunk();
    if(isIdentifier(chunk))
    {
      nextChunk();
      if (chunk == "!")
        nextChunk();
      else
        fail();
    }
    else
      fail();
  }
  else
    fail();
}

//RetStatement := ret identifier !
void is_RetStatement()
{
  if (chunk == "ret")
  {
    nextChunk();
    if(isIdentifier(chunk))
    {
      nextChunk();
      if (chunk == "!")
        nextChunk();
      else
        fail();
    }
    else
      fail();
  }
  else
    fail();
}

//IfStatement := if $ Expression $ StatementSequence  [ ex StatementSequence ] fi
void is_IfStatement()
{
  if(chunk == "if")
  {
    nextChunk();
    if (chunk == "$")
    {
      nextChunk();
      is_Expression();
      if (chunk == "$")
      {
        nextChunk();
        is_StatementSequence();
        if (chunk == "ex")
        {
          nextChunk();
          is_StatementSequence();
        }
        if (chunk == "fi")
          nextChunk();
        else
          fail();
      }
      else
        fail();
    }
    else
      fail();
  }
  else
    fail();
}

//LoopStatement = loop $ Expression $ StatementSequence pool
void is_LoopStatement()
{
  if(chunk == "loop")
  {
    nextChunk();
    if(chunk == "$")
    {
      nextChunk();
      is_Expression();
      if (chunk == "$")
      {
        nextChunk();
        is_StatementSequence();
        if (chunk == "pool")
          nextChunk();
        else
          fail();
      }
      else
        fail();
    }
    else
      fail();
  }
  else
    fail();
}

//PrintStatement = print identifier !
void is_PrintStatement()
{
  if (chunk == "print")
  {
    nextChunk();
    if(isIdentifier(chunk))
    {
      nextChunk();
      if (chunk == "!")
        nextChunk();
      else
        fail();
    }
    else
      fail();
  }
  else
    fail();
}

//Statement := [ Assignment | IfStatement | LoopStatement | PrintStatement | IncStatement | RetStatement ]
void is_Statement()
{
  if (isIdentifier(chunk))
    is_Assignment();
  else if (chunk == "if")
    is_IfStatement();
  else if (chunk == "loop")
    is_LoopStatement();
  else if (chunk == "print")
    is_PrintStatement();
  else if (chunk == "inc")
    is_IncStatement();
  else if (chunk == "ret")
    is_RetStatement();
}

//StatementSequence = Statement { Statement }
void is_StatementSequence()
{
  is_Statement();
  while (isIdentifier(chunk) || chunk == "if" || chunk == "loop" || chunk == "print" || chunk == "inc" || chunk == "ret")
  {
    is_Statement();
  }
}

//ParamSequence :=  identifier  { , identifier } 
void is_ParamSequence()
{
  if (isIdentifier(chunk))
  {
    nextChunk();
    while(chunk == ",")
    {
      nextChunk();
      if (isIdentifier(chunk))
        nextChunk();
      else
        fail();
    }
  }
  else
    fail();
}

//RoutineDeclaration := prog identifier ( [ ParamSequence ] ) blip StatementSequence blorp
void is_RoutineDeclaration()
{
  if (chunk == "prog")
  {
    nextChunk();
    if(isIdentifier(chunk))
    {
      nextChunk();
      if (chunk == "(")
      {
        nextChunk();
        if (isIdentifier(chunk))
          is_ParamSequence();
        if (chunk == ")")
        {
          nextChunk();
          if (chunk == "blip")
          {
            nextChunk();
            is_StatementSequence();
            if (chunk == "blorp")
              nextChunk();
            else
              fail();
          }
          else
            fail();
        }
        else
          fail();
      }
      else
        fail();
    }
    else
      fail();
  }
  else
    fail();
}


//************************ROOT***********************//

int main()
{  

  nextChunk();
  is_RoutineDeclaration();

  cout<<"CORRECT"<<endl;

  return 0;
}