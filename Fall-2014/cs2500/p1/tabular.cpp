#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <vector>
#include <string>
#include <iostream>

using namespace std;

int M[2000][2000];
int knapsack(int value[], int weight[], int C, int n)
{      
  for(int i = 1; i <= C; i++)
  {
    for(int j = 0; j <n; j++)
    {
      if(j > 0)
      {
        M[j][i] = M[j-1][i];
        if (weight[j] <= i)
          M[j][i] = max(M[j][i], M[j-1][i-weight[j]]+value[j]);
      }
      else
      {
        M[j][i] = 0;
        if(weight[j] <= i)
          M[j][i] = max(M[j][i], value[j]);
      }
    }
  }        
  return M[n-1][C];
}  

int main()
{
	srand(time(0));
  int C, N;

  C= rand() % 10;
	cout<<"Capacity is "<<C<<endl;
	
	N= rand() % 10;
	cout<<"Number of items is "<<N<<endl;

  int* value = new int[N+1];
  int* weight = new int[N+1];
  for ( int i = 0; i < N; i++)
  {
    weight[i]=rand() % 10;
	  cout<<"\nItem weight: "<<weight[i];
	  value[i]= rand() % 10;
	  cout<<"\nItem value: "<<value[i]<<endl;
  }

  cout<<"\n"<<knapsack(value,weight,C,N)<<endl;
  
  return 0;
}