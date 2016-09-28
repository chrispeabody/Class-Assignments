//Chris Peabody - CS153
//3/19/2014
//file: packages.cpp
//purpose: the main driver for the program

#include <iostream>
using namespace std;
#include <iomanip>
#include "abstractpackage.h"
#include "pack2d.h"
#include "pack3d.h"
#include "pack4d.h"

int main()
{
  cout.setf(std::ios_base::fixed, std::ios_base::floatfield);
  cout.precision(2);

  int pack_num; //number of packages
  int type; //stores package dimensions (2, 3, or 4)
  float total_charge=0;
  int counter = 0;

  string temp_to, temp_from;
  float temp_x, temp_y, temp_z, temp_t, temp_weight;

  cout<<"Number of packages: ";
  cin>>pack_num;

  //AbstractPackage **load = new AbstractPackage*[pack_num];

  for(int i = 0; i < pack_num; i++)
  {
    cout<<"\nPackage Info: ";
    cin>>type;

    if (type==2)
    {
      
      cin>>temp_from;
      cin>>temp_to;
      pack2d package(temp_from,temp_to);
      cin>>temp_x;
      cin>>temp_y;

      package.setDim(temp_x, temp_y);

      cout<<"#"<<counter<<": From "<<package.getFrom()<<" to "<<package.getTo()<<endl;
      cout<<"$"<<package.getCharge();
      total_charge+=package.getCharge();
      counter++;

      //load[i] = &package;
    }
    if (type==3)
    {
      cin>>temp_from;
      cin>>temp_to;
      pack3d package(temp_from,temp_to);
      cin>>temp_x;
      cin>>temp_y;
      cin>>temp_z;
      cin>>temp_weight;

      package.setDim(temp_x, temp_y, temp_z, temp_weight);

      cout<<"#"<<counter<<": From "<<package.getFrom()<<" to "<<package.getTo()<<endl;
      cout<<"$"<<package.getCharge();
      total_charge+=package.getCharge();
      counter++;
      //load[i] = &package;
    }
    if (type==4)
    {
      cin>>temp_from;
      cin>>temp_to;
      pack4d package(temp_from,temp_to);
      cin>>temp_x;
      cin>>temp_y;
      cin>>temp_z;
      cin>>temp_t;
      cin>>temp_weight;

      cout<<"#"<<counter<<": From "<<package.getFrom()<<" to "<<package.getTo()<<endl;
      cout<<"$"<<package.getCharge();
      total_charge+=package.getCharge();
      counter++;

      package.setDim(temp_x, temp_y, temp_z, temp_t, temp_weight);
      //load[i] = &package;
    }
  }

  /*for(int i=0; i<pack_num; i++)
  {
    cout<<"\n#"<<i<<": From "<<load[i]->getFrom()<<" to "<<load[i]->getTo()<<endl;
    cout<<"$"<<load[i]->getCharge();

    total_charge+=load[i]->getCharge();
  }*/

  cout<<"\n\nTOTAL PROFIT = $"<<total_charge<<endl;
  cout<<"AVERAGE = "<<total_charge/pack_num<<endl;

  return 0;
}