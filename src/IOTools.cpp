//
//  IOTools.cpp
//  GAv2
//
//  Created by Enzo Altamiranda G on 07.09.15.
//  Copyright (c) 2015 Enzo Altamiranda G. All rights reserved.
//

#include <stdlib.h>
#include <iostream>
#include <iomanip>
#include <string>
#include <fstream>
#include <vector>
#include <sys/stat.h>
#include <unistd.h>
#include "IOTools.h"
#include <math.h>

using namespace std;

mutex IOTools::lock;
ofstream IOTools::fifo;


void IOTools::sendDataToPlotServer(FitnessComponents components) {
    if (!DATA_PLOTTING_ACTIVE) {
        return;
    }
    IOTools::lock.lock();
    if (!IOTools::fifo.is_open()) {
        IOTools::openFifo();
    }
    IOTools::fifo.write(reinterpret_cast<char*>(&components), sizeof(FitnessComponents));
    IOTools::fifo.flush();
    if ((IOTools::fifo.rdstate() & ofstream::failbit) != 0) {
        printf("There was an error when sending data to plot server\n");
        printf("Exiting...\n");
        exit(-1);
    }
    IOTools::lock.unlock();
}

void IOTools::openFifo() {
    umask(0);
    int result = mkfifo(FIFO_PATHNAME, 0777);
    if (result == -1) {
        printf("There was an error when CREATING the FIFO pipe\n");
        printf("Errno: %d\n", errno);
        exit(-1);
    }
    
    printf("Opening FIFO for writing...\n");
    printf("Blocking until server opens FIFO for reading...\n");
    fifo.open(FIFO_PATHNAME, std::ofstream::out | std::ofstream::trunc);
    if (!fifo.is_open()) {
        printf("There was an error when OPENING the FIFO.\n");
        exit(-1);
    }
}

string getResultsDirPath(string executablePath) {
    int match = executablePath.rfind("/bin");
    string resultsDirPath = executablePath.substr(0, match);
    resultsDirPath.append("/results");
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
    cout << "Storing results in: " << resultsDirPath << endl;
    storeInfo(resultsDirPath, fitness, params, paramSize);
}

void storeOvitoLine(int numberOfLines, int label) {
    string resultsDirPath = OVITO_PATH;
    
    ofstream file(resultsDirPath, std::ios::app);
    if (file.good()) {
        file << fixed << numberOfLines << endl;
        file << fixed << label << endl;
    } else {
        cout << "results not stored." << endl;
    }
    file.close();
}

void storeOvitoLineValues(btVector3 position, btQuaternion orientation, double ratio, double height) {
    string resultsDirPath = OVITO_PATH;
    
    ofstream file(resultsDirPath, std::ios::app);
    if (file.good()) {
        file << fixed << setprecision(5) << position.x() << "\t" << position.y() << "\t" << position.z() << "\t" << orientation.x() << "\t" << orientation.y() << "\t" << orientation.z() << "\t" << orientation.w() << "\t" << ratio << "\t" << height << endl;
    } else {
        cout << "results not stored." << endl;
    }
    file.close();
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

void storeGenerationInfo(string filename, int generation, double fitness, const std::vector<double>& params, int paramSize) {
    ofstream file(filename, ofstream::app);
    if (file.good()) {
        file << generation << "\t";
        file << setprecision(5) << fitness << "\t";
        for (int i = 0; i < paramSize; i++) {
            file << setprecision(5) << params[i];
            if(i < paramSize -1) {
                file << "\t";
            }
        }
        file << endl;
    } else {
        cout << "Results not stored." << endl;
    }
    file.close();
}

void clearFile(string filename) {
    ofstream file(filename);
    if (file.good()) {
        file << "";
        cout << "File cleared." << endl;
    } else {
        cout << "File not cleared" << endl;
    }
}
