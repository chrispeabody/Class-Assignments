//Name: CHRIS PEABODY
//Class: CS53 section B
//Date: 10/1/2013
//Purpose: To tell whether a given point lies in, out, or on a given cirlce

#include <iostream>
using namespace std;

struct circle
{
  //(x-h)^2+(y-k)^2 = r^2    respectively
  float m_h;
  float m_k;
  float m_r;
};


/*
Desc: Reads a circle and returns it
Pre:  None
Post: returns the circle
*/
circle readCircle();

/*
Desc: Prints appropraite message and gets the x and y coord of the point
Pre:  None
Post: return x and y coords
*/
void readPoint(float& f_x, float& f_y);

/*
Desc: Determines the relative position of the given point w.r.t. the circle
Pre:  Radius of the circle is non-negative
Post: Points relative position is returned (-1 IN, 0 ON, 1 OUT)
*/
int onInOut(const circle c, const float f_x, const float f_y);

/*
Desc: Display the result depending on the value of integer i_inOnOut
      (-1 IN, 0 ON, 1 OUT)
Pre:  i_inOnOut could be only -1, 0, or 1
Post  points relative position will be displayed in words
*/
void printResult(const int i_inOnOut);

//CONST

int main()
{
  //point coords
  float xCoord;
  float yCoord;
  circle Circ; //the actual circle used throughout the program
  char ans; //Used only for y/n responses from user
  
  cout<<"\nWelcome to the cirlce-point coordinator.. thing."<<endl;
  
  do
  {
    cout<<"\nLet's define the circle!"<<endl;
    Circ = readCircle();
    cout<<"\nNow input the point!"<<endl;
    readPoint(xCoord, yCoord);
    printResult(onInOut(Circ,xCoord,yCoord));
    
    do
    {
      cout<<"\nRun the program again? (y/n)\nAnswer: ";
      cin>>ans;
    }while(ans!='y'&&ans!='n');
  }while(ans!='n');
  
  
  return 0;
}

circle readCircle()
{
  circle circ;
  cout<<"\nInput x of the orgin: ";
  cin>>circ.m_h;
  cout<<"Input y of the orgin: ";
  cin>>circ.m_k;
  cout<<"Input the radius of the circle: ";
  cin>>circ.m_r;
  
  return circ;
}

void readPoint(float& f_x, float& f_y)
{
  cout<<"\nInput the x coord of the point: ";
  cin>>f_x;
  cout<<"Input the y coord of the point: ";
  cin>>f_y;
  
  return;
}

int onInOut(const circle c,const float f_x, const float f_y)
{
  int result;
  float temp;
  float temp2;
  
  temp = (f_x-c.m_h)*(f_x-c.m_h)+(f_y-c.m_k)*(f_y-c.m_k); //(a-h)^2+(b-k)^2
  temp2 = c.m_r*c.m_r; //r^2
  
  if (temp>temp2)
  {
    result = 1; //OUT
  }
  else if (temp==temp2)
  {
    result = 0; //ON
  }
  else if (temp<temp2)
  {
    result = -1; //IN
  }
  
  return result;
}

void printResult(const int i_inOnOut)
{
  switch (i_inOnOut)
  {
    case -1:
      cout<<"\nThe point is inside the circle."<<endl;
      break;
    case 0:
      cout<<"\nThe point is on the circle."<<endl;
      break;
    case 1:
      cout<<"\nThe point is outside the circle."<<endl;
      break;
    default:
      cout<<"\nError in printResult. Invalid input."<<endl;
      break;
  }
  
  return;
}
