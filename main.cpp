#include "TSPAlgorithms.h"
#include <iostream>
#include <vector>
#include <algorithm>

// Example array for testing
        // {
        //     {0, 10, 15, 20},
        //     {10, 0, 35, 25},
        //     {15, 35, 0, 30},
        //     {20, 25, 30, 0}
        // };

using namespace std;

int main() {
    string input;
    bool bruteForce = false;
    int numNodes, startCity, minCostBrute, minCost, minCostSSSP;

    cout << "Include the slow brute force algorithm? (y/n): ";
    cin >> input;

    if(input == "y") {
        bruteForce = true;
    }

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

        vector<vector<int>> graph = generateMatrix(numNodes); 
        
        startCity = 0;

        if(bruteForce) {
            minCostBrute = tspBrute(graph, startCity);
        }

        minCost = tspNeighbor(graph, startCity);
        minCostSSSP = tspSSSP(graph);

        if(bruteForce) {
            cout << "Minimum cost using brute force: " << minCostBrute << endl;
        }

        cout << "Minimum cost using neighbor search: " << minCost << endl;
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