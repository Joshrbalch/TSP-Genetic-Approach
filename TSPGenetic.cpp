#include <iostream>
#include <vector>
#include <algorithm>
#include <cstdlib>
#include <ctime>
#include <climits>

using namespace std;

// Function to generate random matrix for testing purposes
vector<vector<int>> generateMatrix(int n) {
    vector<vector<int>> graph(n, vector<int>(n));
    srand(time(NULL));
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            if (i == j) {
                graph[i][j] = 0;
            } else {
                graph[i][j] = rand() % 100; // Random distance between cities (0 to 99)
            }
        }
    }
    return graph;
}

// Function to generate initial population using nearest neighbor searches
vector<vector<int>> generateInitialPopulation(const vector<vector<int>>& graph, int populationSize) {
    cout << "Generating initial population..." << endl;
    vector<vector<int>> population;
    int n = graph.size();

    // Perform nearest neighbor searches to generate solutions
    for (int i = 0; i < populationSize; ++i) {
        vector<int> markedCities(n, 0);
        vector<int> solution;
        int currentCity = rand() % n;
        markedCities[currentCity] = 1;
        solution.push_back(currentCity);

        for (int j = 0; j < n - 1; ++j) {
            int nextCity = -1; // Initialize with an invalid value
            for (int k = 0; k < n; ++k) {
                if (k == currentCity || markedCities[k] == 1) {
                    continue;
                }
                if (nextCity == -1 || graph[currentCity][k] < graph[currentCity][nextCity]) {
                    nextCity = k;
                }
            }

            if (nextCity == -1) {
                cerr << "Error: Unable to find next city for nearest neighbor search." << endl;
                exit(EXIT_FAILURE);
            }

            solution.push_back(nextCity);
            markedCities[nextCity] = 1;
            currentCity = nextCity;
        }

        population.push_back(solution);
    }

    cout << "Initial population generated." << endl;
    return population;
}

// Function to evaluate the fitness of a solution (total distance traveled)
int evaluateFitness(const vector<vector<int>>& graph, const vector<int>& solution) {
    int totalDistance = 0;
    for (int i = 0; i < solution.size() - 1; ++i) {
        totalDistance += graph[solution[i]][solution[i + 1]];
    }
    // Add distance from the last city back to the starting city
    totalDistance += graph[solution.back()][solution[0]];
    return totalDistance;
}

// Selection: Tournament selection
vector<int> tournamentSelection(const vector<vector<int>>& population, const vector<int>& fitnessValues, int tournamentSize) {
    vector<int> selectedParents;
    int populationSize = population.size();
    for (int i = 0; i < populationSize; ++i) {
        int bestIdx = rand() % populationSize;
        for (int j = 1; j < tournamentSize; ++j) {
            int idx = rand() % populationSize;
            if (fitnessValues[idx] < fitnessValues[bestIdx]) {
                bestIdx = idx;
            }
        }
        selectedParents.push_back(bestIdx);
    }
    return selectedParents;
}

// Crossover: Order crossover (OX)
vector<int> orderCrossover(const vector<int>& parent1, const vector<int>& parent2) {
    int n = parent1.size();
    int startPos = rand() % n;
    int endPos = (startPos + rand() % (n - 1) + 1) % n;
    vector<int> child(n, -1);
    for (int i = startPos; i != endPos; i = (i + 1) % n) {
        child[i] = parent1[i];
    }
    int idx = endPos;
    for (int i = endPos; i != startPos; i = (i + 1) % n) {
        if (find(child.begin(), child.end(), parent2[i]) == child.end()) {
            child[idx] = parent2[i];
            idx = (idx + 1) % n;
        }
    }
    return child;
}

// Mutation: Swap mutation
void swapMutation(vector<int>& solution) {
    int n = solution.size();
    int idx1 = rand() % n;
    int idx2 = rand() % n;
    swap(solution[idx1], solution[idx2]);
}

// Main function for the genetic algorithm
// Main function for the genetic algorithm
vector<int> geneticAlgorithm(const vector<vector<int>>& graph, int populationSize, int generations) {
    srand(time(NULL)); // Seed the random number generator
    int n = graph.size();

    cout << "Initializing genetic algorithm..." << endl;

    // Generate initial population using nearest neighbor searches
    vector<vector<int>> population = generateInitialPopulation(graph, populationSize);

    // Initialize bestIdx with a default value
    int bestIdx = 0;

    cout << "Genetic algorithm initialized." << endl;

    // Main loop for the genetic algorithm
    for (int gen = 0; gen < generations; ++gen) {
        // Evaluate fitness of each solution in the population
        vector<int> fitnessValues(populationSize);
        for (int i = 0; i < populationSize; ++i) {
            fitnessValues[i] = evaluateFitness(graph, population[i]);
        }

        // Find the best solution in the current population
        int minFitness = *min_element(fitnessValues.begin(), fitnessValues.end());
        bestIdx = distance(fitnessValues.begin(), min_element(fitnessValues.begin(), fitnessValues.end()));
        vector<int> bestSolution = population[bestIdx];

        // Print the best solution in each generation
        cout << "Generation " << gen << ": Best distance = " << minFitness << endl;

        // Perform selection, crossover, and mutation
        vector<int> selectedParents = tournamentSelection(population, fitnessValues, 2); // Tournament selection with tournament size of 2
        vector<vector<int>> offspring;

        for (int i = 0; i < populationSize; ++i) {
            vector<int> child = orderCrossover(population[selectedParents[i % 2]], population[selectedParents[(i + 1) % 2]]);
            if (rand() % 100 < 10) { // Mutation rate of 10%
                swapMutation(child);
            }
            offspring.push_back(child);
        }

        population.clear(); // Clear the current population
        population.reserve(offspring.size()); // Reserve memory for the new population
        for (const auto& child : offspring) {
            population.push_back(child);
        }

        // For now, we'll just print the best solution found so far
        cout << "Best solution: ";
        for (int city : bestSolution) {
            cout << city << " ";
        }
        cout << endl;
    }

    // Return the best solution found
    if (!population.empty()) {
        return population[bestIdx];
    } else {
        cout << "Warning: Population is empty. No best solution found." << endl;
        return vector<int>(); // Return an empty vector
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
