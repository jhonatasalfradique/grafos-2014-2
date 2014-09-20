// TrabalhoDeGrafos.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "graph.cpp"
#include "string"
#include <fstream>
#include <iostream>




int _tmain(int argc, _TCHAR* argv[])
{//Limpar e enviar para graph mais tarde
	
	Graph *g;
	int b,c;
	string filename = "graph.txt";
	//cout << "Enter file name" << endl;
	//cin >> filename;
	cout << "Press 2 for matrix or any number for list" << endl;
	cin >> b;
	g = new Graph(filename , b);// (file name, type of data)
	g->Output();
	cout << "Press 1 for BFS or 2 for print mode" << endl;
	cin >> c;
	
	if (c == 1) {
		tuple<deque<Graph::dlist>, deque<tuple<int, int>>> temp = g->BFS(g->chainstart(g->n), 1);
		deque<tuple<int, int>> temp2(0);
		for (int i = 0; i < g->n + 1; i++)
		{
			temp2.push_back(get<1>(temp)[i]);
		}
		for each(tuple<int, int> a in temp2)
		{
			cout << get<0>(a) << " at lvl " << get<1>(a) << endl;
		} 
	}
	if (c == 2) { for each (deque<int> a in g->db) { a.pop_back(); for each (int i in a){ cout << i << " "; } cout << endl; } }
	if (c == 3)
	{
		
		ofstream file; // output file
		file.open("BFS.txt");
		cout << "file opened" << endl;
		cout << "Vertice pai e Nivel para cada vertice" << endl;
		deque<tuple<int, int>> k = get<1>(g->BFS(g->chainstart(g->n), 1));
		k.pop_front();
		for each(tuple<int, int> a in k) //eliminate first row of counting stats
		{
			file << get<0>(a) << "  " << get<1>(a) << endl;
		}
		file.close();
		cout << "file closed";
	}
		 
	
	return 0;
}

