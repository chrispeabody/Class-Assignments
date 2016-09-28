//Chris Peabody
//CS 153 Section C
//Date: 5/6/2014
//file: dungeonclam.cpp

#include <iostream>
using namespace std;
#include "funct.h"

int main()
{
  //Size of incoming maze
  int cs, rs;
  int map_number=0; //current map we're on

  do
  {
    // Maze is a 2D array of characters
    char** maze;

    // Readin size of Maze
    cin >> cs >> rs; 
    cout << cs << " " << rs << endl;
    cin.ignore();    // to move read head to next line
        
    // Allocate Maze Array
    maze = new char*[rs];
    for(int k=0; k < rs; k++){
      maze[k] = new char[cs];
    }  
    
    // Read Maze Array
    char dummy;
    for(int k=0; k < rs; k++){
      for(int j=0; j < cs; j++){
        cin.get(maze[k][j]);
      }
      cin.get(dummy);   // read end-of-line
    }

    //find the start
    for(int k=0; k < cs; k++)
      for(int j=0; j < rs; j++)
        if(maze[k][j]=='Z')
          tryMove(maze, cs, rs, j, k);

    // Print Maze Array
    for(int k=0; k < rs; k++){
      for(int j=0; j < cs; j++){
        cout << maze[j][k];
      }
      cout << endl;   // read end-of-line
    }
    
    // De-allocate Maze Array
    for(int k=0; k < rs; k++){
      delete [] maze[k];
    }
    delete [] maze;

    map_number++;
  } while(cs>0&&rs>0);

  return 0;
}