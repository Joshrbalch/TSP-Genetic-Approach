#include <iostream>
#include <vector>
#include <queue>
#include "TSPAlgorithms.h"

using namespace std;

int tspNeighborAll(const vector<vector<int>>& graph, int start){
    vector<int> costs;
    
    for(int i = 0; i < graph.size(); i++){
        costs.push_back(tspNeighbor(graph, i));
    }

    return *min_element(costs.begin(), costs.end());
}