/* 
 * File:   main.cpp
 * Author: jhonatas
 *
 * Created on October 18, 2014, 5:21 PM
 */

#include "Graph.cpp"
#include <iostream>


using namespace std;

/*
 * 
 */
int main(int argc, char** argv) {

    
    cout << "inicio " << endl;
    Graph *graph = new Graph("graphtest.txt",0, 1);
    //graph->BFS(1);
    //graph->DFS(1);
    graph->printGraph();
    //cout << graph->weight(4,5) << endl; 
    graph->Dijkstra(1);
    
    
    return 0;
}

