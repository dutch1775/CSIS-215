#pragma once

#include "GraphADT.h"
#include <iostream>
#include <string>
#include <sstream>
#include <fstream>

class MCST : public Graph {
private:
	int numVertex, numEdge;					//number of vetices and edges for the graph
	int** matrix;							//dynamic matrix
	int* mark;								//dynamic mark table
	std::ifstream readFile;					//input to read file from
	std::ofstream writeFile;				//output to wrtie to
	enum MARK { VISITED, UNVISITED };		//enum for vist status

	// Read graph from file
	void read(std::string file)
	{
		std::string input;					//string input from file
		int inVert;							//variable to hold vertices number from file
		int index = 0;						//index of file
		int row = 0;						//row for weights
		int weight = 0;						//weights for input

		//open the graph file
		readFile.open(file);

		while (std::getline(readFile, input))	//while we are still reading data
		{
			if (index == 0)	//if at index 0 (first line of file)
			{
				int readIndex = (int)input.find("VERTICES=");	//if VERTICES= line is present, save the index
				
				//if the read index is set
				if (readIndex != std::string::npos)
				{
					//grab number of vertices from file as an int
					inVert = stoi(input.substr(readIndex + 9, (input.size() - readIndex + 9)));
					//initialize the matrix with number of vertices
					Init(inVert);
				}
			}
			else
			{
				std::stringstream inWeight;		//string stream var to file string to int
				inWeight.str(input);			//string stream set as input we read in

				//loop through matrix
				for (int col = 0; col < inVert; col++) 
				{
					//the weight we grabed from file into weight var
					inWeight >> weight;
					//if weight is set 
					if (weight != 0) 
					{
						setEdge(row, col, weight);	//add edge with weight
					}
					weight = 0;	//set weight to zero for next iteration
				}
				row++;	//increment row to read weight from
			}
			input.clear();	//clear input string
			index++;		//move down the file
		}

		readFile.close();	//close the file
	}

	// Find minimum cost vertex
	int minVertex(MCST* G, int* D) 
	{
		int i, v = -1;
		// Get first unvisited node
		for (i = 0; i < G->n(); i++) 
		{
			if (G->getMark(i) == UNVISITED) 
			{
				v = i;
				break;
			}
		}
		// Check all subsequent nodes to see if one exists such that 
		// A) it is also unvisited
		// B) it has a cheaper cost
		for (i++; i < G->n(); i++) 
		{
			if (G->getMark(i) == UNVISITED && D[i] < D[v]) 
			{
				v = i;
			}
		}
		return v;
	}


public:

	//constructors
	MCST(int v) 
	{
		Init(v);
	}
	MCST(std::string file) 
	{
		read(file);
	}

	//destructor
	~MCST() 
	{
		delete[] mark;
		for (int i = 0; i < numVertex; i++) 
		{
			delete[] matrix[i];
		}
		delete[] matrix;
	}

	// Initialize a graph of n vertices
	void Init(int n) 
	{
		int i;
		numVertex = n;
		numEdge = 0;
		mark = new int[n];

		// Mark all nodes as unvisited
		for (i = 0; i < numVertex; i++) 
		{
			mark[i] = UNVISITED;
		}

		// Build matrix
		matrix = (int**) new int* [numVertex];
		for (i = 0; i < numVertex; i++) 
		{
			matrix[i] = new int[numVertex];
		}

		// Set all edge weights to 0
		for (i = 0; i < numVertex; i++) 
		{
			for (int j = 0; j < numVertex; j++)
			{
				matrix[i][j] = 0;
			}
		}
	}

	// Return: the number of vertices and edges
	int n() const 
	{
		return numVertex;
	}

	int e() const
	{
		return numEdge;
	}

	// Return v’s first neighbor
	int first(int v) const 
	{
		int n = this->n();
		for (int i = 0; i < n; i++) 
		{
			if (matrix[v][i] != 0) 
			{
				n = i;
				break;
			}
		}
		return n;
	}

