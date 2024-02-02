#include "TSPNeighbor.cpp"
#include "TSPBrute.cpp"
#include "randomMatrix.cpp"
#include "TSPHeuristics.cpp"
#include <iostream>
#include <vector>
#include <algorithm>

int main() {
    int numNodes;
    string input;

    while(true) {
        cout << "Enter the number of nodes: ";
        cin >> numNodes;

        if(numNodes > 11) {
            cout << "WARNING! This operation will take a large amount of time. Continue? (y/n): " << endl;
            cin >> input;

            if(input == "n") {
                break;
            }
        }

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
        int minCostSSSP = tspSSSP(graph);

        cout << "Minimum cost using neighbor search: " << minCost << endl;
        cout << "Minimum cost using brute force: " << minCostBrute << endl;
        cout << "Minimum cost using heuristics: " << minCostSSSP << endl;

        cout << "Would you like to continue? (y/n): ";

        cin >> input;

        if(input == "n") {
            break;
        }

        else {
            cout << endl;
        }
    }
    
    return 0;
}