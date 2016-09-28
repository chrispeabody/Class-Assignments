//Chris Peabody
//Sean Ryan
//Adam Kochan
//12-8-2014
//file: verified.cpp

#include <iostream>
#include <ctime>
#include <cstdlib>
using namespace std;

void menu(string username)
{
  int menu1, menu2, menu3;

  do
  {
    cout<<"Options: "<<endl;
    cout<<"\t1. Create session\n\t2. My created sessions\n\t3. My joined sessions\n\t4. Find sessions\n\t5. Games\n\t6. My account\n\t7. Back"<<endl;

    cin>>menu1;
    while(menu1 < 1 || menu1 > 7)
    {
      cout<<"Please enter a valid number."<<endl;
      cin>>menu1;
    }

    if (menu1 == 1)
    {
      string location, date, game, reoccur;
      bool reoccuring, valid = false;
      int ID;

      cout<<"Game: ";
      cin>>game;

      //-----TODO: MAKE SURE GAME EXISTS-----/

      if(valid == true)
      {
        cout<<"Enter the desired details: "<<endl;
        cout<<"Location: ";
        cin>>location;
        cout<<"Date: ";
        cin>>date;

        cout<<"Reoccurring (y/n): ";
        cin>>reoccur;
        while(reoccur != "y" && reoccur != "n")
        {
          cout<<"(y/n): ";
          cin>>reoccur;
        }
        if (reoccur == "y") {reoccuring = true;}
        else {reoccuring = false;}

        do
        {
          ID = rand()%1000+1; //GENERATE RANDOM ID
          //-----TODO: CHECK IF ID ALREADY EXISTS-----//
        }while(false); //WHILE ID ALREADY EXISTS

        //-----TODO: CREATE NEW SESSION, ADD GAME/SESSION RELATIONSHIP-----//
      }
      else
      {
        cout<<"\nThat game does not exist. You can add it to the list."<<endl;
      }
    }

    if(menu1 == 2)
    {
      cout<<"Sessions you've created: "<<endl;
      //-----TODO: FIND ALL SESSIONS THIS USER CREATED-----//

      cout<<"Options:"<<endl;
      cout<<"\t1. Session details\n\t2. Delete session\n\t3. Back"<<endl;
      cin>>menu2;
      while (menu2 < 1 || menu2 > 3)
      {
        cout<<"Please enter a valid option."<<endl;
        cin>>menu2;
      }

      if (menu2 == 1)
      {
        cout<<"Enter session ID#: ";
        cin>>menu3;

        //IF VALID ID:
        //-----TODO: LIST ALL USERS IN SESSION, AND OTHER DETAILS-----//

        //WHILE MORE PENDING REQUESTS
        //{
          cout<<"You have a request to join from: "<<endl;
          //-----TODO: LIST PENDING USER INFO-----//
          cout<<"\n\t1. Accept\n\t2. Deny\n\t3. Wait"<<endl;
          cin>>menu3;
          while (menu3 < 1 || menu3 > 3)
          {
            cout<<"Please enter a valid option."<<endl;
            cin>>menu3;
          }

          if(menu3 == 1)
          {
            //-----TODO: MOVE USER FROM PENDING TO IN GAME-----//
          }
          if(menu3 == 2)
          {
            //-----TODO: REMOVE USER FROM PENDING-----//
          }

        //}
      }

      if (menu2 == 2)
      {
        cout<<"Enter session ID#: ";
        cin>>menu3;

        //IF VALID ID && USER OWNS SESSION:
        //-----TODO: REMOVE FROM TABLE THE SESSION WITH ID-----//
      }
    }

    if(menu1 == 3)
    {
      cout<<"Session's you've joined: "<<endl;

      //-----TODO: LIST SESSIONS THIS USER IS IN (JOINED ONLY)-----//

      cout<<"Options:"<<endl;
      cout<<"\t1. Session details\n\t2. Leave session\n\t3. Back"<<endl;
      cin>>menu2;
      while (menu2 < 1 || menu2 > 3)
      {
        cout<<"Please enter a valid option."<<endl;
        cin>>menu2;
      }

      if (menu2 == 1)
      {
        cout<<"Enter session ID#: ";
        cin>>menu3;

        //IF VALID ID:
        //-----TODO: LIST ALL USERS IN SESSION, AND OTHER DETAILS-----//
      }

      if (menu2 == 2)
      {
        cout<<"Enter session ID# to leave: ";
        cin>>menu2;

        //IF VALID ID:
        //-----TODO: REMOVE USER FROM SESSION-----//
      }
    }

    if(menu1 == 4)
    {
      cout<<"Open sessions: "<<endl;

      //-----TODO: LIST SESSIONS (GAME, LOCATION, DATE, ID)-----//

      cout<<"Options: "<<endl;
      cout<<"\t1. Join session\n\t2. Back"<<endl;

      cin>>menu2;
      while (menu2 < 1 || menu2 > 2)
      {
        cout<<"Please enter a valid option."<<endl;
        cin>>menu2;
      }

      if (menu2 == 1)
      {
        cout<<"Enter session ID# to request join: ";
        cin>>menu3;

        //-----IF VALID ID: ADD USER TO PENDING REQUEST TABLE FOR THIS SESSION-----//
      }
    }

    if(menu1 == 5)
    {
      cout<<"Existing Games: "<<endl;

      //-----TODO: LIST GAMES AND THEIR INFO-----//

      cout<<"Options: "<<endl;
      cout<<"\t1. Add Game\n\t2. Back"<<endl;

      if (username == "ADMIN")
      {
        cout<<"\nADMIN OPTION:\n\t3. Delete Game"<<endl;
      }

      cin>>menu2;
      while(menu2 < 1 || (menu2 > 2 && username != "ADMIN") || menu2 > 3)
      {
        cout<<"Please enter a valid option.";
        cin>>menu2;
      }

      if (menu2 == 1)
      {
        int min, max;
        string title, genre;

        cout<<"Enter the game info below."<<endl;
        cout<<"Title: ";
        cin>>title;
        cout<<"Genre: ";
        cin>>genre;
        cout<<"Min players: ";
        cin>>min;
        cout<<"Max players: ";
        cin>>max;

        //IF GAME DOESN'T EXIST
        //-----TODO: PUT GAME IN GAME TABLE-----//
        //ELSE
        cout<<"\nThat game already exists!"<<endl;
      }

      if (menu2 == 3)
      {
        string title;
        cout<<"Enter the game title to delete: ";
        cin>>title;

        //-----TODO: DELETE GAME AND WHATNOT-----//
      }
    }

    if(menu1 == 6)
    {
      cout<<"Your information: "<<endl;

      //-----TODO: RETRIEVE AND DISPLAY INFO-----//

      cout<<"Options: "<<endl;
      cout<<"\t1. Change info\n\t2. Back"<<endl;

      cin>>menu2;
      while(menu2 != 1 && menu2 != 2)
      {
        cout<<"Please enter a valid option.";
        cin>>menu2;
      }

      if (menu2 == 1)
      {
        string name, genre;

        cout<<"Please enter your info.\nUsername: "<<username<<endl;
        cout<<"First name: ";
        cin>>name;
        cout<<"Favorite genre: ";
        cin>>genre;

        //-----TODO: UPDATE INFO-----//

        cout<<"\nUpdated!";
      }
    }

  }while(menu1 != 7);
}