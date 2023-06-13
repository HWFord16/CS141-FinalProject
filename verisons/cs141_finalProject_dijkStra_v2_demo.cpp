/*
    Harrison Williams
    CS141-02-Spring23
    Professor Eldawy
    Final Project: Dijkstra's Algorithm
    06/12/23
    verison 2 (demo): hard coded graphs w/ entire path topology output per shortest path
*/

#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <vector>
#include <map>
#include <queue>
#include <set>
#include <limits>
#include <stack>

using namespace std;

//function Prototypes
void DijkstraShortestPath(const map<int,vector<int>>&, const map<pair<int,int>,float>&, int*, float*);
void PrintPath(int*, int);

//execution
//Ideally this program will have user prompts to create graph
//main() will have hard coded graph stored in maps for demo purposes
int main(){
    //Declare Variables
    map<int,vector<int>> E;     //Adjaceny list representing Graph
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
    
    // Assign weights to edges
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
    cout<<"\n\n*************************************************************\n"
        "Welcome to the Single Source All Destination Graph Program\n"
        "                 (Dijkstra's Algorithm)\n"
        "*************************************************************\n"<<endl;

    DijkstraShortestPath(E,W,p,d);  //function call to Dijkstras Algo

    //Display Outputs
    cout << "\n\nShortest Paths\n-------------------" << endl;
    cout << setw(18) << left << "Path to Vertex" << setw(10) << left << "Cost" << "Path Topology" << endl<<endl;
    for (int i = 0; i < E.size(); i++) {
        cout << setw(18) << left << i;
        
        if (p[i] != -1) {
            cout << setw(10) << left << d[i];
            PrintPath(p,i);
            cout<<endl;
        }
        else if(d[i] == 0) cout<< setw(10) <<left<< 0 << i << endl;
        else cout << setw(10) << left << "INF"<< "No path" << endl;
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

void PrintPath(int* p, int v) {
    stack<int> path;
    while (v != -1) {
        path.push(v);
        v = p[v];
    }

    while (!path.empty()) {
        cout << path.top();
        path.pop();
        if (!path.empty()) {
            cout << " -> ";
        }
    }
}