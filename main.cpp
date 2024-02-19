#include <iostream>
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

#include <vector>
#include <iostream>

using namespace std;

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
        } 
        
        else if (input == "n") {
            cout << "Enter the number of nodes in the graph: ";
            cin >> numNodes;
            graph = readAdjacencyMatrix("g15000.graph", numNodes);
            graph = makeSymmetric(graph);
        } 
        
        else {
            cout << "Invalid input. Please try again." << endl;
            graph = generateMatrix(numNodes);
            return 0;
        }

        startCity = 0;

        auto startGenetic = chrono::high_resolution_clock::now(); // Start the timer for genetic algorithm

        // Perform TSP using the genetic algorithm
        // TSPGenetic geneticAlgorithm(numNodes);
        // individual geneticResult = geneticAlgorithm.TSPUtil(graph);
        // minCost = geneticResult.fitness;

        // auto stopGenetic = chrono::high_resolution_clock::now(); // Stop the timer for genetic algorithm
        // auto durationGenetic = chrono::duration_cast<chrono::milliseconds>(stopGenetic - startGenetic); // Calculate the duration for genetic algorithm

        if (bruteForce) {
            auto startBrute = chrono::high_resolution_clock::now(); // Start the timer for brute force algorithm
            minCostBrute = tspBrute(graph, startCity);
            auto stopBrute = chrono::high_resolution_clock::now(); // Stop the timer for brute force algorithm
            auto durationBrute = chrono::duration_cast<chrono::milliseconds>(stopBrute - startBrute); // Calculate the duration for brute force algorithm
            cout << "Minimum cost using brute force: " << minCostBrute << " (Time: " << durationBrute.count() << " ms)" << endl;
        }

        // cout << "Minimum cost using genetic algorithm: " << minCost << " (Time: " << durationGenetic.count() << " ms)" << endl;

        auto startNN = chrono::high_resolution_clock::now(); // Start the timer for nearest neighbor algorithm
        individual nnResult = tspNeighborAll(graph, startCity, numNodes);
        // Perform TSP using the nearest neighbor algorithm
        minCostAll = nnResult.fitness;

        auto stopNN = chrono::high_resolution_clock::now(); // Stop the timer for nearest neighbor algorithm
        auto durationNN = chrono::duration_cast<chrono::milliseconds>(stopNN - startNN); // Calculate the duration for nearest neighbor algorithm

        cout << "Minimum cost using nearest neighbor: " << minCostAll << " (Time: " << durationNN.count() << " ms)" << endl;

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
