//CHRIS PEABODY
//4/15/2014
//file: braincalc.cpp
//purpose: main file

#include <iostream>
#include <cstdlib>
#include "arraystack.h"
#include "abstractstack.h"
using namespace std;

int main()
{
  arrayStack<int> memory; //The brain's short term memory stack
  string input; //The input to the program
  int temp1; //Variables for handling popped ints
  int temp2; // - - -

  do
  {
    cin>>input;

    if(input=="+")
    {
      temp2=memory.top();
      memory.pop();
      temp1=memory.top();
      memory.pop();

      memory.push(temp1+temp2);
    }
    else if(input=="-")
    {
      temp2=memory.top();
      memory.pop();
      temp1=memory.top();
      memory.pop();

      memory.push(temp1-temp2);
    }
    else if(input=="*")
    {
      temp2=memory.top();
      memory.pop();
      temp1=memory.top();
      memory.pop();

      memory.push(temp1*temp2);
    }
    else if(input=="/")
    {
      temp2=memory.top();
      memory.pop();
      temp1=memory.top();
      memory.pop();

      memory.push(static_cast<int>(temp1/temp2));
    }
    else if(input=="%")
    {
      temp2=memory.top();
      memory.pop();
      temp1=memory.top();
      memory.pop();

      memory.push(temp1%temp2);
    }
    else if(input=="!")
    {
      temp1=memory.top();
      memory.pop();

      memory.push(-temp1);
    }
    else if(input=="$")
    {
      cout<<"[ ";
      while(!memory.isEmpty())
      {
        cout<<memory.top();
        memory.pop();
        if(!memory.isEmpty())
          cout<<", ";
      }
      cout<<" ]"<<endl;
    }
    else if(input!="#")//Input is a number
    {
      temp1 = atoi(input.c_str());
      memory.push(temp1); //puts int on stack
    }

  } while(input!="#");

  return 1;
}