//Chris Peabody
//CS 153 Section C
//Date: 5/6/2014
//file: funct.cpp

#include <iostream>
using namespace std;

#include "funct.h"

bool valid(char **map, int map_x, int map_y, int x, int y)
{
  cout<<"Valid?"<<endl;
  if(x>=0 && y>=0 && x<map_x && y<map_y) //inside map
    if(map[x][y]==' '||map[x][y]=='E') //Open or exit
      return true;

  cout<<"Not valid."<<endl;
  return false;
}

bool tryMove(char **map, int map_x, int map_y, int x, int y)
{
  cout<<"Into tryMove()"<<endl;
  
  //x and y values to add for each direction. Right = 0, Up = 1, etc.
  int x_shift[4] = {1, 0, -1, 0};
  int y_shift[4] = {0, -1, 0, 1};

  for(int c=0; c<4; c++)
  {
    cout<<"Into for loop"<<endl;
    //Set new x and y
    int nx = x + x_shift[c];
    int ny = y + y_shift[c];
    cout<<"Current Coord: "<<x<<" "<<y<<endl;
    cout<<"New Coord: "<<nx<<" "<<ny<<endl;
    if(valid(map, map_x, map_y, nx, ny))
    {
      cout<<"Validated"<<endl;
      if(map[nx][ny]=='E') //Found exit
        return true;
      else
      {
        cout<<"No exit, recording"<<endl;
        //Record
        map[nx][ny]='.';
        if(tryMove(map, map_x, map_y, nx, ny)) //Keep going
          return true; //Path found ahead!
        else //Dead end ahead!
        {
          cout<<"Unrecording"<<endl;
          map[x][y]=' ';
        }
      }
    }
  }

  return false; //No way from here!
}