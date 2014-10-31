/* 
 * File:   Graph.cpp
 * Author: jhonatas
 * 
 * Created on October 18, 2014, 5:29 PM
 */

//#include "Graph.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <ctime>
#include <list>
#include <climits>
#include <cfloat>



using namespace std;

/**
 *This class represents a graph
 */
class Graph {
    int n; // number of vertex
    int type; // if 0, list, if 1, it's matrix
    int graphType; // if 0, graphs without weight, 1 weighted Graph
    vector< vector <int> > graphList;
    vector< vector <bool> > graphMatrix;
    vector< vector< pair<int, double> > > graphWeight; // 1,(2, weight)
    bool negativeGraph; //If Graph has negative weight true, else false.
public:

    /**
     * This is the constructor of the Graph Class.
     * @param filename = Name of text file that represents the class
     * @param StructureType = 0 for List, 1 for Matrix
     * @param graphType = 0, for undirectional graphs without weight, 1 weighted Graph 
     */
    Graph(string filename, int StructureType, int graphType = 0) {

        this->negativeGraph = false;//default
        this->type = StructureType;
        std::ifstream myfile(filename.c_str());
        this->graphType = graphType;
        if (myfile.is_open()) {
            myfile >> n;

        } else {

            cout << "Error open file" << endl;
        }

        //list
        if (this->type == 0 && graphType == 0) {

            vector< vector<int> > g(this->n, vector<int>());
            int a, b;

            while (myfile >> a >> b) {

                g[a].push_back(b);

            }
            this->graphList = g;
            cout << "Graph Load (List Structure)" << endl;
        } else if (this->type == 1 && graphType == 0) {

            vector < vector<bool> > g(this->n, vector<bool>(this->n, false));

            int a, b;
            while (myfile >> a >> b) {
                g[a][b] = true;
            }


            this->graphMatrix = g;
            cout << "Graph load (Matrix Structure)" << endl;
        } else if (this->type == 0 && graphType == 1) {

            //vector< pair<pair<int, int>, double > > g(this->n);
            
            this->graphWeight = vector< vector< pair<int, double> > >(this->n);
            int a, b;
            double w;

            while (myfile >> a >> b >> w) {

                if(w < 0){
                    cout << w << endl;
                    this->negativeGraph = true;
                }
                
                pair<int, double> p(b, w);

                  //cout << a << "  " << b << "  " << w << endl;
                this->graphWeight[a].push_back(p);


            }

        }



    }

    /**
     * This the Breadth First Search algorithm for graphs
     * @param root = vertex where start the BFS
     */
    void BFS(int root) {

        std::clock_t start;
        start = std::clock();
        vector<int> Q;
        vector<bool> explored(this->n, false);

        explored[root] = true;
        Q.push_back(root);

        cout << "Breadth First Search starting from vertex ";
        cout << root << " : " << endl;
        while (!Q.empty()) {
            int v;
            v = Q.back();
            Q.pop_back();
            for (int i = 0; i < this->graphList[v].size(); i++) {

                if (explored[this->graphList[v][i]]) {

                    explored[this->graphList[v][i]] = true;
                    Q.push_back(this->graphList[v][i]);
                }
            }

        }

        std::cout << "Time: BFS " << (std::clock() - start) / (double) (CLOCKS_PER_SEC / 1000) << " ms" << std::endl;
        cout << "End BFS " << endl;


        explored.clear();
    }

    /**
     *  This the Depth first Search algorithm for graphs
     * 
     * @param root
     */
    void DFS(int root) {

        std::clock_t start;
        start = std::clock();
        vector<int> Q;
        vector<bool> explored(this->n, false);

        explored[root] = true;
        Q.push_back(root);

        cout << "Depth First Search starting from vertex ";
        cout << root << " : " << endl;
        while (!Q.empty()) {
            int v;
            v = Q.front();
            Q.pop_back();
            for (int i = 0; i < this->graphList[v].size(); i++) {

                if (explored[this->graphList[v][i]]) {

                    explored[this->graphList[v][i]] = true;
                    Q.push_back(this->graphList[v][i]);
                }
            }

        }

        std::cout << "Time: DFS " << (std::clock() - start) / (double) (CLOCKS_PER_SEC / 1000) << " ms" << std::endl;
        cout << "End DFS " << endl;


        explored.clear();


    }

