#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>

using namespace std;

// Function to solve the TSP using naive neighbor search
int tsp(const vector<vector<int>>& graph, int start) {
    int n = graph.size();
    vector<int> markedCities(n, 0);
    markedCities[start] = 1;

    int minCost = 0;
    int prevCity = start;

    // For each city, find the nearest neighbor

    for(int i = 0; i < n; i++) {
        int nextCity = INT_MAX;

        // If we are at the last city, go back to the start
        if(i == n - 1) {
            nextCity = start;
            minCost += graph[prevCity][nextCity];
            cout << "Traveling home from city " << prevCity <<": " << graph[prevCity][nextCity] << endl;
            break;
        }

        //flag symbolizing if we are on the first iteration
        bool flag = true;

        for(int j = 0; j < n; j++) {
            // If we are at the same city or we have already visited this city, skip it
            if(j == prevCity || markedCities[j] == 1) {
                continue;
            }

            // If we are on the first iteration, set the next city to the first unvisited city
            if(flag == true) {
                nextCity = j;
                flag = false;
            }
            
            // If the distance to the current city is less than the distance to the next city, set the next city to the current city
            else if(graph[prevCity][j] < graph[prevCity][nextCity]) {
                nextCity = j;
            }
        }

        minCost += graph[prevCity][nextCity];
        cout << "Traveling from city " << prevCity << " to city " << nextCity << ": " << graph[prevCity][nextCity] << endl;
        prevCity = nextCity;
        markedCities[nextCity] = 1;
    } 

    return minCost;
}