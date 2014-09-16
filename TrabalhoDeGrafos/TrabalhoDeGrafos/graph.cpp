//It's the Graph Class


#include "stdafx.h"
#include <iostream>
#include <fstream>
#include <string>
#include <deque>
using namespace std;

class Graph
{
	public:
	
	int n; //vertex number
	int m; //edge number
	deque<deque<int>> db; // graph
	
	Graph::Graph(string filename,int t)
	{
		m = 0;

		cout << "Filename: " +  filename;
		std::ifstream infile(filename);		//argumento de entrada nome do arquivo
		infile >> n;//get N from first line of file
		cout << "File loaded.\n";
		if (t == 2){//matrix
			cout << "Deque before\n";
			deque<deque<int>> data(n, deque<int> (n+1,0)); // deque square matrix filled with 0 (extra slot for number of neighbors)
			cout << "Deque\n";
			// Begin reading your stream here
			int i, j; //vertex i and j from the graph
			while (infile >> i >> j){ // load pair of data in each variable
				cout << "While\n";
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
				cout << "While\n";
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
		file << "# m = " << m << "\n";
		deque<double> egd;// empiric grade distribution
		cout << "Output()";
		// grau medio = 2E/V (E aresta e V Vertice)
		for each (deque<int> di in db)
		{
			cout << "Output() for each";
			int grade = di.back();//Grade of vertex
			if (grade > (int) egd.size()) 
				{
				if (grade < (int) egd.max_size()) egd.resize(grade, 0); // check for memory leak
				else cout << "Error output stack overflow.\n";
				}
		//	egd[grade] += egd[grade]/n; //f(d) = n(d)/n
			cout << "Output() end";
		}
		double totalegd = 0;

		size_t e =  egd.size();
		cout << "Output()3";
		for (size_t i = 0; i < e; i++)
		{
			totalegd += (i+1)*egd[i];
		}
		double d_medio = (2*m)/(n);
		file << "# d_medio = " << d_medio << "\n";
		cout << "Output()4";
		for (size_t i = 0; i < e; i++)
		{
			file << i << " " << egd[i] << "\n"; // Print each grade number
		}



		file.close();
	}
};