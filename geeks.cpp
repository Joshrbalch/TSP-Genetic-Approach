#include <iostream>
#include <fstream>
#include <vector>
#include <limits.h>
#include <cstdlib>
#include <ctime>
#include <cmath>
#include <algorithm>

using namespace std;

#define V 1000  // Number of cities in TSP
#define POP_SIZE 1000  // Initial population size for the algorithm

struct individual {
    vector<int> path;  // Store the path as a vector of integers
    int fitness;
};

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
    return (90 * temp) / 100;
}

// Comparator function for sorting individuals by fitness
bool lessthan(const individual& t1, const individual& t2) {
    return t1.fitness < t2.fitness;
}

// Genetic algorithm function for solving TSP
individual TSPUtil(const vector<vector<int>>& map) {
    int gen = 1;
    int gen_thres = 5;

    vector<individual> population;

    // Initialize population
    srand(time(NULL));
    for (int i = 0; i < POP_SIZE; i++) {
        individual temp;
        temp.path = createPath();
        temp.fitness = cal_fitness(temp.path, map);
        population.push_back(temp);
    }

    // Main loop of genetic algorithm
    int temperature = 10000;
    while (temperature > 1000 && gen <= gen_thres) {
        sort(population.begin(), population.end(), lessthan);
        vector<individual> new_population;

        for (int i = 0; i < POP_SIZE; i++) {
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

        int mincost = INT_MAX;

        cout << "Generation: " << gen << endl;
        cout << "Population size: " << population.size() << endl;
        cout << "Population lowest cost: ";

        for(int i = 0; i < population.size(); i++){
            if(population[i].fitness < mincost){
                mincost = population[i].fitness;
            }
        }

        cout << mincost << endl;
        
    }

    cout << "Population evolved successfully!" << endl;

    individual mincostind = population[0];
    for (const auto& ind : population) {
        if (ind.fitness < mincostind.fitness) {
            mincostind = ind;
        }
    }

    cout << "Minimum path cost: " << mincostind.fitness << endl;
    cout << "And Path is: ";
    for (int city : mincostind.path) {
        cout << city << " ";
    }
    cout << endl;

    return mincostind;
}

int main() {
    ifstream infile("Size100.graph");
    if (!infile) {
        cerr << "Error: Unable to open input file." << endl;
        return 1;
    }

    vector<vector<int>> map(V, vector<int>(V));
    for (int i = 0; i < V; ++i) {
        for (int j = 0; j <= i; ++j) {
            infile >> map[i][j];
            map[j][i] = map[i][j]; // Since the graph is undirected, fill in the other half of the matrix
        }
    }

    cout << "Adjacency matrix read successfully!" << endl;

    individual p = TSPUtil(map);

    return 0;
}
