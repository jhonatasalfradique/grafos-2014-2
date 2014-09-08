// TrabalhoDeGrafos.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "graph.cpp"

int _tmain(int argc, _TCHAR* argv[])
{
	
	Graph *a;
	a = new Graph();
	int ab = a->get_i();
	cout << ab;
	int b;
	cin >> b;
		 
	
	return 0;
}

