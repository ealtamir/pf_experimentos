//
//  IOTools.cpp
//  GAv2
//
//  Created by Enzo Altamiranda G on 07.09.15.
//  Copyright (c) 2015 Enzo Altamiranda G. All rights reserved.
//

#include "IOTools.h"
#include <stdlib.h>
#include <iostream>
#include <iomanip>
#include <string>
#include <fstream>
#include <vector>

using namespace std;

string getResultsDirPath(string executablePath) {
    int match = executablePath.rfind("/bin");
    string resultsDirPath = executablePath.substr(0, match);
    resultsDirPath.append("/results");
    cout << "Results dir: " << resultsDirPath << endl;
    return resultsDirPath;
}

double getBestFitness(string resultsDirPath) {
    resultsDirPath.append("/best_fitness.txt");
    ifstream fitnessFile(resultsDirPath);
    string line;
    double fitness = -10;
    if (fitnessFile.good()) {
        getline(fitnessFile, line);
        fitness = stof(line);
        cout << "loaded fitness: " << fitness << endl;
    }
    fitnessFile.close();
    return fitness;
}

vector<double> loadPreviousParams(string executablePath) {
    vector<double> params;
    string resultsDirPath = getResultsDirPath(executablePath);
    ifstream latestResults(resultsDirPath.append("/latest_result.txt"));
    double value;
    string line;
    getline(latestResults, line);
    while (getline(latestResults, line)) {
        params.push_back(stof(line));
    }
    cout << "params loaded..." << endl;
    return params;
}

void updateResultFiles(string executablePath, double fitness, double params[], int paramSize, int miliTime) {
    string resultsDirPath = getResultsDirPath(executablePath);
    double bestFitness = getBestFitness(resultsDirPath);
    if (fitness == -10) {
        cout << "Not fitness file found" << endl;
    }
    if (bestFitness < fitness) {
        storeNewBestFitness(resultsDirPath, fitness, params, paramSize);
    }
    storeLatestResults(resultsDirPath, fitness, params, paramSize);
}


void storeNewBestFitness(string resultsDirPath, double fitness, double params[], int paramSize) {
    resultsDirPath.append("/fitness_file.txt");
    storeInfo(resultsDirPath, fitness, params, paramSize);
}

void storeLatestResults(string resultsDirPath, double fitness, double params[], int paramSize) {
    resultsDirPath.append("/latest_result.txt");
    cout << "storing results" << endl;
    storeInfo(resultsDirPath, fitness, params, paramSize);
}

void storeInfo(string filename, double fitness, double params[], int paramSize) {
    ofstream file(filename);
    if (file.good()) {
        file << fixed << setprecision(5) << fitness << endl;
        for (int i = 0; i < paramSize; i++) {
            file << fixed << setprecision(5) << params[i] << endl;
        }
    } else {
        cout << "results not stored." << endl;
    }
    file.close();
}
