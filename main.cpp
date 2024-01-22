#include "TSPNeighbor.cpp"
#include <iostream>
#include <vector>
#include <algorithm>

int main() {
    // Example usage
    vector<vector<int>> graph = {
        {0, 10, 15, 20},
        {10, 0, 35, 25},
        {15, 35, 0, 30},
        {20, 25, 30, 0}
    };
    
    int startCity = 0;
    int minCost = tsp(graph, startCity);
    
    cout << "Minimum cost of the TSP starting from city " << startCity << ": " << minCost << std::endl;
    
    return 0;
}