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
	cout << "Press 1 for BFS / 2 for print / 3 BFS print / 4 rBFS" << endl;
	cin >> c;
	
	if (c == 1) {
		
		deque<tuple<int, int>> temp2(0);
		for (int i = 0; i < g->n + 1; i++)
		{
			temp2.push_back(get<1>(g->BFS(g->chainstart(g->n), 1))[i]);//grabs structure to preview
		}
		for each(tuple<int, int> a in temp2)
		{
			cout << get<0>(a) << " at lvl " << get<1>(a) << endl;
		} 
	}
	if (c == 2) { for each (deque<int> a in g->db) { a.pop_back(); for each (int i in a){ cout << i << " "; } cout << endl; } }
	if (c == 3)	{g->printBFS("");	}
	if (c == 4) {g->printrBFS("");}
		 
	delete g;
	return 0;
}

