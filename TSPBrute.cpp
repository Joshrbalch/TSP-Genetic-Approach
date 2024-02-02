#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>

using namespace std;

// Function to solve the TSP using brute force

int tspBrute(const vector<vector<int>>& graph, int start) {
    int n = graph.size();
    vector<int> cities(n);
    for(int i = 0; i < n; i++) {
        cities[i] = i;
    }
    int minCost = INT_MAX;
    do {
        int cost = 0;
        int prevCity = start;
        for(int i = 0; i < n; i++) {
            int nextCity = cities[i];
            cost += graph[prevCity][nextCity];
            prevCity = nextCity;
        }
        cost += graph[prevCity][start];
        minCost = min(minCost, cost);
    } while(next_permutation(cities.begin(), cities.end()));
    return minCost;
}