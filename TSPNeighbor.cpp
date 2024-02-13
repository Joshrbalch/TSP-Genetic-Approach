#ifndef TSPNEIGHBOR_CPP
#define TSPNEIGHBOR_CPP

#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>

using namespace std;

// Function to solve the TSP using naive neighbor search
int tspNeighbor(const vector<vector<int>>& graph, int start, int numNodes) {
    // cout << "Solving TSP using naive neighbor search..." << endl; // Print a message when starting the neighbor search algorithm
    int n = numNodes;
    // cout << n << endl;

    // cout << "Size of graph: " << n << endl; // Print the size of the graph
    vector<int> markedCities(n, 0);
    vector<int> path;
    markedCities[start] = 1;

    int minCost = 0;
    int prevCity = start;

    // For each city, find the nearest neighbor
    for(int i = 0; i < n; i++) {
        // cout << "City " << i << endl; // Print the current city
        int nextCity = -1; // Initialize nextCity to an invalid value

        // Initialize minDist to a very large value
        int minDist = INT_MAX;

        // Find the nearest unmarked neighbor
        for(int j = 0; j < n; j++) {
            if(j != prevCity && markedCities[j] == 0 && graph[prevCity][j] < minDist) {
                nextCity = j;
                minDist = graph[prevCity][j];
            }
        }

        if(nextCity == -1) {
            // No unmarked neighbors left, return to the start
            nextCity = start;
            minCost += graph[prevCity][nextCity];
            path.push_back(nextCity);
            // cout << "Reached the last city. Traveling back to start." << endl; // Print a message when reaching the last city
            break;
        }

        minCost += graph[prevCity][nextCity];
        path.push_back(prevCity);
        // cout << "Traveling from city " << prevCity << " to city " << nextCity << endl; // Print the cities being traveled from and to
        prevCity = nextCity;
        markedCities[nextCity] = 1;
    } 

    // Print the path
    // cout << "Path: ";
    // for(int i = 0; i < path.size(); i++) {
    //     cout << path[i] << " ";
    // }
    // cout << endl;

    return minCost;
}



#endif
