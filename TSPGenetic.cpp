#include <iostream>
#include <vector>
#include <algorithm>
#include <cstdlib>
#include <ctime>
#include <climits>
#include "TSPAlgorithms.h"

using namespace std;

class TSPGenetic {
    public:
    vector<vector<int>> graph;
    int populationSize;
    int generations;

    TSPGenetic(const vector<vector<int>>& graph, int populationSize, int generations) {
        this->graph = graph;
        this->populationSize = populationSize;
        this->generations = generations;
    }

    vector<int> geneticAlgorithm(const vector<vector<int>>& graph, int populationSize, int generations) {
        
    }

    int fitness(const vector<int> chromosome) {
        int n = chromosome.size();
        int cost = 0;

        for(int i = 0; i < n - 1; i++) {
            cost += graph[chromosome[i]][chromosome[i + 1]];
        }

        cost += graph[chromosome[n - 1]][chromosome[0]];

        return cost;
    }

    vector<vector<int>> generatePopulation(int populationSize, int n) {
        vector<vector<int>> population;

        for(int i = 0; i < populationSize; i++) {
            vector<int> chromosome;
            for(int j = 0; j < n; j++) {
                chromosome.push_back(j);
            }
            random_shuffle(chromosome.begin(), chromosome.end());
            population.push_back(chromosome);
        }

        return population;
    }
}

int main() {
    int input;
    cin >> input;
    vector<vector<int>> graph = generateMatrix(input);

    int populationSize = 10; // Adjust population size as needed
    int generations = 10;    // Adjust number of generations as needed

    cout << "Starting genetic algorithm..." << endl;

    // Run the genetic algorithm
    vector<int> bestSolution = geneticAlgorithm(graph, populationSize, generations);

    // Print the best solution found
    cout << "Best solution: ";

    for (int city : bestSolution) {
        cout << city << " ";
    }

    cout << endl;

    cout << "Genetic algorithm finished." << endl;

    return 0;
}
