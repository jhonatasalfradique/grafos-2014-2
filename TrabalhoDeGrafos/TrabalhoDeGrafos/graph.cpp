#include "stdafx.h"
#include <iostream>
#include <fstream>
#include <string>
#include <deque>
#include <list>
#include <tuple>
#include <vector>
using namespace std;

class Graph
{
	public:
	
	int n; //vertex number
	int m; //edge number
	vector<deque<int>> db; // list
	vector<vector<int>> db1;//matrix
	Graph::Graph(string filename,int t)
	{
		m = 0;
		
		cout << "Filename: " +  filename << endl;
		std::ifstream infile(filename);		//argumento de entrada nome do arquivo
		infile >> n;//get N from first line of file
		cout << "File loading" ;
		if (t == 2){//matrix
			vector<vector<int>> data(n, vector<int> (n+1,0)); // vector square matrix filled with 0 (extra slot for number of neighbors)
			// Begin reading your stream here
			int i, j; //vertex i and j from the graph
			while (infile >> i >> j){ // load pair of data in each variable
				data[i - 1][j - 1] = 1; // vertex i receive j as neighboor
				data[j - 1][i - 1] = 1; // vertex j receive i as neighboor
				m++; // each line add 1 edge
				data[i - 1][n] = data[i - 1][n] + 1;
				data[j - 1][n] = data[j - 1][n] + 1;//Grade + 1
				}
			db1 = data;
			}
		else {//lista de adjacencia
			db = vector<deque<int>> (n, deque<int>(1,0)); //Deck de arestas de adjacencia (last entry number of neighbors)

			// Begin reading your stream here
			int i, j; //vertex i and j from the graph
			while (infile >> i >> j) // load pair of data in each variable
			{	
				if (m % 100000 == 0){ cout << "."; }
				db[i - 1].back() = 1 + db[i - 1].back();//Grade + 1
				db[j - 1].back() = 1 + db[j - 1].back();//Grade + 1
				m++; // each line add 1 edge
				db[i - 1].push_front(j); // vertex i receive j as neighboor
				db[j - 1].push_front(i); // vertex j receive i as neighboor
			}
			cout << "Load Completed" << endl;
			//db = data;
		}
	
	}
	

