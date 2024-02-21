#ifndef TSPGENETIC_H
#define TSPGENETIC_H

// This algorithm was written by Joshua Balch at the University of Alabama

#include <iostream>
#include <fstream>
#include <vector>
#include <limits.h>
#include <cstdlib>
#include <ctime>
#include <cmath>
#include <algorithm>
#include <random>
#include "TSPAlgorithms.h"
#include "individual.cpp"

using namespace std;

class TSPGenetic {
public:
    int V;  // Number of cities in TSP
    long long POP_SIZE;  // Initial population size for the algorithm
    double ELITE_PERCENTAGE; // Percentage of elite individuals to preserve
    int gen_thres;
    individual shortestPathIndividual; // Store the shortest path individual

    // Constructors
    TSPGenetic(int v, int pop_size, double elite_percentage, int gen_threshold) {
        V = v;
        POP_SIZE = pop_size;
        ELITE_PERCENTAGE = elite_percentage;
        gen_thres = gen_threshold;
    }

    TSPGenetic(int v) {
        V = v;
        ELITE_PERCENTAGE = 0.5;
        
        if(V <= 10) {
            POP_SIZE = 100;
            gen_thres = 100;
        } 

        else if(V <= 20) {
            POP_SIZE = pow(V, 2);
            gen_thres = pow(2, (V / 2));
        } 

        else if(V <= 100){
            POP_SIZE = V * 10;
            gen_thres = V * 100;
        }

        else if(V <= 500) {
            POP_SIZE = V;
            gen_thres = V * 100;
        }

        else {
            POP_SIZE = V / 5;
            gen_thres = V * 10;
        }
    }

    TSPGenetic() {
        V = 100;
        POP_SIZE = 5000;
        ELITE_PERCENTAGE = 0.1;
    }

    // Helper function to generate a random number between start and end
    int rand_num(int start, int end) {
        random_device rd;
        mt19937 gen(rd());
        uniform_int_distribution<int> dis(start, end - 1);
        return dis(gen);
    }

    // Helper function to check if a character repeats in a string
    bool repeat(const vector<int>& path, int city) {
        return find(path.begin(), path.end(), city) != path.end();
    }

    // Helper function to mutate a path
    void mutatePath(vector<int>& path) {
        int index1 = rand_num(1, path.size() - 2); // Adjusted range to avoid mutating the start and end cities
        int index2 = rand_num(1, path.size() - 2); // Adjusted range to avoid mutating the start and end cities

        swap(path[index1], path[index2]);
    }

    // Helper function to create a random path
    vector<int> createPath() {
        vector<int> path;
        path.push_back(0);  // Start with city 0

        while (path.size() < V) {
            int city = rand_num(1, V);
            if (!repeat(path, city)) {
                path.push_back(city);
            }
        }

        path.push_back(0);  // End at city 0
        return path;
    }

    // Helper function to calculate the fitness of a path
    int cal_fitness(const vector<int>& path, const vector<vector<int>>& map) {
        int f = 0;

        for (int i = 0; i < path.size() - 1; i++) {
            int city1 = path[i];
            int city2 = path[i + 1];

            if (city1 >= map.size() || city2 >= map.size()) {
                return INT_MAX;
            }

            if (map[city1][city2] == INT_MAX) {
                return INT_MAX;
            }

            f += map[city1][city2];
        }
        return f;
    }

    individual reproduce(individual parent1, individual parent2, const vector<vector<int>>& map) {
        // cout << "Reproducing..." << endl;
        
        int start = rand_num(1, V - 2); // Adjusted the range to ensure it stays within bounds
        int end = rand_num(start + 1, V - 1); // Ensures end is greater than start and within bounds
        // cout << "Start: " << start << ", End: " << end << endl;
        
        vector<int> childPath;
        vector<bool> taken(V, false); // A vector to mark which cities are already taken

        // Copy the segment from parent1
        for (int i = start; i <= end; i++) {
            // cout << "Pushing " << parent1.path[i] << " from parent1" << endl;
            childPath.push_back(parent1.path[i]);
            taken[parent1.path[i]] = true; // Mark the city as taken
            // cout << "Child path size after push: " << childPath.size() << endl;
        }

        // Copy the remaining cities from parent2
        for (int i = 0; i < V; i++) {
            if (!taken[parent2.path[i]]) {
                // cout << "Pushing " << parent2.path[i] << " from parent2" << endl;
                childPath.push_back(parent2.path[i]);
                taken[parent2.path[i]] = true; // Mark the city as taken
                // cout << "Child path size after push: " << childPath.size() << endl;
            }
        }

        // cout << "Creating child individual..." << endl;

        individual child;
        child.path = childPath;
        child.fitness = cal_fitness(childPath, map);
        return child;
    }

    // Genetic algorithm function for solving TSP
    individual TSPUtil(const vector<vector<int>>& map) {
        int gen = 1;

        vector<individual> population;

        // Initialize population
        srand(time(NULL));
        for (int i = 0; i < POP_SIZE; i++) {
            individual temp;
            temp.path = createPath();
            temp.fitness = cal_fitness(temp.path, map);
            population.push_back(temp);
        }

        population[0] = tspNeighbor(map, 0, V);

        // Initialize the best solution variable
        shortestPathIndividual = population[0];

        // Main loop of genetic algorithm
        while (gen <= gen_thres) {
            sort(population.begin(), population.end(), [&](individual& t1, individual& t2) { return t1.fitness < t2.fitness; });
            vector<individual> new_population;

            // Calculate the number of elite individuals to preserve
            int elite_count = POP_SIZE * ELITE_PERCENTAGE;

            // Copy the elite individuals directly into the new population
            for (int i = 0; i < elite_count; i++) {
                new_population.push_back(population[i]);
            }

            // Reproduce the elite individuals to fill the rest of the population
            for (int i = 0; i < elite_count; i++) {
                int r = rand_num(0, population.size() - 1);
                individual parent1 = population[r];
                r = rand_num(0, population.size() - 1);
                individual parent2 = population[r];
                individual child = reproduce(parent1, parent2, map);
                new_population.push_back(child);
            }

            int mutations = rand() % (POP_SIZE / 2) + 1;

            // Mutate a portion of the population
            for (int i = 0; i < mutations; i++) {
                individual mutatedIndividual = population[i];
                mutatePath(mutatedIndividual.path);
                mutatedIndividual.fitness = cal_fitness(mutatedIndividual.path, map);
                new_population.push_back(mutatedIndividual);
            }

            //fill rest of population
            while (new_population.size() < POP_SIZE) {
                individual temp;
                int random = rand() % POP_SIZE;
                temp.path = population[random].path;
                temp.fitness = population[random].fitness;
                new_population.push_back(temp);
            }

            population = new_population;
            gen++;

            // Update the best solution if a new best is found
            if (population[0].fitness < shortestPathIndividual.fitness) {
                shortestPathIndividual = population[0];
                cout << "Generation: " << gen << " Found a new Best Path: " << shortestPathIndividual.fitness << endl;
            }
        }

        cout << "Population evolved successfully!" << endl;
        cout << "Minimum path cost: " << shortestPathIndividual.fitness << endl;
        cout << "And Path is: ";

        for (int city : shortestPathIndividual.path) {
            cout << city << " ";
        }

        cout << endl;

        return shortestPathIndividual;
    }
};

#endif
