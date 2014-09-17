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
	if (c == 1) { for each(int a in g->BFS(g->db,1)){ cout << a << " "; } }
	if (c == 2) { for each (deque<int> a in g->db) { a.pop_back(); for each (int i in a){ cout << i << " "; } cout << endl; } }

		 
	
	return 0;
}

