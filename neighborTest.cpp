#include <iostream>
#include <fstream>
#include <vector>
#include "TSPAlgorithms.h"
#include "TSPNeighbor.cpp"

using namespace std;

int main() {
    ifstream infile("size100.graph");
    if (!infile) {
        cerr << "Error: Unable to open input file." << endl;
        return 1;
    }

    // Read the graph from the input file
    int numNodes;
    infile >> numNodes;
    vector<vector<int>> graph(numNodes, vector<int>(numNodes));
    for (int i = 0; i < numNodes; ++i) {
        for (int j = 0; j < numNodes; ++j) {
            infile >> graph[i][j];
        }
    }

    cout << "Adjacency matrix read successfully!" << endl;

    // Choose a starting city
    int startCity = 0;

    // Solve the TSP using the neighbor search algorithm
    int minCost = tspNeighbor(graph, startCity);

    // Output the minimum cost
    cout << "Minimum cost using neighbor search: " << minCost << endl;

    return 0;
}


