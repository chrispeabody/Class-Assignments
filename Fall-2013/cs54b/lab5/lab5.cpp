//Name: CHRIS PEABODY
//Class: CS54 Section B
//Date: 9/24/2013
//Purpose: To calculate the perimeter and area of a given rectangle

#include <iostream>
using namespace std;

//Function prototypes
void printMenu();
void Area(float f_side1, float f_side2);
void Perimeter(float f_side1, float f_side2);
float getSide();

int main()
{
  float side1, side2;
  int Ans; //menu control variable
  
  cout<<"Welcome to the rectangle-o-matic.. thing."<<endl;
  do
  {
    cout<<"Please enter the width."<<endl;
    side1 = getSide();
    cout<<"Please enter the height."<<endl;
    side2 = getSide();
    
    printMenu();
    cout<<"Answer: ";
    cin>>Ans;
    
    switch (Ans)
    {
      case 1:
        Area(side1,side2);
        break;
      case 2:
        Perimeter(side1,side2);
        break;
    }
    
  } while(Ans!=3);
}

void printMenu()
{
  cout<<"\nWhat would you like to find?\n\t1. Area\n\t2. Perimeter";
  cout<<"\n\t3. Exit"<<endl;
  
  return;
}

void Area(float f_side1, float f_side2)
{
  float area;
  area = f_side1*f_side2;
  cout<<"\nThe area of the rectangle is "<<area<<endl;
 
  return;
}

void Perimeter(float f_side1,float f_side2)
{
  float perimeter;
  perimeter = (2*f_side1)+(2*f_side2);
  cout<<"\nThe perimeter of the rectangle is "<<perimeter<<endl;

  return;
}

float getSide()
{
  float ans;
  cout<<"Answer: ";
  cin>>ans;
  
  return ans;
}
