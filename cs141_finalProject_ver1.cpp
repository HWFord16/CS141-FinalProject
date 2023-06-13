/*
    Harrison Williams
    CS141-02-Spring23
    Professor Eldawy
    Final Project: Dijkstra's Algorithm
    06/12/23
    verison 1
*/

#include <iostream>
#include <cstdlib>
#include <vector>
#include <map>
#include <queue>
#include <set>
#include <limits>

using namespace std;

//function Prototypes
void DijkstraShortestPath(const map<int,vector<int>>&, const map<pair<int,int>,float>&, int*, float*);

//execution
//Ideally this program will have user prompts to create graph
//for demo Purposes, main() will have hard coded graph stored in maps
int main(){
    //Declare Variables
    map<int,vector<int>> E;     //Adjacency list representing Graph
    map<pair<int,int>,float> W; //Edge weight mapping G.E-->R
    int p[8];                   //shortest path topology (predecessor)
    float d[8];                 //shortest path distances to each vertice

    //Initialize Variables
    //Construct Graph
    E[0] = {1, 2, 4};
    E[1] = {2, 3, 5};
    E[2] = {0, 5};
    E[3] = {7};
    E[4] = {7};
    E[5] = {3};
    E[6] = {4,5};
    E[7] = {6};
    
    // Assignweights to edges
    W[make_pair(0, 1)] = 1.0;
    W[make_pair(0, 2)] = 8.0;
    W[make_pair(0, 4)] = 3.0;
    W[make_pair(1, 2)] = 8.0;
    W[make_pair(1, 3)] = 5.0;
    W[make_pair(1, 5)] = 1.0;
    W[make_pair(2, 0)] = 2.0;
    W[make_pair(2, 5)] = 8.0;
    W[make_pair(3, 7)] = 5.0;
    W[make_pair(4, 7)] = 9.0;
    W[make_pair(5, 3)] = 7.0;
    W[make_pair(6, 4)] = 5.0;
    W[make_pair(6, 5)] = 4.0;
    W[make_pair(7, 6)] = 8.0;
    
    //Process Inputs to Ouputs
    DijkstraShortestPath(E,W,p,d);

    //Display Outputs
    cout << "\n\nShortest Path\n-------------------" << endl;
    for (int i = 0; i < E.size(); i++) {
        cout << "Vertex " << i << ": ";
        if (p[i] != -1) {
            cout << p[i] << " -> ";
        }
        cout << i << " (Cost: " << d[i] << ")" << endl;
    }
    cout<<endl<<endl;

    //Exit Program
    return 0;
}

//Function Implementation
void DijkstraShortestPath(const map<int,vector<int>>& E , const map<pair<int,int>,float>& W, int* p, float* d){
    //Declare Variables
    int srcNode;        //starting Vertex
    priority_queue<pair<float, int>, vector<pair<float, int>>, greater<pair<float, int>>> priQue;
    set<int> visited;   //Set of visited nodes

    //Prompt User for starting Node
    cout<<"Enter Starting Vertex: ";
    cin >> srcNode;

    //Initialize Single-Source and Graph Nodes/Edges
    fill(p, p + E.size(), -1);
    fill(d, d + E.size(), numeric_limits<float>::max());
    d[srcNode] = 0;

    //Insert all vertices into Pri-Queue
    for (const auto& entry : E) {
        int vertex = entry.first;
        priQue.push(make_pair(d[vertex], vertex));
    }
    //priQue.push(make_pair(0, srcNode));

    //Iterate through Graph G to find shortest path
    while (!priQue.empty()) {
        //Extract from Pri-que
        pair<float, int> vertex = priQue.top(); 
        priQue.pop();
        int u = vertex.second;  //set u to vertex from pri-que
        visited.insert(u);      //insert into visited node set

        const vector<int>& neighbors = E.at(u);
        for (int v : neighbors) {
            pair<int, int> edge = make_pair(u, v);
            
            //check range of map and its edge
            if (W.find(edge) != W.end()) {
                float weight = W.at(edge);
                
                //Edge Relaxation
                if (visited.find(v) == visited.end() && d[u] + weight < d[v]) {
                    d[v] = d[u] + weight;
                    p[v] = u;
                    priQue.push(make_pair(d[v], v));
                }
            }
        }
    }
}