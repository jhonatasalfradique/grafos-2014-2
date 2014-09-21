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
	deque<deque<int>> cgroup; // connect segment listed
	
	Graph::Graph(string filename,int t)
	{
		m = 0;
		cgroup = deque<deque<int>>(1, deque<int>(1, 0));

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
	
		struct dlist // double linked list
	{
		int vertex;
		dlist * prev = nullptr;
		dlist * next = nullptr;



		void remove()
		{

			prev->next = next;
			next->prev = prev; 
			vertex = 0;
		};

		
	};
	deque<dlist> remove(deque<dlist> a, int v)
	{ 
		a[v - 1].next = a[v].next;
		if (v < (int) a.size() - 1) { a[v + 1].prev = a[v].prev; }
		a[v].vertex = 0;
		if (a[v].prev->vertex == -1) { a[0].next = a[v].next; }
		return a;
	};


	deque<dlist> chainstart(int k)
	{
		dlist at0;
		at0.vertex = -1;
		deque<dlist> vlist(1,at0); // node 0

		for (int i = 0; i < k ; i++)// start list to check who was not inspected, first slot for reference where it start
		{
			dlist a;
			a.vertex = i+1;
			a.prev = &vlist[i];
			a.next = &vlist[0]; //make this link point to the "nowhere"
			vlist.push_back(a);
			vlist[i].next = &vlist[i+1]; //make previous link point to the this
			
		}
		vlist[0].prev = &vlist[0];// first node point to itself
		
//		for each (dlist k in vlist) {
//			cout << "vertex " << k.vertex << " ";
//			if (k.prev != nullptr) { cout << "prev " << k.prev->vertex << " "; }
//			if (k.next != nullptr) { cout << "next " << k.next->vertex << endl; }else { cout << endl; }		}
		return vlist;
	}

	void printBFS(string s)
	{
		ofstream file; // output file
		file.open(s + "BFS.txt");
		cout << "file opened" << endl;
		cout << "Vertice pai e Nivel para cada vertice" << endl;
		deque<tuple<int, int>> k = get<1>(BFS(chainstart(n), 1));
		k.pop_front();
		for each(tuple<int, int> a in k) //eliminate first row of counting stats
		{
			file << get<0>(a) << "  " << get<1>(a) << endl;
		}
		file.close();
		cout << "file closed"; 
	}

	void printrBFS(string s)
	{
		ofstream file; // output file
		file.open(s + "rBFS.txt");
		deque<deque<int>> k = rBFS(chainstart(n));
		for each(deque<int> a in k) 
		{
			for each(int p in a){ file << ">" <<p; }
			file << endl;
		}
		file.close();
	}

	tuple<deque<dlist>,deque<tuple<int, int>>,deque<int>> BFS(deque<dlist> vlist,int v) // This function is based on List of Neighbors
	{//usar vlist para apenas carregar os vertices desconhecidos e economizar iteracoes e espaco
		
			
			deque<int> list;
			deque<tuple<int, int>> marker(n + 1, make_tuple(0, -1)); // mark if U has been red before (0 = not marked, -1 = origin , number = parent) (extra slot at the start to show how many were discovered on this BFS)
			deque<int> fifo;						// 2nd field of tuple means the tree level( 0 = start )
			marker[v].swap(make_tuple(-1, 0));
			marker[0].swap(make_tuple(1, 0)); //count +1
			vlist = remove(vlist,v);//remove V from undiscovered list
			fifo.push_back(v);
			list.push_back(v);// v added to the return list

			while (!fifo.empty())
			{
								
				int u = fifo.front(); // pick and erase U from list
				fifo.pop_front();
				int z = (int) db[u - 1].size();
				for (int k = 0; k < z - 1 ; k++)
				{	
					int w = db[u - 1][k];
					if (get<0>(marker[w]) == 0)
					{
						
						marker[w].swap(make_tuple(u, 1 + get<1>(marker[u]))); // u is w parent on the bfs tree
						get<0>(marker[0]) = get<0>(marker[0]) + 1; // 1 more vertex read
						
						fifo.push_back(w);// w added to the list
						list.push_back(w);// w added to the return list
						vlist = remove(vlist,w);//remove W from undiscovered list
						cout << "marker " << w << endl;

					}
				}
			}

			tuple<deque<dlist>, deque<tuple<int, int>>,deque<int>>  temp = make_tuple(vlist, marker,list);
			return temp;
		}

	
	deque<deque<int>> rBFS(deque<dlist> vlist)
	{

		deque<deque<int>> list(0);
		while (vlist[0].next->vertex != 0)
		{ 
		
			tuple<deque<dlist>, deque<tuple<int, int>>,deque<int>> chest = BFS(vlist, vlist[0].next->vertex); // run BFS on the first vertex
			vlist = get<0>(chest); // retrieve list to save up iterations
			list.push_back(get<2>(chest)); // results
			for (int k = 0; k < n + 1 ; k++) {				cout << "vertex " << vlist[k].vertex  << " ";				if (vlist[k].prev != nullptr) { cout << "prev " << vlist[k].prev->vertex << " "; }				if (vlist[k].next != nullptr) { cout << "next " << vlist[k].next->vertex << endl; }				else { cout << endl; }			}

		}
		return list;
	}

};