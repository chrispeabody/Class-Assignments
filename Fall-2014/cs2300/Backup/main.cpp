//Chris Peabody
//Sean Ryan
//Adam Kochan
//12-8-2014
//file: main.cpp
//Purpose: A database to facilitate the creation and finding of game night sessions

#include <iostream>
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
    cout<<"\t1. Login\n\t2. New User\n\t3. Exit"<<endl;

    cin>>menu1;
    while(menu1 < 1 || menu1 > 3) //Input cleansing for login
    {
      cout<<"\nPlease enter a valid number."<<endl;
      cin>>menu1;
    }

    if(menu1 == 1)
    {
    	string input1, input2;
      bool verified = false;

      cout<<"\nUsername: ";
      cin>>input1;
      cout<<"Password: ";
      cin>>input2;

      //-----TODO: VERIFY USER AND PASS AGAINST DATABASE-----//

      if(verified == true)
        menu(input1); //Passes username in
      else
        cout<<"\nThat username/password combination does not exist."<<endl;
    }

    if(menu1 == 2)
    {
      string username, name, pass1, pass2, genre;
      bool back = false;

      do //Entering username and password
      {
      	bool valid = false;
      	
        cout<<"Enter your information below."<<endl;
        cout<<"Username: ";
        cin>>username;
        cout<<"Password: ";
        cin>>pass1;
        cout<<"Re-enter password: ";
        cin>>pass2;

        //-----TODO: MAKE SURE NAME NOT TAKEN FIRST-----//
        if(pass1 == pass2)
          valid = true;

        if (valid == true)
        {
          cout<<"Valid name and password!"<<endl;
          cout<<"\t1. Back to main menu\n\t2. Choose new username/password\n\t3. Confirm/continue"<<endl;
          cin>>menu2;
          while(menu2 != 1 && menu2 != 2 && menu2 != 3)
          {
            cout<<"Please enter a valid option."<<endl;
            cin>>menu2;
          }
        }
        else
        {
          cout<<"Username taken, or passwords do not match."<<endl;
          cout<<"\t1. Back to main menu\n\t2. Try again\n\t"<<endl;
          cin>>menu2;
          while(menu2 != 1 && menu2 != 2)
          {
            cout<<"Please enter a valid option."<<endl;
            cin>>menu2;
          }
        }

        if (menu2 == 1 || menu2 == 3) {back = true;}
        if (menu2 == 2) {back = false;}

      } while(back == false);

      if (menu2 == 1) {break;}
      
      cout<<"Name: ";
      cin>>name;
      cout<<"Favorite game genre: ";
      cin>>genre;
      //Add preferred days, maybe somehow

      //-----TODO: ADD NEW USER TO THE DATABASE WITH GIVEN INFO-----//
    }
  }while(menu1 != 3); //Option 3 is exit

  cout<<"\nThank you. Goodbye!";

  return 0;
}