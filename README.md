# Traveling Salesman Problem Solver

## Overview

This project aims to solve the Traveling Salesman Problem (TSP) using various algorithms implemented in C++. The TSP is a classic optimization problem where the goal is to find the shortest possible route that visits each city exactly once and returns to the original city.

## Features

- **Brute Force Algorithm**: Solves the TSP by exhaustively searching through all possible permutations of cities.  
  - **Warning**: Do not use brute force with graphs where the number of nodes exceeds 13. It will take an impractical amount of time.
- **Genetic Algorithm**: Implements a genetic algorithm to find approximate solutions to the TSP.
- **Nearest Neighbor Algorithm**: Utilizes the nearest neighbor heuristic to quickly find a feasible solution.
- **Nearest Neighbor All Algorithm**: Runs the Nearest Neighbor Algorithm on all nodes and returns the best solution found.
- **Random Graph Generator**: Generates random symmetric weighted graphs to test the algorithms and outputs the generated graph to `graph.graph`.
- **Testing Suite**: Includes a testing suite to evaluate the performance of each algorithm and compare their results.

## Directory Structure

All project files are stored in the main directory. The `TSP Algorithms.h` file contains the implementation of all the algorithms, while `main.cpp` serves as the entry point for running the program.

## Usage

1. Clone the repository to your local machine.
2. Navigate to the project directory.
3. Compile the code:
   - To run the main solver:
     ```bash
     g++ main.cpp
     ```
   - To compare different algorithms:
     ```bash
     g++ test.cpp
     ```
4. Run the executable to solve the TSP for specific instances or generate random graphs for testing.

## Dependencies

- C++11 standard library

## Contributors

- Joshua Balch - [@joshrbalch](https://github.com/joshrbalch)

## License

This project is licensed under the MIT License. See the LICENSE file for details.
