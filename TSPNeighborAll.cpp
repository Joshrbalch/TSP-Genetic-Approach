#include <iostream>
#include <vector>
#include <queue>
#include "TSPAlgorithms.h"

using namespace std;

individual tspNeighborAll(const vector<vector<int>>& graph, int start, int numNodes){
    vector<individual> costs;

    for(int i = 0; i < 50; i++){
        costs.push_back(tspNeighbor(graph, i, numNodes));
    }

    individual minPath = costs[0];

    for(int i = 0; i < costs.size(); i++){
        if(costs[i].fitness < minPath.fitness){
            minPath = costs[i];
        }
    }

    for(int i = 0; i < minPath.path.size(); i++){
        cout << minPath.path[i] << " ";
    }

    return minPath;
}