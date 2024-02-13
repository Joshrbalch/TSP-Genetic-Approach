#ifndef TSPGENETIC_CPP
#define TSPGENETIC_CPP

#include <iostream>
#include <fstream>
#include <vector>
#include <limits.h>
#include <cstdlib>
#include <ctime>
#include <cmath>
#include <algorithm>
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
        ELITE_PERCENTAGE = 0.01;
        
        if(V <= 10) {
            POP_SIZE = 100;
            gen_thres = 100;
        } else if(V <= 20) {
            POP_SIZE = pow(V, 2);
            gen_thres = pow(2, (V / 2));
        } else {
            POP_SIZE = V;
            gen_thres = (V * 100) / 2;
            ELITE_PERCENTAGE = 0.05;
        }
    }

    TSPGenetic() {
        V = 100;
        POP_SIZE = 5000;
        ELITE_PERCENTAGE = 0.1;
    }

    // Helper function to generate a random number between start and end
    int rand_num(int start, int end) {
        int r = end - start;
        int rnum = start + rand() % r;
        return rnum;
    }

    // Helper function to check if a character repeats in a string
    bool repeat(const vector<int>& path, int city) {
        return find(path.begin(), path.end(), city) != path.end();
    }

    // Helper function to mutate a path
    void mutatePath(vector<int>& path) {
        int index1 = rand_num(1, V - 1);
        int index2 = rand_num(1, V - 1);
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

    // Helper function to cool down the temperature
    int cooldown(int temp) {
        return (20 * temp) / 100;
    }

    // Comparator function for sorting individuals by fitness
    bool lessthan(const individual& t1, const individual& t2) {
        return t1.fitness < t2.fitness;
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

        // Initialize the best solution variable
        shortestPathIndividual = population[0];

        // Main loop of genetic algorithm
        int temperature = 10000;
        while (gen <= gen_thres) {
            sort(population.begin(), population.end(), [&](individual& t1, individual& t2) { return t1.fitness < t2.fitness; });
            vector<individual> new_population;

            // Calculate the number of elite individuals to preserve
            int elite_count = POP_SIZE * ELITE_PERCENTAGE;

            // Copy the elite individuals directly into the new population
            for (int i = 0; i < elite_count; i++) {
                new_population.push_back(population[i]);
            }

            // Apply genetic operations to the remaining individuals
            for (int i = elite_count; i < POP_SIZE; i++) {
                individual p1 = population[i];
                individual new_individual;
                new_individual.path = p1.path;
                mutatePath(new_individual.path);
                new_individual.fitness = cal_fitness(new_individual.path, map);

                if (new_individual.fitness <= population[i].fitness) {
                    new_population.push_back(new_individual);
                } else {
                    float prob = exp(-1 * ((float)(new_individual.fitness - population[i].fitness) / temperature));
                    if (prob > 0.5) {
                        new_population.push_back(new_individual);
                    }
                }
            }

            temperature = cooldown(temperature);
            population = new_population;
            gen++;

            // Update the best solution if a new best is found
            if (population[0].fitness < shortestPathIndividual.fitness) {
                shortestPathIndividual = population[0];
            }

            int mincost = INT_MAX;

            cout << "Generation: " << gen << endl;
            cout << "Population size: " << population.size() << endl;
            cout << "Population lowest cost: ";

            for (int i = 0; i < population.size(); i++) {
                if (cal_fitness(population[i].path, map) < mincost) {
                    mincost = cal_fitness(population[i].path, map);
                }
            }

            cout << mincost << endl;
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
