
#include <cstdlib>
#include <ctime>
#include <iostream>
using namespace std;

const int NUMITEMS = 5;

int knapsack(int Weights[], int Values[], int weightLeft, int index)
{
  int max = 0;
  int curr= 0;

  if (weightLeft == 0 || index == NUMITEMS)
    return 0;

  for(int x = index; x<NUMITEMS; x++)
  {
    if (weightLeft - Weights[x]>=0) //Item fits
    {
      int a;
      int b;

      a = knapsack(Weights, Values, weightLeft-Weights[x], index+1) + Values[x];
      b = knapsack(Weights, Values, weightLeft, index+1);

      curr = (a>b) ? a : b;
    }
    else //Item does not fit
    {
      curr = knapsack(Weights, Values, weightLeft, index+1);
    }

    if (curr > max)
      max = curr;
  }

  return max;
}

int main()
{
  int Weights[NUMITEMS];
  int Values[NUMITEMS];

  int knapsize = 7;

  srand(time(NULL));
  int W, V;

  for (int x = 0; x<NUMITEMS; x++)
  {
    W = rand()%10 + 1;
    V = rand()%10 + 1;

    Weights[x] = W;
    Values[x] = V;

    cout<<"\nItem weight: "<<W;
    cout<<"\nItem value: "<<V<<endl;
  }

  cout<<"\nKnapsack size: "<<knapsize;

  int optimal;
  optimal = knapsack(Weights, Values, knapsize, 0);

  cout<<"\n"<<optimal<<endl;

  return 0;
}