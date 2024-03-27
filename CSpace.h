#pragma once
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>

using namespace std;

class CSpace {
public:
    int type;
    string name;

    // Constructor
    CSpace(int t, string& n) : type(t), name(n) {}

    virtual ~CSpace(){}
};




// Function to read data from degrees.txt and populate the spaces vector
vector<CSpace*> readSpacesFromFile(const string& filename) {
    vector<CSpace*> spaces;
    ifstream file(filename);
    if (!file.is_open()) {
        cerr << "Error opening file: " << filename << endl;
        return spaces;
    }

    int type;
    string name;
    string line;
    while (file >> type) {
        getline(file >> ws, name);
        // cout << "Read space: " << type << " " << name << endl; // Print out the space being read
        CSpace* space = new CSpace(type, name);
        spaces.push_back(space);
    }
    file.close();
    return spaces;
}
