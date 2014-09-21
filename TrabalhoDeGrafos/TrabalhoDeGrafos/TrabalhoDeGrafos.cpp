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
	cout << "Enter file name without extension" << endl;
	cin >> filename;

	cout << "Press 2 for matrix or any number for list" << endl;
	cin >> b;
	g = new Graph(filename + ".txt" , b);// (file name, type of data)
	g->Output();
	cout << "Press 1 for BFS / 2 for print / 3 BFS print / 4 rBFS / 5 DFS" << endl;
	cin >> c;
	
	if (c == 1) {
		int bc;
		cout << "Choose the vertex to start BFS" << endl;
		cin >> bc;
		deque<tuple<int, int>> temp2(0);
		for (int i = 0; i < g->n + 1; i++)
		{
			temp2.push_back(get<1>(g->BFS(g->chainstart(g->n), bc))[i]);//grabs structure to preview
		}
		for each(tuple<int, int> a in temp2)
		{
			cout << get<0>(a) << " at lvl " << get<1>(a) << endl;
		} 
	}
	if (c == 2) { for each (deque<int> a in g->db) { a.pop_back(); for each (int i in a){ cout << i << " "; } cout << endl; } }
	if (c == 3)	{ time_t timev = time(0); g->printBFS(filename); cout << "tempo de exec " << timev - time(0) ; }
	if (c == 4) {g->printrBFS(filename);}
	if (c == 5) { time_t timev = time(0); g->printDFS(filename); cout << "tempo de exec " << timev - time(0); }
		 
	delete g;
	return 0;
}