	void Output(string s)
	{
		cout << "output started" << endl;
		ofstream file; // output file
		file.open(s + "_output.txt");

		file << "# n = " << n << "\n";
		file << "# m = " << m << "\n";
		double d_medio = (double) (2 * m) / (n);// grau medio = 2E/V (E aresta e V Vertice)
		file << "# d_medio = " <<  d_medio << "\n";
		cout  << "# n,m = " <<n << ","<< m << endl;

		deque<double> egd(1,(double) 0.0);// empiric grade distribution
		
	
			cout << "Math Progress ";

			for (int i = 0; i < n; i++)//for each (deque<int> di in db)
			{
				int grade = db[i].back();//Grade of vertex
				if (grade > (int)egd.size())
				{
					if (grade < (int)egd.max_size())// check for memory leak
					{
						egd.resize(grade, (double) 0.0);
					}
					else cout << "Error output stack overflow.\n";
				}
				if (grade>0)
				{
					egd[grade - 1] = egd[grade - 1] + 1;
				} //f(d) = n(d)/n
			}
	
		for (size_t i = 0; i < egd.size(); i++)
		{
			if (i % 100000 == 0){cout << "!"; }
			file << i+1 << " " << (double) (egd[i] / n) << "\n"; // Print each grade number
		}
		cout << endl;
		file.close();
		cout << "output end" << endl;
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
	vector<dlist> remove(vector<dlist> a, int v)
	{ 
		
		a[v - 1].next = a[v].next;
		if (v < (int) a.size() - 1) { a[v + 1].prev = a[v].prev; }
		a[v].vertex = 0;
		if (a[v].prev->vertex == -1) { a[0].next = a[v].next; }
		return a;
	};


	vector<dlist> chainstart(int k)
	{
	
		vector<dlist> vlist(k+1); // node 0
		
		for (int i = 0; i < k ; i++)// start list to check who was not inspected, first slot for reference where it start
		{
			dlist a;
			a.vertex = i+1;
			a.prev = &vlist[i];
			a.next = &vlist[0]; //make this link point to the "nowhere"
			//vlist.push_back(a);
			vlist[i+1] = a;
			vlist[i].next = &vlist[i+1]; //make previous link point to the this
			
		}
		vlist[0].vertex = -1;
		vlist[0].prev = &vlist[0];// first node point to itself
		
//		for each (dlist k in vlist) {
//			cout << "vertex " << k.vertex << " ";
//			if (k.prev != nullptr) { cout << "prev " << k.prev->vertex << " "; }
//			if (k.next != nullptr) { cout << "next " << k.next->vertex << endl; }else { cout << endl; }		}
		return vlist;
	}

	void printBFS(string s, int v)
	{
		ofstream file; // output file
		file.open(s + "(" + to_string(v) +")" + "_BFS.txt");
		cout << "file opened" << endl;
	
		auto ak = BFS(chainstart(n), v);
		vector<int> k1 = get<1>(ak);
		vector<int> k2 = get<2>(ak);

	
		for (int i = 1; i < (int) k1.size(); i++) //eliminate first row of counting stats
		{
			
			file << "vertice " << i << " discovered by "  << k1[i] << " at level " << k2[i] << endl;
		}
		file.close();
		cout << "file closed"; 
	}
	void printDFS(string s,int v)
	{
		ofstream file; // output file
		file.open(s + "("+ to_string(v) + ")"+ "_DFS.txt");
		cout << "file opened" << endl;
		auto ak = BFS(chainstart(n), v);
		vector<int> k1 = get<1>(ak);
		vector<int> k2 = get<2>(ak);


		for (int i = 1; i < (int)k1.size(); i++) //eliminate first row of counting stats
		{

			file << "vertice " << i << " discovered by " << k1[i] << " at level " << k2[i] << endl;
		}
		file.close();
		cout << "file closed";
	}
	void printrBFS(string s)
	{
		ofstream file; // output file
		file.open(s + "_rBFS.txt");
		deque<deque<int>> k = rBFS(chainstart(n));
		for (int t = 0; t < (int)k.size(); t++)  // Sorting K based on size stored in k[][0]
		{
			int i = t;
			while (i < (int) k.size()-1)
			{
				int u;
				if (k[i][0] > k[i + 1][0])
				{
					u = k[i][0]; 
					k[i][0] = k[i + 1][0];
					k[i + 1][0] = u;
				}
				i++;
			}
			
		}

		for (int t = 0; t < (int)k.size(); t++)//for each(deque<int> a in k) 
		{
			file << "size :" << k[t].front() << " components -";;
			for (int kt = 1; kt < (int)k[t].size(); kt++)//for each(int p in k[t])
			{ file << ">" << k[t][kt]; }
			file << endl;
		}
		file.close();
	}
	void printrDFS(string s)
	{
		ofstream file; // output file
		file.open(s + "_rDFS.txt");
		deque<deque<int>> k = rBFS(chainstart(n));
		for (int t = 0; t < (int)k.size(); t++)  // Sorting K based on size stored in k[][0]
		{
			int i = t;
			while (i < (int)k.size() - 1)
			{
				int u;
				if (k[i][0] > k[i + 1][0])
				{
					u = k[i][0];
					k[i][0] = k[i + 1][0];
					k[i + 1][0] = u;
				}
				i++;
			}

		}

		for (int t = 0; t < (int)k.size(); t++)//for each(deque<int> a in k) 
		{
			file << "size :" << k[t].front() << " components -";;
			for (int kt = 1; kt < (int)k[t].size(); kt++)//for each(int p in k[t])
			{
				file << ">" << k[t][kt];
			}
			file << endl;
		}
		file.close();
	}
	tuple<vector<dlist>, vector<int>, vector<int>, deque<int>> BFS(vector<dlist> vlist, int v) // This function is based on List of Neighbors
	{//usar vlist para apenas carregar os vertices desconhecidos e economizar iteracoes e espaco
		
			
			deque<int> list;
//			deque<tuple<int, int>> marker(n + 1, make_tuple(0, -1)); // mark if U has been red before (0 = not marked, -1 = origin , number = parent) (extra slot at the start to show how many were discovered on this BFS)
			vector<int> marker1(n + 1, 0); // mark if U has been red before (0 = not marked, -1 = origin , number = parent) (extra slot at the start to show how many were discovered on this BFS)
			vector<int> marker2(n + 1, -1); // mark if U has been red before (0 = not marked, -1 = origin , number = parent) (extra slot at the start to show how many were discovered on this BFS)

			deque<int> fifo;						// 2nd field of tuple means the tree level( 0 = start )
			cout << "BFS start" << endl << "progress " << endl ;
			//marker[v].swap(make_tuple(-1, 0));
			marker1[v] = -1;
			marker2[v] = 0;

			
			
			//marker[0].swap(make_tuple(1, 0)); //count +1
			list.push_back(1);//count +1
			vlist = remove(vlist,v);//remove V from undiscovered list
			fifo.push_back(v);
			list.push_back(v);// v added to the return list

			while (!fifo.empty())
			{
				int u = fifo.front(); // pick and erase U from list
				fifo.pop_front();
				int z = (int) db[u - 1].size();
				if (u % 1000 == 0) { cout << "|"; }
				for (int k = 0; k < z - 1 ; k++)
				{	
					int w = db[u - 1][k];
					if (marker1[w] == 0)//(get<0>(marker[w]) == 0)
					{
												
						//marker[w].swap(make_tuple(u, 1 + get<1>(marker[u]))); // u is w parent on the bfs tree
						marker1[w] = u;// u is w parent on the bfs tree
						marker2[w]= 1 + marker2[u]; // u is w parent on the bfs tree
						
						//get<0>(marker[0]) = get<0>(marker[0]) + 1; // 1 more vertex read
						list.front() = list.front() + 1; // 1 more vertex read
						fifo.push_back(w);// w added to the list
						list.push_back(w);// w added to the return list
						vlist = remove(vlist,w);//remove W from undiscovered list


					}
				}
			}

			tuple<vector<dlist>, vector<int>, vector<int>, deque<int>>  temp = make_tuple(vlist, marker1, marker2, list);
			return temp;
		}
	tuple<vector<dlist>, vector<int>, vector<int>, deque<int>> DFS(vector<dlist> vlist, int v) // This function is based on List of Neighbors
	{//usar vlist para apenas carregar os vertices desconhecidos e economizar iteracoes e espaco


		deque<int> list;
		//			deque<tuple<int, int>> marker(n + 1, make_tuple(0, -1)); // mark if U has been red before (0 = not marked, -1 = origin , number = parent) (extra slot at the start to show how many were discovered on this BFS)
		vector<int> marker1(n + 1, 0); // mark if U has been red before (0 = not marked, -1 = origin , number = parent) (extra slot at the start to show how many were discovered on this BFS)
		vector<int> marker2(n + 1, -1); // mark if U has been red before (0 = not marked, -1 = origin , number = parent) (extra slot at the start to show how many were discovered on this BFS)

		deque<int> filo;						// 2nd field of tuple means the tree level( 0 = start )
		cout << "DFS start" << endl << "progress " << endl;
		//marker[v].swap(make_tuple(-1, 0));
		marker1[v] = -1;
		marker2[v] = 0;



		//marker[0].swap(make_tuple(1, 0)); //count +1
		list.push_back(1);//count +1
		vlist = remove(vlist, v);//remove V from undiscovered list
		filo.push_back(v);
		list.push_back(v);// v added to the return list

		while (!filo.empty())
		{

			int u = filo.back(); // pick and erase U from list
			filo.pop_back();
			int z = (int)db[u - 1].size();
			if (u % 1000 == 0) { cout << "|"; }
			for (int k = 0; k < z - 1; k++)
			{
				int w = db[u - 1][k];
				if (marker1[w] == 0)//(get<0>(marker[w]) == 0)
				{

					//marker[w].swap(make_tuple(u, 1 + get<1>(marker[u]))); // u is w parent on the bfs tree
					marker1[w] = u;// u is w parent on the bfs tree
					marker2[w] = 1 + marker2[u]; // u is w parent on the bfs tree

					//get<0>(marker[0]) = get<0>(marker[0]) + 1; // 1 more vertex read
					list.front() = list.front() + 1; // 1 more vertex read
					filo.push_back(w);// w added to the list
					list.push_back(w);// w added to the return list
					vlist = remove(vlist, w);//remove W from undiscovered list


				}
			}
		}

		tuple<vector<dlist>, vector<int>, vector<int>, deque<int>>  temp = make_tuple(vlist, marker1, marker2, list);
		return temp;
	}
	deque<deque<int>> rBFS(vector<dlist> vlist)
	{

		deque<deque<int>> list(0);
		while (vlist[0].next->vertex != 0)
		{ 
		
			tuple<vector<dlist>,  vector<int>, vector<int>, deque<int>> chest = BFS(vlist, vlist[0].next->vertex); // run BFS on the first vertex
			vlist = get<0>(chest); // retrieve list to save up iterations
			list.push_back(get<3>(chest)); // results
		
		
		}
		return list;
	}
	deque<deque<int>> rDFS(vector<dlist> vlist)
	{

		deque<deque<int>> list(0);
		while (vlist[0].next->vertex != 0)
		{

			tuple<vector<dlist>, vector<int> ,vector<int>, deque<int>> chest = DFS(vlist, vlist[0].next->vertex); // run BFS on the first vertex
			vlist = get<0>(chest); // retrieve list to save up iterations
			list.push_back(get<3>(chest)); // results


		}
		return list;
	}
};