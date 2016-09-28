#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <iostream>

using namespace std;
 
void knapsack(int n, float weight[], float profit[], float capacity) {
   float x[20], tp = 0;
   int i, u;
   u = capacity;
 
   for (i = 0; i < n; i++)
      x[i] = 0.0;
 
   for (i = 0; i < n; i++) {
      if (weight[i] > u)
         break;
      else {
         x[i] = 1.0;
         tp = tp + profit[i];
         u = u - weight[i];
      }
   }
 
   if (i < n)
      x[i] = u / weight[i];
 
   tp = tp + (x[i] * profit[i]);
 
   printf("\nThe result is: ");
   for (i = 1; i < n-1; i++){

	  printf("%f\t", profit[i]);
     }
   printf("\nMaximum profit is: %f", tp);
 
}
 
int main() {
   srand(time(0));
   float weight[20], profit[20], capacity;
   int  i, j;
   int const num= rand() % 10;
   float ratio[20], temp;
 
   for ( int i = 0; i < num; i++) {
        weight[i]=rand() % 10;
		cout<<"weight "<<i<<" is "<<weight[i]<<endl;
		profit[i]= rand() % 10;
		cout<<"value "<<i<<" is "<< profit[i]<<endl;
   }	

   capacity= rand() % 8;
   cout<<"capacity is "<<capacity<<endl;   
   for (i = 0; i < num; i++) {
      ratio[i] = profit[i] / weight[i];
   }
 
   for (i = 0; i < num; i++) {
      for (j = i + 1; j < num; j++) {
         if (ratio[i] < ratio[j]) {
            temp = ratio[j];
            ratio[j] = ratio[i];
            ratio[i] = temp;
 
            temp = weight[j];
            weight[j] = weight[i];
            weight[i] = temp;
 
            temp = profit[j];
            profit[j] = profit[i];
            profit[i] = temp;
         }
      }
   }
 
   knapsack(num, weight, profit, capacity);
   return(0);
}