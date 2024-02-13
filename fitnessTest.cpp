#include <iostream>
#include <vector>
#include <cassert>
#include <cstdlib>
#include <ctime>
#include <climits>
#include <algorithm>

using namespace std;

// Your fitness function
int cal_fitness(const vector<int>& path, const vector<vector<int>>& map) {
    int f = 0;

    for (int i = 0; i < path.size() - 1; i++) {
        int city1 = path[i];
        int city2 = path[i + 1];

        if (city1 >= map.size() || city2 >= map.size()) {
            return INT_MAX;
        }

        if (map[city1][city2] == INT_MAX) {
            return INT_MAX;
        }

        f += map[city1][city2];
    }

    return f;
}

// Generate a random path
vector<int> generateRandomPath(int size) {
    vector<int> path;
    path.push_back(0);  // Start with city 0

    while (path.size() < size) {
        int city = rand() % size;
        if (find(path.begin(), path.end(), city) == path.end()) {
            path.push_back(city);
        }
    }

    path.push_back(0);  // End at city 0
    return path;
}

// Generate a random adjacency matrix
vector<vector<int>> generateRandomAdjacencyMatrix(int size) {
    vector<vector<int>> map(size, vector<int>(size));

    // Initialize the matrix with random distances
    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
            if (i == j) {
                map[i][j] = 0;  // Diagonal elements are zero
            } else {
                map[i][j] = rand() % 100;  // Random distance between 0 and 99
            }
        }
    }

    return map;
}

int main() {
    // Seed the random number generator
    srand(time(NULL));

    // Define the number of cities
    int size = 10;

    // Generate a random path and adjacency matrix
    vector<int> path = generateRandomPath(size);
    vector<vector<int>> map = generateRandomAdjacencyMatrix(size);

    // Calculate fitness using the function
    int calculated_fitness = cal_fitness(path, map);

    // Calculate the expected fitness manually
    int expected_fitness = 0;
    for (int i = 0; i < size; ++i) {
        expected_fitness += map[path[i]][path[i + 1]];
    }

    // Assert if the calculated fitness matches the expected fitness
    assert(calculated_fitness == expected_fitness);

    cout << "Test passed: Fitness function is calculating correctly!" << endl;

    return 0;
}