    void printGraph() {

        if (this->type == 0 && this->graphType == 0) {

            for (int i = 0; i< this->n; i++) {

                for (int j = 0; j< this->graphList[i].size(); j++) {

                    cout << i << "  " << this->graphList[i][j] << endl;

                }

            }

        } else if (this->type == 1) {

            cout << "Not Avaiable" << endl;

        } else if (this->type == 0 && this->graphType == 1) {

            cout << "Print" << endl;
            for (int i = 0; i< this->n; i++) {
                for( int j= 0; j < this->graphWeight[i].size(); j++){
                    
                    cout << i << "  " << this->graphWeight[i][j].first <<
                            "  " << this->graphWeight[i][j].second << endl;
                            
                }
                
            }

        }

    }

    /**Return the weight of the edge of this two vertex
     * 
     * @param vertex1 vertex 1
     * @param vertex2 vertex 2
     * @return the weight of the edge of this two vertex
     */
    double weight(int vertex1, int vertex2) {

       // cout << "weight" << endl;

        if (this->graphType == 1) {

            for (int i = 0; i < this->graphWeight[vertex1].size(); i++) {

                if (this->graphWeight[vertex1][i].first == vertex2) {

                    return this->graphWeight[vertex1][i].second;
                }

            }
            
            return 0.0;


        }


    }
    
    void Dijkstra(int s){
        
        if(this->negativeGraph){
            
            cout << "Negative Graph" << endl;
            
            
        } else {
        double infinite = 9999;
        
        vector<double> dist = vector<double>(this->n);
        
        for(int k = 0; k < this->n; k++){
            
            dist[k] = infinite;
            cout << "d["<< k << "]=" << dist[k] << endl;
        }
        vector<int> S;
        
        dist[s] = 0.0;
        
        //S.push_back(s);
        int minimumDist = 0;
        double distance= 0.0;
        while( S.size() < this->n){
            
           
            for(int i= 0; i < dist.size(); i++){
                
                
                if(dist[i] <= distance){
                    cout << " Menor dist " << dist[i]  << " i=" << i<< endl;
                    distance = dist[i];
                    minimumDist = i;
                    
                }
                                
            }
            
            S.push_back(minimumDist);
            
            for(int j = 0; j < this->graphWeight[minimumDist].size(); j++){
                cout << "j= " << j << endl;
                cout << "minimumDist" << minimumDist << endl;
                    cout << "this->graphWeight[minimumDist][j].first" << this->graphWeight[minimumDist][j].first << endl;
                    cout << "dist[minimumDist] = " <<  dist[minimumDist] <<
                            "dist[this->graphWeight[minimumDist][j].first]" << dist[this->graphWeight[minimumDist][j].first] << "\n" <<
                            "this->weight(minimumDist, this->graphWeight[minimumDist][j].first)" << this->weight(minimumDist, this->graphWeight[minimumDist][j].first) << endl;
                if(dist[this->graphWeight[minimumDist][j].first] > (dist[minimumDist]
                        + this->weight(minimumDist, this->graphWeight[minimumDist][j].first))){
                    
                            
                    
                    dist[j] = (dist[minimumDist] + this->weight(minimumDist, this->graphWeight[minimumDist][j].first));
                    cout << "dist[j]= " << dist[j] << endl;
                }
                
            }
            
        }
        
        for(int i = 0; i< S.size(); i++){
            
            cout << S[i] << endl;
        }
        
    }
        
        
    
    }



};

