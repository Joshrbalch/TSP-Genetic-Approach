#include "TSPNeighbor.cpp"
#include "TSPBrute.cpp"
#include "randomMatrix.cpp"
#include <iostream>
#include <vector>
#include <algorithm>

int main() {

    cout << "Enter the number of nodes: ";
    int numNodes;
    cin >> numNodes;

    // Example usage
    // {
    //     {0, 10, 15, 20},
    //     {10, 0, 35, 25},
    //     {15, 35, 0, 30},
    //     {20, 25, 30, 0}
    // };
    
    vector<vector<int>> graph = generateMatrix(numNodes); 
    
    int startCity = 0;
    int minCost = tspNeighbor(graph, startCity);
    int minCostBrute = tspBrute(graph, startCity);
    
    cout << "Minimum cost using neighbor search: " << minCost << endl;
    cout << "Minimum cost using brute force: " << minCostBrute << endl;
    
    return 0;
}