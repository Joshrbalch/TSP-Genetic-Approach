#ifndef INDIVIDUAL_H
#define INDIVIDUAL_H

#include <vector>
#include <algorithm>

using namespace std;

struct individual {
    vector<int> path;  // Store the path as a vector of integers
    int fitness = 0;
};

#endif