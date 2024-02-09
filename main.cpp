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
    int numNodes, startCity, minCostBrute, minCost, minCostAll;

    cout << "Include the slow brute force algorithm? (y/n): ";
    cin >> input;

    if(input == "y") {
        bruteForce = true;
    }

    while(true) {
        cout << "Would you like to generate a random graph? (y/n): ";
        cin >> input;

        if(input == "y") {
            cout << "Enter the number of nodes: ";
            cin >> numNodes;

            vector<vector<int>> graph = generateMatrix(numNodes);
        }

        else if(input == "n") {
            fInput file("Graphs/Size100.graph");
            numNodes = file.numNodes;
            vector<vector<int>> graph = file.graph;
        }

        else {
            cout << "Invalid input. Please try again." << endl;
            continue;
        }

        vector<vector<int>> graph = generateMatrix(numNodes); 
        
        startCity = 0;

        if(bruteForce) {
            minCostBrute = tspBrute(graph, startCity);
        }

        minCost = tspNeighbor(graph, startCity);
        minCostAll = tspNeighborAll(graph, startCity);
        tspHeuristics tspH;
        tspH.run(graph, startCity);
        int minCostSSSP = tspH.getCost();

        if(bruteForce) {
            cout << "Minimum cost using brute force: " << minCostBrute << endl;
        }

        cout << "Minimum cost using neighbor search: " << minCost << endl;
        cout << "Minimum cost using neighbor search (all): " << minCostAll << endl;
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