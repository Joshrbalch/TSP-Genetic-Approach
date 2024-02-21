#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <chrono>
#include <sstream>
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
    }

    return adjacencyList;
}

vector<vector<int>> makeSymmetric(const vector<vector<int>>& halfAdjacencyMatrix) {
    int n = halfAdjacencyMatrix.size();
    vector<vector<int>> symmetricAdjacencyMatrix(n, vector<int>(n, 0));

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j <= i; ++j) {
            // Reflect the upper triangular part to the lower triangular part
            symmetricAdjacencyMatrix[i][j] = halfAdjacencyMatrix[i][j];
            symmetricAdjacencyMatrix[j][i] = halfAdjacencyMatrix[i][j];
        }
    }

    return symmetricAdjacencyMatrix;
}

int main() {
    ofstream outFile("results.txt"); // Open a file for writing results

    string input;
    vector<vector<int>> graph;
    bool bruteForce = true;
    int numNodes, startCity, minCostBrute, minCost, minCostAll;
    numNodes = 5;

    for (int i = 0; i < 30; ++i) { // Loop to run 30 times
        if(numNodes > 11) {
            bruteForce = false;
            numNodes += 100; // Increase number of nodes by 100 each iteration
        }
        else {
            numNodes++;
        }

        cout << "Generating graph with " << numNodes << " nodes..." << endl;
        graph = generateMatrix(numNodes);

        startCity = 0;

        auto startGenetic = chrono::high_resolution_clock::now(); // Start the timer for genetic algorithm
        TSPGenetic geneticAlgorithm(numNodes);
        individual geneticResult = geneticAlgorithm.TSPUtil(graph);
        minCost = geneticResult.fitness;
        auto stopGenetic = chrono::high_resolution_clock::now(); // Stop the timer for genetic algorithm
        auto durationGenetic = chrono::duration_cast<chrono::milliseconds>(stopGenetic - startGenetic); // Calculate the duration for genetic algorithm
        

        if (bruteForce) {
            auto startBrute = chrono::high_resolution_clock::now(); // Start the timer for brute force algorithm
            minCostBrute = tspBrute(graph, startCity);
            auto stopBrute = chrono::high_resolution_clock::now(); // Stop the timer for brute force algorithm
            auto durationBrute = chrono::duration_cast<chrono::milliseconds>(stopBrute - startBrute); // Calculate the duration for brute force algorithm
            cout << "Minimum cost using brute force: " << minCostBrute << " (Time: " << durationBrute.count() << " ms)" << endl;
            outFile << "Brute Force Algorithm: " << minCostBrute << " (Time: " << durationBrute.count() << " ms)\n";
        }

        auto startNN = chrono::high_resolution_clock::now(); // Start the timer for nearest neighbor algorithm
        minCostAll = tspNeighbor(graph, startCity, numNodes).fitness;
        auto stopNN = chrono::high_resolution_clock::now(); // Stop the timer for nearest neighbor algorithm
        auto durationNN = chrono::duration_cast<chrono::milliseconds>(stopNN - startNN); // Calculate the duration for nearest neighbor algorithm

        cout << "Minimum cost using genetic algorithm: " << minCost << " (Time: " << durationGenetic.count() << " ms)" << endl;
        cout << "Minimum cost using nearest neighbor: " << minCostAll << " (Time: " << durationNN.count() << " ms)" << endl;

        // Write results to the output file
        outFile << "Graph with " << numNodes << " nodes:\n";
        outFile << "Genetic Algorithm: " << minCost << " (Time: " << durationGenetic.count() << " ms)\n";
        outFile << "Nearest Neighbor Algorithm: " << minCostAll << " (Time: " << durationNN.count() << " ms)\n";
        outFile << endl;
    }

    outFile.close(); // Close the output file
    return 0;
}
