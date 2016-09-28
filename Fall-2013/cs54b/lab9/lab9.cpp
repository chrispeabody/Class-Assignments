//name: CHRIS PEABODY
//class: CS54 section B
//date: 10/22/2013
//file: lab9.cpp
//purpose: to mimic a login in server

#include "lab9.h"
#include <iostream>
using namespace std;


int main()
{
  char ans; //handles the y/n question at the end of the program
  char domain[11];
  string fullname;
  string username;
  string password;

  cout<<"\nWelcome."<<endl;
  do
  {
    //get credentials
    cout<<"\n\t\tLOGIN"<<endl;
    cout<<"Enter Domain: ";
    cin>>domain;

    cout<<"Enter Full Name: ";
    cin.ignore(500,'\n');
    getline(cin, fullname,'\n');

    cout<<"Enter Username: ";
    getline(cin, username, '\n');

    cout<<"Enter Password: ";
    getline(cin, password, '\n');

    //make domain all caps
    toAllCaps(domain);

    cout<<"\n\t\tSTATUS"<<endl;
    cout<<"Server: "<<domain<<endl;

    //Verify the username then the password
    if (!verifyUser(username))
      cout<<"Username not recognized.";
    else
    {
      cout<<"User: "<<username<<endl;
      if (!verifyPass(password))
        cout<<"ACCESS DENIED"<<endl;
      else
        cout<<"ACCESS GRANTED"<<endl;
    }

    //prompt for repeat
    do
    {
      cout<<"\n\nAgain? (y/n): ";
      cin>>ans;
    } while(ans!='y'&&ans!='n');
  } while(ans=='y');

  return 0;
}
