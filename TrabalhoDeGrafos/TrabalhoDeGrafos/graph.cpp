//It's the Graph Class


#include "stdafx.h"
#include <iostream>
#include <fstream>
#include <string>
#include <deque>
#include <list>
#include <tuple>
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
		
		cout << "Filename: " +  filename << endl;
		std::ifstream infile(filename);		//argumento de entrada nome do arquivo
		infile >> n;//get N from first line of file
		cout << "File loaded." << endl;
		if (t == 2){//matrix
			deque<deque<int>> data(n, deque<int> (n+1,0)); // deque square matrix filled with 0 (extra slot for number of neighbors)
			// Begin reading your stream here
			int i, j; //vertex i and j from the graph
			while (infile >> i >> j){ // load pair of data in each variable
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
	
	deque<tuple<int,int>> BFS(deque<deque<int>> vect,int v) // This function is based on List of Neighbors
	{
		//std::list<int> unreachable(1,n+1);
		deque<tuple<int,int>> marker(n+1,(0,-1)); // mark if U has been red before (0 = not marked, -1 = origin , number = parent) (extra slot at the start to show how many were discovered on this BFS)
		deque<int> fifo;						// 2nd field of tuple means the tree level( 0 = start )
		marker[v].swap(-1,0);
		marker[0].swap(1,0); //count +1
		fifo.push_back(v);
		for each (deque<int> o in vect) // remove last collum of counting
		{
			o.pop_back();
		}
		while (!fifo.empty())
		{
		
			int u = fifo.front(); // pick and erase U from list
			fifo.pop_front();
			//	unreachable.erase(u-1);
			
			for each (int w in vect[u-1])
			{				
				if (get<0>(marker[w]) == 0)
				{
					marker[w].swap(u, 1 + get<1>(marker[u])); // u is w parent on the bfs tree
					get<0>(marker[0]) = get<0>(marker[0]) + 1; // 1 more vertex read
					fifo.push_back(w);// w added to the list
					
					
				}
			}
		}
		return marker;
	}

	deque<tuple<int, int>> DFS(deque<deque<int>> vect, int v) // This function is based on List of Neighbors
	{
		//std::list<int> unreachable(1,n+1);
		deque<tuple<int, int>> marker(n + 1, (0, -1)); // mark if U has been red before (0 = not marked, -1 = origin , number = parent) (extra slot at the start to show how many were discovered on this BFS)
		deque<int> filo;						// 2nd field of tuple means the tree level( 0 = start )
		marker[v].swap(-1, 0);
		marker[0].swap(1, 0); //count +1
		filo.push_back(v);
		for each (deque<int> o in vect) // remove last collum of counting
		{
			o.pop_back();
		}
		while (!filo.empty())
		{

			int u = filo.back(); // pick and erase U from list
			filo.pop_back();
			//	unreachable.erase(u-1);

			for each (int w in vect[u - 1])
			{
				if (get<0>(marker[w]) == 0)
				{
					marker[w].swap(u, 1 + get<1>(marker[u])); // u is w parent on the bfs tree
					get<0>(marker[0]) = get<0>(marker[0]) + 1; // 1 more vertex read
					fifo.push_back(w);// w added to the list


				}
			}
		}
		return marker;
	}

	

};