	// Return v’s next neighbor
	int next(int v, int w) const 
	{
		int n = numVertex;
		for (int i = w + 1; i < numVertex; i++) 
		{
			if (matrix[v][i] != 0) 
			{
				n = i;
				break;
			}
		}
		return n;
	}

	// Set the weight for an edge
	void setEdge(int v1, int v2, int wt) 
	{
		if (wt >= 0) 
		{
			if (matrix[v1][v2] == 0) 
			{
				numEdge++;
			}
			matrix[v1][v2] = wt;
		}
	}

	// Delete an edge
	void delEdge(int v1, int v2) 
	{
		if (matrix[v1][v2] != 0) 
		{
			numEdge--;
		}
		matrix[v1][v2] = 0;
	}

	// Determine if an edge is in the graph
	bool isEdge(int v1, int v2) const 
	{
		return matrix[v1][v2] != 0;
	}

	// Return an edge’s weight
	int weight(int v1, int v2) const {

		return matrix[v1][v2];
	}

	// Get and Set the mark value for a vertex
	int getMark(int v) const 
	{
		return mark[v];
	}

	void setMark(int v, int val) 
	{
		mark[v] = val;
	}

	//print the graph matrix
	void print(int i) const 
	{
		//if 0 then print out all data on the MCST
		if (i == 0) 
		{
			std::cout << "Number of vertices is " << numVertex << std::endl;
			std::cout << "Number of edges is " << numEdge << std::endl;
			std::cout << "Matrix is:" << std::endl;
		}

		//loop over the matrix and print
		for (int row = 0; row < numVertex; row++) 
		{
			for (int col = 0; col < numVertex; col++) 
			{
				std::cout << matrix[row][col] << ' ';
			}
			std::cout << std::endl;
		}
		std::cout << std::endl;
	}

	//write the mcst to a file
	void write(std::string file)
	{
		writeFile.open(file);	//open file to write

		writeFile << "VERTICES=" << numVertex << std::endl;	//print formatting and number of vertices

		//loop over the matrix and print it to the file
		for (int row = 0; row < numVertex; row++) 
		{
			for (int col = 0; col < numVertex; col++) 
			{
				writeFile << matrix[row][col];

				//space between the numbers until end of matrix
				if (col + 1 < numVertex) 
				{
					writeFile << " ";
				}
			}
			writeFile << std::endl; // newline for formatting
		}

		writeFile.close();	//close the file
	}

	//make MCST from statring vertex s
	MCST* Prim(int s) 
	{
		MCST* mst = new MCST(numVertex);	//make dynamic MCST with the same num of vertices
		std::cout << std::endl << "Begin MST starting at Vertex " << s << std::endl;	//prompt start

		int* D = new int[this->n()]; // Array of weights
		int* V = new int[this->n()]; // closest vertex
		int i, w;

		//set all weights to "infinity", INT_MAX
		for (int i = 0; i < this->n(); i++) 
		{
			D[i] = INT_MAX;
			V[i] = INT_MAX;
			this->setMark(i, UNVISITED);	//set as unvisted
		}

		D[s] = 0;

		//process the vertices
		for (i = 0; i < this->n(); i++)
		{
			int v = minVertex(this, D); //find min vertex
			this->setMark(v, VISITED);	//set as visited

			if (v != s)	//if vertex is not start
			{
				//prompt edge being added and add edge
				std::cout << "Add edge " << V[v] << " to " << v << std::endl;
				mst->setEdge(V[v], v, D[v]);
				mst->setEdge(v, V[v], D[v]);
			}

			if (D[v] == INT_MAX) return mst; //if infinity then abort, unreachable vertices

			for (w = this->first(v); w < this->n(); w = this->next(v, w))
			{
				if (D[w] > this->weight(v, w))
				{
					D[w] = this->weight(v, w);	//update distance
					V[w] = v;					//where it came from
				}
			}
		}
		delete[] D;
		delete[] V;

		//print graph and return the made MCST
		std::cout << std::endl;
		mst->print(1);
		return mst;
	}
};