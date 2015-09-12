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

using std::string;
using std::vector;

string getResultsDirPath(string executablePath);

double getBestFitness(string resultsDirPath);

void updateResultFiles(string executablePath, double fitness, double params[], int paramSize, int miliTime);

void storeNewBestFitness(string resultsDirPath, double fitness, double params[], int paramSize);

void storeLatestResults(string resultsDirPath, double fitness, double params[], int paramSize);

void storeInfo(string filename, double fitness, double params[], int paramSize);

vector<double> loadPreviousParams(string executablePath);


#endif /* defined(__GAv2__IOTools__) */
