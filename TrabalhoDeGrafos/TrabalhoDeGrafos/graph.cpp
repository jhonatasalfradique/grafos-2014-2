//It's the Graph Class


#include "stdafx.h"
#include <iostream>
#include <fstream>
#include <string>
#include <deque>
#include <list>
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
				data[i - 1][n] ++;
				data[j - 1][n] ++;//Grade + 1
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
				data[j - 1].back() = 1 + data[j - 1].back();//Grade + 1
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
		double d_medio = (2 * m) / (n);// grau medio = 2E/V (E aresta e V Vertice)
		file << "# d_medio = " << d_medio << "\n";


		deque<double> egd(1,(double) 0.0);// empiric grade distribution
		
		for each (deque<int> di in db)
		{
			int grade = di.back();//Grade of vertex
			if (grade > (int) egd.size()) 
				{
				if (grade < (int)egd.max_size())// check for memory leak
				{
					egd.resize(grade, (double) 0.0);
				} 
				else cout << "Error output stack overflow.\n";
				}

			egd[grade - 1] = egd[grade - 1] + (double) 1/n; //f(d) = n(d)/n
		}
	
		for (size_t i = 0; i < egd.size(); i++)
		{
			file << i << " " << egd[i] << "\n"; // Print each grade number
		}

		file.close();
	}
	
	deque<int> BFS(list<int> li,int v) // This function is based on List of Neighbors
	{
		//std::list<int> unreachable(1,n+1);
		deque<int> marker(n+1,0); // mark if U has been red before (0 = not marked, -1 = origin , number = parent) (extra slot at the start to show how many were discovered on this BFS)
		deque<int> fifo;
		marker[v] = -1;
		marker[0] = 1; //count +1
		fifo.push_back(v);
		while (!(fifo.empty()))
		{
			int u = fifo.front(); // pick and erase U from list
			fifo.pop_front();
		//	unreachable.erase(u-1);
			for each (int w in db[u])// check all neighbors
			{
				if (marker[w] = 0)
				{
					marker[w] = u; // u is w parent on the bfs tree
					marker[0] = marker[0] + 1; // 1 more vertex read
					fifo.push_back(w);// w added to the list
					
					
				}
			}
		}
		return marker;
	}
};