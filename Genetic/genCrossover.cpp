#include <iostream>
#include <vector>
#include <random>
#include <algorithm>
#include <unordered_set>


using namespace std;

// Function to perform order crossover for TSP
// Function to perform order crossover for TSP
vector<vector<int>> orderCrossover(const vector<vector<int>>& parents) {
    // Initialize offspring
    vector<vector<int>> offspring = parents;

    // Randomly select crossover points
    int size = parents[0].size();
    int crossoverPoint1 = rand() % size;
    int crossoverPoint2 = rand() % size;
    if (crossoverPoint1 > crossoverPoint2) {
        swap(crossoverPoint1, crossoverPoint2);
    }

    // Check for duplicates in crossover pairs
    vector<bool> hasDuplicates(parents.size(), false);
    for (int i = 0; i < parents.size(); ++i) {
        unordered_set<int> cities(parents[i].begin() + crossoverPoint1, parents[i].begin() + crossoverPoint2);
        if (cities.size() < crossoverPoint2 - crossoverPoint1) {
            hasDuplicates[i] = true;
        }
    }

    // Perform crossover for each parent pair
    for (int i = 0; i < parents.size() - 1; ++i) {
        if (hasDuplicates[i] || hasDuplicates[i + 1]) {
            continue;  // Skip crossover if either parent pair has duplicates
        }
        // Copy segment between crossover points from the second parent to the first offspring
        copy(parents[i + 1].begin() + crossoverPoint1, parents[i + 1].begin() + crossoverPoint2,
             offspring[i].begin() + crossoverPoint1);
        // Initialize iterators for the second parent and the first offspring
        auto itParent = parents[i].begin();
        auto itOffspring = offspring[i].begin();
        // Copy remaining elements from the first parent to the first offspring, avoiding duplicates
        for (int j = 0; j < size; ++j) {
            if (itParent != parents[i].begin() + crossoverPoint1 && find(offspring[i].begin(), itOffspring, *itParent) == itOffspring) {
                *itOffspring++ = *itParent;
            }
            if (++itParent == parents[i].end()) {
                itParent = parents[i].begin();
            }
        }
    }

    return offspring;
}


// Function to print a vector
void printVector(const vector<int>& vec) {
    for (int i = 0; i < vec.size(); i++) {
        cout << vec[i] << " ";
    }
    cout << endl;
}

int main() {
    // Define parent vectors (representing solutions to TSP)
    vector<vector<int>> parents = {
        {1, 2, 3, 4, 5, 6, 7, 8, 9},
        {9, 3, 7, 8, 2, 6, 5, 1, 4},
        {2, 4, 6, 8, 1, 3, 5, 7, 9}
    };

    // Perform crossover multiple times
    for (int i = 0; i < 3; i++) {
        parents = orderCrossover(parents);
        cout << "Crossover " << i + 1 << " done" << endl;
    }

    // Display offspring
    for (int i = 0; i < parents.size(); i++) {
        cout << "Offspring " << i << ": ";
        printVector(parents[i]);
    }

    return 0;
}
