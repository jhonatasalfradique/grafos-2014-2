// TrabalhoDeGrafos.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "graph.cpp"
#include "string"
#include "ctime"



int _tmain(int argc, _TCHAR* argv[])
{//Limpar e enviar para graph mais tarde
	
	Graph *g;
	int b,c;
	string filename;//= "graph.txt";
	cout << "Enter file name without extension: " ;
	cin >> filename;

	cout << "Press 2 for matrix or any number for list: ";
	cin >> b;
	g = new Graph(filename + ".txt" , b);// (file name, type of data)
	g->Output(filename);
	cout << "Press:\n1 for BFS(v) \n2 for DFS(v) \n3 show graph \n4 BFS print \n5 DFS \n6 rBFS \n7 rDFS" << endl;
	cin >> c;
	
	if (c == 1) {
		int bc;
		cout << "Choose Vertex to start: ";
		cin >> bc;
		clock_t timev = clock(); g->printBFS(filename, bc); cout << "tempo de exec " << (float)((timev - clock()) / CLOCKS_PER_SEC);
	}
	if (c == 2) {
		int bc;
		cout << "Choose Vertex to start: ";
		cin >> bc;
		clock_t timev = clock(); g->printDFS(filename, bc); cout << "tempo de exec " << (float)((timev - clock()) / CLOCKS_PER_SEC);
	}

	if (c == 3) { for each (deque<int> a in g->db) { a.pop_back(); for each (int i in a){ cout << i << " "; } cout << endl; } }
	if (c == 4)	{ clock_t timev = clock(); g->printBFS(filename, 1); cout << "tempo de exec " << (float)((timev - clock())/CLOCKS_PER_SEC ); }
	if (c == 5) { clock_t timev = clock(); g->printDFS(filename, 1); cout << "tempo de exec " << (float)((timev - clock()) / CLOCKS_PER_SEC); }
	if (c == 6) { g->printrBFS(filename); }
	if (c == 7) { g->printrDFS(filename); }

	delete g;
	return 0;
}

