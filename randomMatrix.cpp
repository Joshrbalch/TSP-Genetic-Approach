#ifndef RANDOMMATRIX_CPP

#define RANDOMMATRIX_CPP

#include <iostream>
#include <vector>
#include <random>

// Function to generate a random adjacency matrix for a graph with the given number of nodes

using namespace std;

vector<vector<int>> generateMatrix(int numNodes) {
    // Initialize a 2D vector with all elements set to 0
    vector<vector<int>> weightedMatrix(numNodes, vector<int>(numNodes, 0));

    // Use a random device and a Mersenne Twister engine for random number generation
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<int> distribution(1, 100);  // Adjust the range as needed

    // Generate random weights for the edges (symmetric)
    for (int i = 0; i < numNodes; ++i) {
        for (int j = i + 1; j < numNodes; ++j) {
            int weight = distribution(gen);
            weightedMatrix[i][j] = weight;
            weightedMatrix[j][i] = weight;  // Set the symmetric element
        }
    }

    return weightedMatrix;
}

// int main() {
//     // Get the number of nodes from the user
//     int numNodes;
//     std::cout << "Enter the number of nodes: ";
//     std::cin >> numNodes;

//     // Generate the random symmetric weighted matrix
//     std::vector<std::vector<int>> weightedMatrix = generateMatrix(numNodes);

//     // Display the generated symmetric weighted matrix
//     std::cout << "Generated Random Symmetric Weighted Matrix:\n";
//     for (const auto &row : weightedMatrix) {
//         for (int weight : row) {
//             std::cout << weight << " ";
//         }
//         std::cout << "\n";
//     }

//     return 0;
// }



#endif