#include <iostream>
#include <vector>
#include <queue>
#include <limits>

using namespace std;

// Function to find the shortest path using Dijkstra's algorithm
vector<int> dijkstra(const vector<vector<int>>& graph, int start) {
    int n = graph.size();
    vector<int> dist(n, numeric_limits<int>::max());
    vector<bool> visited(n, false);
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;

    dist[start] = 0;
    pq.push({0, start});

    while (!pq.empty()) {
        int u = pq.top().second;
        pq.pop();

        if (visited[u]) {
            continue;
        }

        visited[u] = true;

        for (int v = 0; v < n; ++v) {
            if (graph[u][v] != -1 && dist[u] + graph[u][v] < dist[v]) {
                dist[v] = dist[u] + graph[u][v];
                pq.push({dist[v], v});
            }
        }
    }

    return dist;
}

// Function to solve the TSP using SSSP combined with heuristics
int tspSSSP(const vector<vector<int>>& graph) {
    int n = graph.size();
    vector<vector<int>> dist(n, vector<int>(n, -1));

    // Precompute the shortest distances between all pairs of vertices using Dijkstra's algorithm
    for (int i = 0; i < n; ++i) {
        dist[i] = dijkstra(graph, i);
    }

    std::vector<int> path;
    std::vector<bool> visited(n, false);
    int current = 0;
    visited[current] = true;
    path.push_back(current);

    while (path.size() < n) {
        int next = -1;
        int minDist = std::numeric_limits<int>::max();

        // Find the nearest unvisited neighbor using the precomputed distances
        for (int i = 0; i < n; ++i) {
            if (!visited[i] && dist[current][i] < minDist) {
                minDist = dist[current][i];
                next = i;
            }
        }

        if (next == -1) {
            // No unvisited neighbors left, return to the starting vertex
            path.push_back(0);
            break;
        }

        visited[next] = true;
        path.push_back(next);
        current = next;
    }

    // Calculate the total distance of the TSP tour
    int totalDistance = 0;
    for (int i = 0; i < n - 1; ++i) {
        totalDistance += graph[path[i]][path[i + 1]];
    }

    return totalDistance;
}

// int main() {
//     // Example usage
//     std::vector<std::vector<int>> graph = {
//         {0, 2, 9, 10},
//         {1, 0, 6, 4},
//         {15, 7, 0, 8},
//         {6, 3, 12, 0}
//     };

//     int shortestDistance = tspWithHeuristics(graph);
//     std::cout << "Shortest distance: " << shortestDistance << std::endl;

//     return 0;
// }
