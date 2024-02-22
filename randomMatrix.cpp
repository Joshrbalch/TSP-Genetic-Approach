#include <iostream>
#include <fstream>
#include <vector>
#include <random>

using namespace std;

vector<vector<int>> generateMatrix(int numNodes) {
    // Initialize a 2D vector with all elements set to 0
    const string filename = "graph.graph";
    vector<vector<int>> weightedMatrix(numNodes, vector<int>(numNodes, 0));

    // Use a random device and a Mersenne Twister engine for random number generation
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<int> distribution(1, 100);  // Adjust the range as needed
    int weight;

    // Generate random weights for the edges (symmetric)
    for (int i = 0; i < numNodes; ++i) {
        for (int j = i + 1; j < numNodes; ++j) {
            weight = distribution(gen);
            weightedMatrix[i][j] = weight;
            weightedMatrix[j][i] = weight;  // Set the symmetric element
        }
    }

    // Write the generated graph to the file
    ofstream outputFile(filename);
    if (!outputFile.is_open()) {
        cerr << "Error: Unable to open file " << filename << " for writing." << endl;
        return {};
    }

    // Write the number of nodes to the file
    outputFile << numNodes << endl;

    // Write the adjacency matrix to the file
    for (const auto& row : weightedMatrix) {
        for (int weight : row) {
            outputFile << weight << " ";
        }
        outputFile << endl;
    }

    outputFile.close();

    // Return the generated graph
    return weightedMatrix;
}

// int main() {
//     // Get the number of nodes from the user
//     int numNodes;
//     cout << "Enter the number of nodes: ";
//     cin >> numNodes;

//     // Generate the random symmetric weighted matrix and write it to file
//     vector<vector<int>> generatedGraph = generateMatrix(numNodes, "graph.graph");

//     cout << "Graph written to file 'graph.graph'." << endl;

//     // You can use the generatedGraph here for further processing if needed

//     return 0;
// }
