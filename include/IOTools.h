//
//  IOTools.h
//  GAv2
//
//  Created by Enzo Altamiranda G on 07.09.15.
//  Copyright (c) 2015 Enzo Altamiranda G. All rights reserved.
//

#ifndef __GAv2__IOTools__
#define __GAv2__IOTools__

#include <stdio.h>
#include <string>
#include <vector>
#include <fstream>
#include <mutex>


#define     FIFO_PATHNAME           "/tmp/passive_walker_exp.fifo"
#define     DATA_PLOTTING_ACTIVE    0


using std::string;
using std::vector;

typedef struct {
    double height;
    double direction;
    double speed;
} FitnessComponents;

class IOTools {
    
public:    
    static void sendDataToPlotServer(FitnessComponents components);

private:
    static std::mutex lock;

    static std::ofstream fifo;
    
    static void openFifo();
    
};

string getResultsDirPath(string executablePath);

double getBestFitness(string resultsDirPath);

void updateResultFiles(string executablePath, double fitness, double params[], int paramSize, int miliTime);

void storeNewBestFitness(string resultsDirPath, double fitness, double params[], int paramSize);

void storeLatestResults(string resultsDirPath, double fitness, double params[], int paramSize);

void storeInfo(string filename, double fitness, double params[], int paramSize);

vector<double> loadPreviousParams(string executablePath);


#endif /* defined(__GAv2__IOTools__) */
