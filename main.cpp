#include <iostream>
#include <vector>
#include <algorithm>
#include "TSPAlgorithms.h" // Include the header file containing the genetic algorithm

using namespace std;

vector<vector<int>> readAdjacencyMatrix(const string& input) {
    istringstream iss(input);
    vector<vector<int>> adjacencyMatrix;

    string line;
    while (getline(iss, line)) {
        istringstream lineStream(line);
        vector<int> row;
        int value;
        while (lineStream >> value) {
            row.push_back(value);
        }
        adjacencyMatrix.push_back(row);
    }

    return adjacencyMatrix;
}

int main() {
    string input;
    vector<vector<int>> graph;
    bool bruteForce = false;
    int numNodes, startCity, minCostBrute, minCost, minCostAll;

    cout << "Include the slow brute force algorithm? (y/n): ";
    cin >> input;

    if (input == "y") {
        bruteForce = true;
    }

    while (true) {
        cout << "Would you like to generate a random graph? (y/n): ";
        cin >> input;

        if (input == "y") {
            cout << "Enter the number of nodes: ";
            cin >> numNodes;

            graph = generateMatrix(numNodes);
        } else if (input == "n") {
            graph = readAdjacencyMatrix("size100.graph");
        } else {
            cout << "Invalid input. Please try again." << endl;
            graph = generateMatrix(numNodes);
            return 0;
        }


        startCity = 0;

        // Perform TSP using the genetic algorithm
        individual geneticResult = TSPUtil(graph);
        minCost = geneticResult.fitness;

        if (bruteForce) {
            minCostBrute = tspBrute(graph, startCity);
            cout << "Minimum cost using brute force: " << minCostBrute << endl;
        }

        // Output the minimum cost using the genetic algorithm
        cout << "Minimum cost using genetic algorithm: " << minCost << endl;

        // Perform TSP using the nearest neighbor algorithm
        minCostAll = tspNeighbor(graph, startCity);
        cout << "Minimum cost using nearest neighbor: " << minCostAll << endl;

        cout << "Would you like to continue? (y/n): ";
        cin >> input;

        if (input == "n") {
            break;
        } else {
            cout << endl;
        }
    }

    return 0;
}
