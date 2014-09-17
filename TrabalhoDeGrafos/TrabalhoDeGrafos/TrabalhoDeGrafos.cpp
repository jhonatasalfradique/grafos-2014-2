// TrabalhoDeGrafos.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "graph.cpp"
#include "string"





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
	if (c == 1) { for each(tuple<int, int> a in g->BFS(g->db, 1)){ cout << get<0>(a) << " at lvl " << get<1>(a) << endl; } }
	if (c == 2) { for each (deque<int> a in g->db) { a.pop_back(); for each (int i in a){ cout << i << " "; } cout << endl; } }
	if (c == 3)
	{
		ofstream file; // output file
		file.open("BFS.txt");
		file << "Vertice pai e Nivel para cada vertice";

		for each(tuple<int, int> a in g->BFS(g->db, 1).pop_front())//eliminate first row of counting stats
		{
			file << get<0>(a) << "  " << get<1>(a) << endl;
		}
		file.close();
	}
		 
	
	return 0;
}

