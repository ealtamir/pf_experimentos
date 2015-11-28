// GA libraries
#include "Initialization.h"
#include "Algorithm.h"
#include "IncrementalAlgorithm.h"

#include "Population.h"
#include "Chromosome.h"
#include "DomainChromosome.h"
#include "MultiValueChromosome.h"

#include "PopulationOperations.h"
#include "ChromosomeOperations.h"
#include "SelectionOperations.h"
#include "ReplacementOperations.h"
#include "CouplingOperations.h"
#include "MutationOperations.h"
#include "ScalingOperations.h"

#include "ValueSets.h"

#include "StopCriterias.h" 

// System libraries
#include <stdlib.h>
#include <vector>
#include <iostream>
#include <sys/time.h>

// PF includes
#include "Experiment.h"
#include "PassiveWalkerExperiment.h"
#include "IOTools.h"

#include "BasicDemo.h"

// NEW GA
#include <ga/ga.h>
#include <ga/GARealGenome.h>
#include <ga/GARealGenome.C>

#define POPULATION_SIZE             50
#define GENERATIONS                 100
#define GENOME_MUTATION             0.1
#define REPLACEMENT_PORCENTAGE      0.4
#define LAST_RESULTS                false


int mainLoop();
double getTimeElapsed();
double getAngleBetween(btVector3 v1, btVector3 v2);

double values[VALUES_SIZE];
double fitness;

long int time_begin = 0;

double getTimeElapsed(){
    struct timeval after;
    gettimeofday(&after, NULL);
    
    return (after.tv_sec * 1000 + after.tv_usec / 1000) - time_begin;
}

float
Objective4(GAGenome& g)
{
    GARealGenome& genome = (GARealGenome&)g;
    int size = 0;
#if FIRST_STEP_GENERIC
    size += 12;
#elif FIRST_STEP_FOURIER
    size += 14;
#elif FIRST_STEP_DOUBLE_COSINE
    size += 10;
#endif
    
#if GENERIC
    size += 12;
#elif FOURIER
    size += 14;
#elif DOUBLE_COSINE
    size += 10;
#endif

    double arr[size];
    for(int i=0; i < genome.length(); i++)
        arr[i] = genome.gene(i);
    std::vector<double> vals(arr, arr + sizeof(arr) / sizeof(arr[0]));
    return PassiveWalkerExperiment::getFitness(vals);
}

