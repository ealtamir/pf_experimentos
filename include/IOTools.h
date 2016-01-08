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
#include <BulletDynamics/btBulletDynamicsCommon.h>

#define     FIFO_PATHNAME           "/tmp/passive_walker_exp.fifo"
#define     DATA_PLOTTING_ACTIVE    0
#define     OVITO_PATH              "/Users/tomymehdi/itba/pf_experimentos/bin/Debug/ovito.xyz"



using std::string;
using std::vector;

typedef struct {
    double totalFitness;
    double dummy;
    double dummy2;
} FitnessComponents;

class IOTools {
    
public:    
    static void sendDataToPlotServer(FitnessComponents component);

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

void storeOvitoLine(int numberOfLines, int label);

void storeOvitoLineValues(btVector3 position, btQuaternion orientation);

void storeGenerationInfo(string filename, int generation, double fitness, const std::vector<double>& params, int paramSize);

void clearFile(string filename);

vector<double> loadPreviousParams(string executablePath);


#endif /* defined(__GAv2__IOTools__) */
