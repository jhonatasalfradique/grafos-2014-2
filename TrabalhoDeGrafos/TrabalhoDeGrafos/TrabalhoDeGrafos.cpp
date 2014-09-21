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
	g->Output(filename);
	cout << "Press 1 for BFS / 2 for print / 3 BFS print / 4 rBFS / 5 DFS" << endl;
	cin >> c;
	
	if (c == 1) {
		int bc;
		cout << "Choose the vertex to start BFS" << endl;
		cin >> bc;
		deque<int> temp2(0);
		deque<int> temp3(0);
		for (int i = 0; i < g->n + 1; i++)
		{
			//temp2.push_back(get<1>(g->BFS(g->chainstart(g->n), bc))[i]);//grabs structure to preview
			//temp2.push_back(get<2>(g->BFS(g->chainstart(g->n), bc))[i]);//grabs structure to preview
		}
		
		//for (int i = 0; i < g->n + 1; i++)
		{
			//cout << temp2[i] << " at lvl " << temp3[i] << endl;
		}
		
	}
	if (c == 2) { for each (deque<int> a in g->db) { a.pop_back(); for each (int i in a){ cout << i << " "; } cout << endl; } }
	if (c == 3)	{ clock_t timev = clock(); g->printBFS(filename); cout << "tempo de exec " << (float)((timev - clock())/CLOCKS_PER_SEC ); }
	if (c == 4) {g->printrBFS(filename);}
	if (c == 5) { clock_t timev = clock(); g->printDFS(filename); cout << "tempo de exec " << (float)((timev - clock()) / CLOCKS_PER_SEC); }
		 
	delete g;
	return 0;
}

