#pragma once
#include "CSpace.h"

class CAssessmentSpace : public CSpace
{
protected:
	int motivationalCost;
	int successScore;
	int year;

	// constructor
	CAssessmentSpace(int t, const std::string& n, int mCost, int mScore, int yr)
		: CSpace(t, n), motivationalCost(mCost), successScore(sScore), year(yr) {}

};

//vector<CAssessmentSpace*> readSpacesFromFile(const string& filename) {
//    vector<CAssessmentSpace*> aSpaces;
//    ifstream file(filename);
//    if (!file.is_open()) {
//        cerr << "Error opening file: " << filename << endl;
//        return aSpaces;
//    }
//
//    int type;
//    string name;
//    string line;
//    while (file >> type) {
//        getline(file >> ws, name);
//        // cout << "Read space: " << type << " " << name << endl; // Print out the space being read
//        CAssessmentSpace* aSpace = new CAssessmentSpace(type);
//        aSpaces.push_back(aSpace);
//    }
//    file.close();
//    return aSpaces;