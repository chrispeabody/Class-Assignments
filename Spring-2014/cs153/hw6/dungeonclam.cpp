//Chris Peabody
//CS 153 Section C
//Date: 5/6/2014
//file: dungeonclam.cpp

#include <iostream>
using namespace std;

bool Success(char **maze, int x, int y);
bool IsValid(char **maze, int x, int y);
bool move(char **maze, int x, int y);
void findZ(char **maze,int & x,int & y,int cs,int rs);

int main()
{
  int rs,cs,x,y,counter=0;
  
  char** maze;
  char char_var;
  
  do
  {
    cin>>cs>>rs;
    if (cs<=0||cs<=0)
      return 0;

    cin.ignore();
    maze = new char*[rs];
    for(int i=0; i < rs; i++)
      maze[i] = new char[cs]; 
 
    for(int j=0; j < rs; j++)
    {
      for(int k=0; k < cs; k++)
        cin.get(maze[j][k]);
      cin.get(char_var);   
    }
  
    //Locate Zoidberg
    findZ(maze,x,y,cs,rs);

    cout<<"map: "<<counter<<endl;
    if(move(maze,x,y))
    {
      for(int j=0; j < rs; j++)
      {
        for(int k=0; k < cs; k++)
          cout << maze[j][k];
        cout << endl;
      }
      cout << endl;
    }
    else
      return 0;
  
    for(int i=0; i < rs; i++)
      delete [] maze[i];
    delete [] maze;

    counter++;
  } while (cs>0&&rs>0);

  return 0;
}

bool Success(char** maze,int x,int y)
{
  if(maze[x][y] == 'E')
  {
    return true;
  }
  return false;
}

//recursion
bool move(char** maze, int x,int y) 
{
	//If adjacent to E
	if(Success(maze,x,y+1)||Success(maze,x+1,y)||Success(maze,x-1,y)||Success(maze,x,y-1))
	{
		return true;
	}

  //move up
    if(IsValid(maze,x,y+1))  
  {
    maze[x][y+1] = '.';
    if(move(maze,x,y+1))
    {
      return true;
    }else
    {
      maze[x][y+1] = ' ';     
    }
  }
    //right
    if(IsValid(maze,x+1,y))  
  {
    maze[x+1][y] = '.';
    if(move(maze,x+1,y))
    {
      return true;
    }else
    {
      maze[x+1][y] = ' ';
    }
      
  }
       //  left
    if(IsValid(maze,x-1,y))
  {
    maze[x-1][y] = '.';
    if(move(maze,x-1,y))
    {
      return true;
    }else
    {
      maze[x-1][y] = ' ';   
    }
  }
    //down
    if(IsValid(maze,x,y-1)) 
  {
    maze[x][y-1] = '.';
    if(move(maze,x,y-1))
    {
      return true;
    }else
    {
      maze[x][y-1] = ' ';   
    }
  }


	return false;
}	

void findZ(char** maze,int & x,int & y,int cs,int rs)
{
  for(int k=0; k < rs; k++)
    for(int j=0; j < cs; j++)
      if(maze[k][j] == 'Z')
	    {
    	  x = k;
    		y = j;
	    }
}
  
bool IsValid(char** maze,int x,int y)
{
  if(maze[x][y] == ' ')
  {
    return true;
  }
  return false;
}



