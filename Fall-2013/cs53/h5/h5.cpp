//Name: CHRIS PEABODY
//Class: CS53 section A
//Date: 9/30/2013
//Purpose: To assist math with fractions

#include <iostream>
using namespace std;

struct fraction
{
  short m_num; //numerator
  short m_den; //denominator
};

void greetings();    //Display greeting message
void goodbye();     //Display goodbye message
int menu();          //Display menu and take in option
fraction enterFrac();    //take in a fraction
void dispFrac(const fraction f1); //shows the fraction in a/b form
fraction addFrac(const fraction f1, const fraction f2);  //add
fraction divFrac(const fraction f1, const fraction f2);  //divide
fraction simpFrac(const fraction f1); //simplify

int main()
{
  int ans; //store the output from the menu function
  bool fracExist = false; //tells whether fractions have been entered
  fraction frac1; //fractions used througout
  fraction frac2; //^
  
  greetings();
  
  do
  {
    ans = menu();
    switch (ans)
    {
      case 1: //ENTER
        cout<<"\nFirst fraction:"<<endl;
        frac1 = enterFrac();
        cout<<"\nSecond fraction:"<<endl;
        frac2 = enterFrac();
        
        fracExist = true; //tells the rest of the program fractions obtained
        break;
      case 2: //ADD
        if (fracExist==false)
        {
          cout<<"\nYou have not entered fractions yet!"<<endl;
          break;
        }
        else
        {
          //Displays the results with dispFrac in between to show the fractions
          cout<<"\nAdding ";
          dispFrac(frac1);
          cout<<" to ";
          dispFrac(frac2);
          cout<<"\nResult: ";
          dispFrac(simpFrac(addFrac(frac1, frac2)));
          cout<<endl;
          break;
        }
      case 3: //DIVIDE
        if (fracExist==false)
        {
          cout<<"\nYou have not entered fractions yet!"<<endl;
          break;
        }
        else
        {
          //Displays the results with dispFrac in between to show the fractions
          cout<<"\nDividing ";
          dispFrac(frac1);
          cout<<" by ";
          dispFrac(frac2);
          cout<<"\nResult: ";
          dispFrac(simpFrac(divFrac(frac1, frac2)));
          cout<<endl;
          break;
        }
      case 4: //SIMPLIFY
        if (fracExist==false)
        {
          cout<<"\nYou have ont entered fractions yet!"<<endl;
          break;
        }
        else
        {
          //Displays teh results with dispFrac in between to show the fractions
          cout<<"\nFraction 1 (";
          dispFrac(frac1);
          cout<<") simplified: ";
          dispFrac(simpFrac(frac1));
          cout<<"\nFraction 2 (";
          dispFrac(frac2);
          cout<<") simplified: ";
          dispFrac(simpFrac(frac2));
          cout<<endl;
          break;
        }
    }
  } while(ans!=5);
  
  goodbye();
  return 0;
}

void greetings()
{
  cout<<"\nWelcome to the fractionator! (New name pending. . .)"<<endl;
  return;
}

void goodbye()
{
  cout<<"\nThanks for using the fraction-figurer! (Any better?)"<<endl;
  return;
}

int menu()
{
  int opt; //the chosen option
  
  do
  {
    cout<<"\nWhat would you like to do? (Enter valid option number)";
    cout<<"\n\t1. Enter fractions"
        <<"\n\t2. Add fractions"
        <<"\n\t3. Divide fractions"
        <<"\n\t4. Simplify fractions"
        <<"\n\t5. Exit"
        <<"\n\nAnswer: ";
    cin>>opt;
  } while(opt!=1&&opt!=2&&opt!=3&&opt!=4&&opt!=5); //redo until valid answer
  
  return opt;
}

fraction enterFrac()
{
  fraction f1;
  cout<<"Numerator: ";
  cin>>f1.m_num;
  cout<<"Denominator: ";
  cin>>f1.m_den;
  
  return f1;
}

void dispFrac(const fraction f1)
{
  cout<<f1.m_num<<"/"<<f1.m_den;

  return;
}

fraction addFrac(const fraction f1, const fraction f2)
{
  fraction result;
  result.m_num=((f1.m_num*f2.m_den)+(f1.m_den*f2.m_num));
  result.m_den=(f1.m_den*f2.m_den);
  
  return result;
}

fraction divFrac(const fraction f1, const fraction f2)
{
  fraction result;
  result.m_num=(f1.m_num*f2.m_den);
  result.m_den=(f1.m_den*f2.m_num);
  
  return result;
}

fraction simpFrac(const fraction f1)
{
  int big;
  int small;
  int answer;
  fraction result;
  
  big=((f1.m_num>f1.m_den)?f1.m_num:f1.m_den);
  small=((f1.m_num<f1.m_den)?f1.m_num:f1.m_den);
  
  answer = big%small;
  
  while(answer!=0)
  {
    big=small;
    small=answer;
    answer = big%small;      
  }
  //Now small is the greatest common diviser
  
  result.m_num=(f1.m_num/small);
  result.m_den=(f1.m_den/small);
  
  return result;  
}
