#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>

using namespace std;

class fInput {
    public:
    vector<vector<int>> graph;
    int numNodes;

    fInput(string filename) {
        ifstream file(filename);
        string line;
        int num;
        vector<int> row;
        numNodes = 0;

        while(getline(file, line)) {
            istringstream ss(line);
            while(ss >> num) {
                row.push_back(num);
            }
            graph.push_back(row);
            row.clear();
            numNodes++;
        }
    }
};
