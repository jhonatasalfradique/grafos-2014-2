//It's the Graph Class

#include <iostream>
#include "stdafx.h"
using namespace std;
#include <fstream>
#include <deque>


class Graph
{
	public:
	
	int n; //vertex number
	int m; //edge number
	deque<deque<int>> db; // graph
	
	Graph::Graph(string filename,int t)
	{
		m = 0;
		std::ifstream infile(filename);		//argumento de entrada nome do arquivo
		n = (int)infile.get();//get N from first line of file
		
		if (t = 2){//matrix
			deque<deque<int>> data(n, deque<int> (n+1,0)); // deque square matrix filled with 0 (extra slot for number of neighbors)
		
			// Begin reading your stream here
			int i, j; //vertex i and j from the graph
			while (infile >> i >> j){ // load pair of data in each variable
				data[i - 1][j - 1] = 1; // vertex i receive j as neighboor
				data[j - 1][i - 1] = 1; // vertex j receive i as neighboor
				m++; // each line add 1 edge
				data[i - 1][n] ++;//Grade + 1
				}
			db = data;
			}
		else {//lista de adjacencia
			deque<deque<int>> data(n, deque<int>(1,0)); //Deck de arestas de adjacencia (last entry number of neighbors)

			// Begin reading your stream here
			int i, j; //vertex i and j from the graph
			while (infile >> i >> j) // load pair of data in each variable
			{
				data[i - 1].back() = 1 + data[i - 1].back();//Grade + 1
				m++; // each line add 1 edge
				data[i - 1].push_front(j); // vertex i receive j as neighboor
				data[j - 1].push_front(i); // vertex j receive i as neighboor
			}
			db = data;
		}
		
	}
	

	void Output()
	{
		ofstream file; // output file
		file.open("output.txt");

		file << "# n = " << n << "\n";
		file << "# n = " << m << "\n";
		deque<double> egd;// empiric grade distribution

		for each (deque<int> di in db)
		{
			int grade = di.back();//Grade of vertex
			if (grade > (int) egd.size()) 
				{
				if (grade < (int) egd.max_size()) egd.resize(grade, 0); // check for memory leak
				else std::cout << "Error output stack overflow.\n";
				}
			egd[grade] += egd[grade]/n; //f(d) = n(d)/n
		}
		double totalegd = 0;

		size_t e =  egd.size();
		
		for (size_t i = 0; i < e; i++)
		{
			totalegd += (i+1)*egd[i];
		}
		file << "# d_medio = " << totalegd << "\n";

		for (size_t i = 0; i < e; i++)
		{
			file << i << " " << egd[i] << "\n"; // Print each grade number
		}



		file.close();
	}
};