int main(int argc,char* argv[]) {
    if(!LAST_RESULTS){
        cout << "Example 21\n\n";
        cout << "This example shows various uses of the allele set object\n";
        cout << "in combination with the real number genome.\n\n"; cout.flush();
    
        // See if we've been given a seed to use (for testing purposes).  When you
        // specify a random seed, the evolution will be exactly the same each time
        // you use that seed number.
    
        unsigned int seed = 0;
        for(int ii=1; ii<argc; ii++) {
            if(strcmp(argv[ii++],"seed") == 0) {
                seed = atoi(argv[ii]);
            }
        }
    
        // This genome is created using an array of allele sets.  This means that each
        // element of the genome will assume a value in its corresponding allele set.
        // For example, since the first allele set is [0,10], the first element of the
        // genome will be in [0,10].  Notice that you can add allele sets in many other
        // ways than those shown.
    
        GARealAlleleSetArray alleles4;
#if FIRST_STEP_GENERIC
        alleles4.add(-60,60);
        alleles4.add(-60,60);
        alleles4.add(0.01, 10);
        alleles4.add(0.01, 10);
        alleles4.add(-SIMD_PI, SIMD_PI);
        alleles4.add(-10,10);
        alleles4.add(-30, -30);
        alleles4.add(-30, -30);
        alleles4.add(0.01, 10);
        alleles4.add(0.01, 10);
        alleles4.add(-SIMD_PI, SIMD_PI);
        alleles4.add(-10,10);
#elif FIRST_STEP_FOURIER
        alleles4.add(-60,60);
        alleles4.add(-60,60);
        alleles4.add(-60,60);
        alleles4.add(-60,60);
        alleles4.add(0.01, 10);
        alleles4.add(-SIMD_PI, SIMD_PI);
        alleles4.add(-10,10);
        alleles4.add(-30,30);
        alleles4.add(-30,30);
        alleles4.add(-30,30);
        alleles4.add(-30,30);
        alleles4.add(0.01, 10);
        alleles4.add(-SIMD_PI, SIMD_PI);
        alleles4.add(-10,10);
#elif FIRST_STEP_DOUBLE_COSINE
        alleles4.add(0, 40);
        alleles4.add(0.01, 10);
        alleles4.add(0.01, 10);
        alleles4.add(-SIMD_PI, SIMD_PI);
        alleles4.add(-10,10);
        alleles4.add(0, 30);
        alleles4.add(0.01, 10);
        alleles4.add(0.01, 10);
        alleles4.add(-SIMD_PI, SIMD_PI);
        alleles4.add(-10,10);
#endif
    
#if GENERIC
        alleles4.add(-60,60);
        alleles4.add(-60,60);
        alleles4.add(0.01, 10);
        alleles4.add(0.01, 10);
        alleles4.add(-SIMD_PI, SIMD_PI);
        alleles4.add(-10,10);
        alleles4.add(-30, -30);
        alleles4.add(-30, -30);
        alleles4.add(0.01, 10);
        alleles4.add(0.01, 10);
        alleles4.add(-SIMD_PI, SIMD_PI);
        alleles4.add(-10,10);
#elif FOURIER
        alleles4.add(-60,60);
        alleles4.add(-60,60);
        alleles4.add(-60,60);
        alleles4.add(-60,60);
        alleles4.add(0.01, 10);
        alleles4.add(-SIMD_PI, SIMD_PI);
        alleles4.add(-10,10);
        alleles4.add(-30,30);
        alleles4.add(-30,30);
        alleles4.add(-30,30);
        alleles4.add(-30,30);
        alleles4.add(0.01, 10);
        alleles4.add(-SIMD_PI, SIMD_PI);
        alleles4.add(-10,10);
#elif DOUBLE_COSINE
        alleles4.add(0, 40);
        alleles4.add(0.01, 10);
        alleles4.add(0.01, 10);
        alleles4.add(-SIMD_PI, SIMD_PI);
        alleles4.add(-10,10);
        alleles4.add(0, 30);
        alleles4.add(0.01, 10);
        alleles4.add(0.01, 10);
        alleles4.add(-SIMD_PI, SIMD_PI);
        alleles4.add(-10,10);
#endif
        GARealGenome genome4(alleles4, Objective4);
    
        // Now that we have the genomes, create a parameter list that will be used for
        // all of the genetic algorithms and all of the genomes.
    
        GAParameterList params;
        GASteadyStateGA::registerDefaultParameters(params);
        params.set(gaNnGenerations, GENERATIONS);
        params.set(gaNpopulationSize, POPULATION_SIZE);
        params.set(gaNscoreFrequency, 1);
        // generation  TAB  mean  TAB  max  TAB  min  TAB deviation  TAB  diversity NEWLINE
        params.set(gaNselectScores, (int)GAStatistics::AllScores);
        params.set(gaNflushFrequency, 1);
        params.set(gaNpMutation, GENOME_MUTATION);
        params.set(gaNrecordDiversity, gaTrue);
        params.parse(argc, argv, gaFalse);
    
        GASteadyStateGA ga4(genome4);
        ga4.parameters(params);
        ga4.pReplacement(REPLACEMENT_PORCENTAGE);
        ga4.set(gaNscoreFilename, "bog4.dat");
        cout << "\nrunning ga number 4 (maximize each gene)..." << endl;
        ga4.evolve();
        cout << "the ga generated:\n" << ga4.statistics().bestIndividual() << endl;
    
        GARealGenome& genome = (GARealGenome&)ga4.statistics().bestIndividual();
    
        static double arr[] = { 0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21 };
        for(int i=0; i < genome.length(); i++)
            arr[i] = genome.gene(i);
        std::vector<double> vals(arr, arr + sizeof(arr) / sizeof(arr[0]));
    
        PassiveWalkerExperiment* experiment = PassiveWalkerExperiment::getInstance();
        WalkerBody* body = experiment->selectedBody;
        experiment->setCameraDistance(btScalar(5.));
        experiment->setCameraUp(btVector3(0, 15, 0));
        std::string exePath(argv[0]);
     
        for (int i = 0; i < vals.size(); i++) {
            std::cout << "Values: " << vals[i] << std::endl;
        }
        
        updateResultFiles(exePath, genome.fitness(), &vals[0], 22, getTimeElapsed());
        body->setActuatorValues(vals);
        return glutmain(argc, argv, 800, 600, "Experiment", experiment);
    } else {
        PassiveWalkerExperiment* experiment = PassiveWalkerExperiment::getInstance();
        WalkerBody* body = experiment->selectedBody;
        experiment->setCameraDistance(btScalar(5.));
        experiment->setCameraUp(btVector3(0, 15, 0));
        
        std::string exePath(argv[0]);
        std::vector<double> vals = loadPreviousParams(exePath);
        body->setActuatorValues(vals);
        return glutmain(argc, argv, 800, 600, "Experiment", experiment);
    }
}
