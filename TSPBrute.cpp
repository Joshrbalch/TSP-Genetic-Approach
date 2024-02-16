#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>

using namespace std;

// Recursive function to find the minimum cost of TSP
int tspRecursive(const vector<vector<int>>& graph, vector<int>& cities, int start, int current, int cost) {
    int n = graph.size();
    // Base case: If all cities have been visited, return the cost of returning to the starting city
    if (current == n) {
        return cost + graph[cities[current - 1]][start];
    }
    int minCost = INT_MAX;
    // Try visiting each unvisited city from the current city
    for (int i = current; i < n; i++) {
        // Swap the current city with the ith city to explore different permutations
        swap(cities[current], cities[i]);
        // Calculate the cost of visiting the ith city from the current city
        int newCost = cost + graph[cities[current - 1]][cities[current]];
        // Recur to explore further paths with the updated cost and current city index
        minCost = min(minCost, tspRecursive(graph, cities, start, current + 1, newCost));
        // Undo the swap to backtrack and try other permutations
        swap(cities[current], cities[i]);
    }
    return minCost;
}

// Function to solve the TSP using brute force recursively
int tspBrute(const vector<vector<int>>& graph, int start) {
    int n = graph.size();
    vector<int> cities(n);
    for (int i = 0; i < n; i++) {
        cities[i] = i;
    }
    // Start with the first city and index 1 (since the first city is already chosen)
    return tspRecursive(graph, cities, start, 1, 0);
}

// // Example usage:
// int main() {
//     vector<vector<int>> graph = {
//         {0, 10, 15, 20},
//         {10, 0, 35, 25},
//         {15, 35, 0, 30},
//         {20, 25, 30, 0}
//     };
//     int start = 0; // Starting city
//     int minCost = tspBruteRecursive(graph, start);
//     cout << "Minimum cost for TSP: " << minCost << endl;
//     return 0;
// }
