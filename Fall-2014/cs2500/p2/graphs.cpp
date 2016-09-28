//Chris Peabody
//Gary Warren
//Billy Dodds
//11-25-2014
//file: graphs.cpp

#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;

const int NUMNODES = 5;

struct graph
{
	int weights[NUMNODES][NUMNODES]; //Stores weights from each edge to each other edge

	void print() //Print out all values in the table
	{
		for (int y = 0; y < NUMNODES; y++)
		{
			for (int x = 0; x < NUMNODES; x++)
				cout << weights[x][y] << " ";
			cout << endl;
		}
	}

	void clear() //sets all values to -1 to show they need to be set
	{
		for (int x = 0; x < NUMNODES; x++)
			for (int y = 0; y < NUMNODES; y++)
				weights[x][y] = -1;
	}

	void generate() //To create a random graph
	{
		//FOR EACH SLOT IN MATRIX
		for (int x = 0; x < NUMNODES; x++)
		{
			for (int y = 0; y < NUMNODES; y++)
			{
				//SKIP REFLEXIVE EDGES (edges that connect to themself)
				if (x != y)
				{
					if (weights[x][y] == -1) //Only change unset edges
					{
						int num = rand()%20-10; //Random number from -10 to 10
						if (num < 0) {num = 0;} 	//If below 0, set to zero
						//Zero means no connection

						//Fill edges concerned (AB and BA for example) with weight
						weights[x][y] = num;
						weights[y][x] = num;
					}
				}
				else
				{
					//Set reflexive edges to "unset" (-1)
					weights[x][y] = -1;
				}
			}
		}

		return;
	}
};

//Single Source Shortest-Path
void SSSP(graph nodes, int source, int dist[])
{			
	//Dist is an array for how far each node is from our source
	for (int i = 0; i < NUMNODES; i++)
		dist[i] = -1;			//Give initial values (-1 represents infinity)
	dist[source] = 0;			//Source has distance value of 0

	int finished[NUMNODES];		//Array storing whether each node has its shortest value yet
	for (int i = 0; i < NUMNODES; i++)
		finished[i] = 0;		//0 unfinished, 1 finished

	int curr = source; 			//Start current at source

	bool done = false;			//for use in while loop
	do
	{
		for (int i = 0; i < NUMNODES; i++)
		{
			//Skip self,
			//Make sure nodes are connected,
			//Make sure node is unfinished
			if (curr != i && nodes.weights[curr][i] != 0 && finished[i] == 0)
				//if distance to node is inf, or this path is shorter
				if (dist[i] == -1 || dist[curr] + nodes.weights[curr][i] < dist[i])
					//Set the shortest path to the node to this path
					dist[i] = dist[curr] + nodes.weights[curr][i];
		}
		finished[curr] = 1; //we are done with this node

		//IF ANY UNFINISHED NODE IS NOT INFINITY
		//(If there are still connected nodes unfinished)
		done = true;
		for(int i = 0; i < NUMNODES; i++)
			if (finished[i] == 0 && dist[i] != -1)
				done = false;
		//THEN WE HAVE TO KEEP GOING

		if (done == false) //Time to set new current node
		{
			int smallestval = -2; //arbitrary marker value
			int smallestnode = 0; //Actual node number
			for (int i = 1; i < NUMNODES; i++)
			{
				//Don't mess with finished/inf values
				if (finished[i] == 0 && dist[i] != -1) 
				{
					if (dist[i] < smallestval || smallestval == -2)
					{
						smallestval = dist[i];
						smallestnode = i;
					}
				}
			}

			 //We continue the algorithm with the node with the smallest dist
			curr = smallestnode;
		}
	}while(done == false);

	return; //dist is now modified
}

int main ()
{
	srand(time(NULL)); //Seeding the random number generator

	graph nodes;
	nodes.clear();
	nodes.generate();
	nodes.print();

	int dist[NUMNODES];
	//Run SSSP with graph "nodes", source a first node, and modifying "dist"
	SSSP(nodes, 0, dist);

	cout<<"Distances: "<<endl;
	for (int i = 0; i < NUMNODES; i++)
		cout<<dist[i]<<" ";

	return 0;
}