#include <iostream>
#include <vector>
#include <algorithm>
#include "TSPAlgorithms.h" // Include the header file containing the genetic algorithm

using namespace std;

vector<vector<int>> readAdjacencyMatrix(const string& filename, int& numNodes) {
    ifstream file(filename);
    if (!file.is_open()) {
        cerr << "Error: Unable to open file " << filename << endl;
        exit(EXIT_FAILURE);
    }

    vector<vector<int>> adjacencyList;

    string line;
    while (getline(file, line)) {
        if (line.empty()) continue; // Skip empty lines
        if (line == "0endl") break; // End of adjacency list marker

        istringstream lineStream(line);
        vector<int> neighbors;
        int value;
        while (lineStream >> value) {
            neighbors.push_back(value);
        }
        adjacencyList.push_back(neighbors);
        numNodes++;
    }

    return adjacencyList;
}


int main() {
    string input;
    vector<vector<int>> graph;
    bool bruteForce = false;
    int numNodes, startCity, minCostBrute, minCost, minCostAll;
    numNodes = 0;

    cout << "Include the slow brute force algorithm? (y/n): ";
    cin >> input;

    if (input == "y") {
        bruteForce = true;
    }

    while (true) {
        numNodes = 0;
        cout << "Would you like to generate a random graph? (y/n): ";
        cin >> input;

        if (input == "y") {
            cout << "Enter the number of nodes: ";
            cin >> numNodes;

            graph = generateMatrix(numNodes);

            for(int i = 0; i < numNodes; i++){
                for(int j = 0; j < numNodes; j++){
                    cout << graph[i][j] << " ";
                }

                cout << endl;
            }
        } else if (input == "n") {
            graph = readAdjacencyMatrix("size100.graph", numNodes);
            cout << numNodes << endl;
        } else {
            cout << "Invalid input. Please try again." << endl;
            graph = generateMatrix(numNodes);
            return 0;
        }

        startCity = 0;

        // Perform TSP using the genetic algorithm
        TSPGenetic geneticAlgorithm(numNodes);
        individual geneticResult = geneticAlgorithm.TSPUtil(graph);;
        minCost = geneticResult.fitness;

        if (bruteForce) {
            minCostBrute = tspBrute(graph, startCity);
            cout << "Minimum cost using brute force: " << minCostBrute << endl;
        }

        // Output the minimum cost using the genetic algorithm
        cout << "Minimum cost using genetic algorithm: " << minCost << endl;

        // Perform TSP using the nearest neighbor algorithm
        minCostAll = tspNeighbor(graph, startCity, numNodes);
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
