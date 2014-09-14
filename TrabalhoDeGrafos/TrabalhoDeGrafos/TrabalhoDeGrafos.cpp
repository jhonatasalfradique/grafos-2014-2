// TrabalhoDeGrafos.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "graph.cpp"
#include "string"





int _tmain(int argc, _TCHAR* argv[])
{//Limpar e enviar para graph mais tarde
	
	Graph *g;
	int b;
	string filename;
	cout << "Enter file name" << endl;
	cin >> filename;
	cout << "Press 2 for matrix or any number for list" << endl;
	cin >> b;
	g = new Graph(filename , b);// (file name, type of data)
	g.Output();

	
		 
	
	return 0;
}

