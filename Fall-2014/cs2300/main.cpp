//Chris Peabody
//Sean Ryan
//Adam Kochan
//12-8-2014
//file: main.cpp
//Purpose: A database to facilitate the creation and finding of game night sessions

#include <iostream>
#include <ctime>
#include <cstdlib>
#include "verified.h"
using namespace std;

int main()
{
  int menu1, menu2;
  srand(time(NULL));

  //Main program loop
  do
  {
    cout<<"Welcome! [Input number]"<<endl;
    cout<<"\t1. Login\n\t2. Exit"<<endl;

    cin>>menu1;
    while(menu1 < 1 || menu1 > 2) //Input cleansing for login
    {
      cout<<"\nPlease enter a valid number."<<endl;
      cin>>menu1;
    }

    if(menu1 == 1)
    {
    	string username, name, genre;
      bool verified = false;

      cout<<"\nUsername: ";
      cin>>username;

      //-----TODO: IF USER EXISTS, SET VERIFIED TO TRUE-----//

      if(verified == true)
        menu(username); //Passes username into next menus
      else
      {
        cout<<"\nThat username does not exist."<<endl;
        cout<<"\t1. Create it\n\t2. Back"<<endl;

        cin>>menu2;
        while(menu2 < 1 || menu2 > 2) //Input cleansing for login
        {
          cout<<"\nPlease enter a valid number."<<endl;
          cin>>menu2;
        }

        if (menu2 == 1)
        {
          cout<<"Please enter your info.\nUsername: "<<username<<endl;
          cout<<"First name: ";
          cin>>name;
          cout<<"Favorite genre: ";
          cin>>genre;

          cout<<"\nCreating and logging in. . ."<<endl;

          //-----TODO: ADD USER TO DATABASE-----//
          menu(username);
        }
      }
    }
  }while(menu1 != 2); //Option 3 is exit

  cout<<"\nThank you. Goodbye!";

  return 0;
}