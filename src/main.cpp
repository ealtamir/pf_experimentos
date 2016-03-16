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


int mainLoop();
double getTimeElapsed();
double getAngleBetween(btVector3 v1, btVector3 v2);

double values[VALUES_SIZE+1];
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
    int size = ACTUATOR_SIZE;

    std::vector<double> vals;
    for(int i=0; i < genome.length(); i++) {
        vals.push_back(genome.gene(i));
    }
    float aux = PassiveWalkerExperiment::getFitness(vals);
//    cout << aux << endl;
    return aux;
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
        alleles4.add(-30,10);
        alleles4.add(0,30);
        alleles4.add(0.01, 10);
        alleles4.add(0.01, 10);
        alleles4.add(-SIMD_PI, SIMD_PI);
        alleles4.add(-10,10);
        alleles4.add(-60, 60);
        alleles4.add(-60, 60);
        alleles4.add(0.01, 10);
        alleles4.add(0.01, 10);
        alleles4.add(-SIMD_PI, SIMD_PI);
        alleles4.add(-10,10);
        
        alleles4.add(-30,30);
        alleles4.add(-30,30);
        alleles4.add(0.01, 10);
        alleles4.add(0.01, 10);
        alleles4.add(-SIMD_PI, SIMD_PI);
        alleles4.add(-10,10);
        alleles4.add(-60, 60);
        alleles4.add(-60, 60);
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
        alleles4.add(-25, 25);
        alleles4.add(0.1, 10);
        alleles4.add(0.1, 10);
        alleles4.add(-SIMD_PI, SIMD_PI);
        alleles4.add(-10,10);
        alleles4.add(-40, 40);
        alleles4.add(0.1, 10);
        alleles4.add(0.1, 10);
        alleles4.add(-SIMD_PI, SIMD_PI);
        alleles4.add(-10,10);
        alleles4.add(-25, 25);
        alleles4.add(0.1, 10);
        alleles4.add(0.1, 10);
        alleles4.add(-SIMD_PI, SIMD_PI);
        alleles4.add(-10,10);
        alleles4.add(-40, 40);
        alleles4.add(0.1, 10);
        alleles4.add(0.1, 10);
        alleles4.add(-SIMD_PI, SIMD_PI);
        alleles4.add(-10,10);
#endif
    
#if GENERIC
        alleles4.add(-30,30);
        alleles4.add(-30,30);
        alleles4.add(0.01, 10);
        alleles4.add(0.01, 10);
        alleles4.add(-SIMD_PI, SIMD_PI);
        alleles4.add(-10,10);
        alleles4.add(-60, 60);
        alleles4.add(-60, 60);
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
        alleles4.add(-100, 100);
        alleles4.add(0.1, 10);
        alleles4.add(0.1, 10);
        alleles4.add(-SIMD_PI, SIMD_PI);
        alleles4.add(-50,50);
        
        alleles4.add(-100, 100);
        alleles4.add(0.1, 10);
        alleles4.add(0.1, 10);
        alleles4.add(-SIMD_PI, SIMD_PI);
        alleles4.add(-100,100);

//        parámetros viejos
//        alleles4.add(-25, 25);
//        alleles4.add(0.1, 10);
//        alleles4.add(0.1, 10);
//        alleles4.add(-SIMD_PI, SIMD_PI);
//        alleles4.add(-10,10);
        
//        alleles4.add(-40, 40);
//        alleles4.add(0.1, 10);
//        alleles4.add(0.1, 10);
//        alleles4.add(-SIMD_PI, SIMD_PI);
//        alleles4.add(-10,10);
#elif EXTRA_FOURIER
        // Lower
        alleles4.add(-10, 10);
        alleles4.add(-60,60);
        alleles4.add(-60,60);
        alleles4.add(-60,60);
        alleles4.add(-60,60);
        alleles4.add(-60,60);
        alleles4.add(-60,60);
        alleles4.add(-60,60);
        alleles4.add(-60,60);
        alleles4.add(-60,60);
        alleles4.add(-60,60);
        alleles4.add(-60,60);
        alleles4.add(-60,60);
        alleles4.add(-60,60);
        alleles4.add(-60,60);
        alleles4.add(-60,60);
        alleles4.add(-60,60);
        alleles4.add(-60,60);
        alleles4.add(-60,60);
        alleles4.add(0.1, 2);
        alleles4.add(-SIMD_PI, SIMD_PI);

        // Upper
        alleles4.add(-10, 10);
        alleles4.add(-60,60);
        alleles4.add(-60,60);
        alleles4.add(-60,60);
        alleles4.add(-60,60);
        alleles4.add(-60,60);
        alleles4.add(-60,60);
        alleles4.add(-60,60);
        alleles4.add(-60,60);
        alleles4.add(-60,60);
        alleles4.add(-60,60);
        alleles4.add(-60,60);
        alleles4.add(-60,60);
        alleles4.add(-60,60);
        alleles4.add(-60,60);
        alleles4.add(-60,60);
        alleles4.add(-60,60);
        alleles4.add(-60,60);
        alleles4.add(-60,60);
        alleles4.add(0.1, 2);
        alleles4.add(-SIMD_PI, SIMD_PI);
#endif
#if RIEL
       alleles4.add(700, 1600);
#endif
        
        GARealGenome genome4(alleles4, Objective4);
        
        GARealGenome::FlipMutator(genome4, GENOME_MUTATION);
        
//        define name        full name                   short name  default value
//        
//        gaNminimaxi         minimaxi                    mm          int   gaDefMiniMaxi        = 1
//        gaNnGenerations     number_of_generations       ngen        int   gaDefNumGen          = 250
//        gaNpConvergence     convergence_percentage      pconv       float gaDefPConv           = 0.99
//        gaNnConvergence     generations_to_convergence  nconv       int   gaDefNConv           = 20
//        gaNpCrossover       crossover_probability       pcross      float gaDefPCross          = 0.9
//        gaNpMutation        mutation_probability        pmut        float gaDefPMut            = 0.01
//        gaNpopulationSize   population_size             popsize     int   gaDefPopSize         = 30
//        gaNnPopulations     number_of_populations       npop        int   gaDefNPop            = 10
//        gaNpReplacement     replacement_percentage      prepl       float gaDefPRepl           = 0.25
//        gaNnReplacement     replacement_number          nrepl       int   gaDefNRepl           = 5
//        gaNnBestGenomes     number_of_best              nbest       int   gaDefNumBestGenomes  = 1
//        gaNscoreFrequency   score_frequency             sfreq       int   gaDefScoreFrequency1 = 1
//        gaNflushFrequency   flush_frequency             ffreq       int   gaDefFlushFrequency  = 0
//        gaNscoreFilename    score_filename              sfile       char* gaDefScoreFilename   = "generations.dat"
//        gaNselectScores     select_scores               sscores     int   gaDefSelectScores    = GAStatistics::Maximum
//        gaNelitism          elitism                     el          GABoolean gaDefElitism     = gaTrue
//        gaNnOffspring       number_of_offspring         noffspr     int   gaDefNumOff          = 2
//        gaNrecordDiversity  record_diversity            recdiv      GABoolean gaDefDivFlag     = gaFalse
//        gaNpMigration       migration_percentage        pmig        float gaDefPMig            = 0.1
//        gaNnMigration       migration_number            nmig        int   gaDefNMig            = 5
    
        GAParameterList params;
        GASteadyStateGA::registerDefaultParameters(params);
        params.set(gaNnGenerations, GENERATIONS);
        params.set(gaNpopulationSize, POPULATION_SIZE);
        params.set(gaNpCrossover, 0.9);
        params.set(gaNpMutation, GENOME_MUTATION);
        params.set(gaNrecordDiversity, gaTrue);
        params.set(gaNelitism, gaFalse);
        
        params.set(gaNscoreFrequency, 1);
        params.set(gaNflushFrequency, 1);
        
        // generation  mean  max  min deviation  diversity
        params.set(gaNselectScores, (int)GAStatistics::AllScores);
        
        params.parse(argc, argv, gaFalse);
    
        GASteadyStateGA ga4(genome4);
        ga4.parameters(params);
        ga4.pReplacement(REPLACEMENT_PERCENTAGE);
        
        // Default is GARealGenome::UniformCrossover
//        ga4.crossover(GARealGenome::OnePointCrossover);
        ga4.crossover(GARealGenome::UniformCrossover);

//      GARankSelector
//      GARouletteWheelSelector
//      GATournamentSelector
//      GADSSelector
//      GASRSSelector
//      GAUniformSelector
//      http://lancet.mit.edu/galib-2.4/API.html#selection
//        ga4.selector(GATournamentSelector());
        ga4.selector(GARouletteWheelSelector());
        
        ga4.set(gaNscoreFilename, "bog4.dat");
        ga4.scaling(GANoScaling());
        
        cout << "\nrunning ga number 4 (maximize each gene)..." << endl;
        ga4.evolve();
        
        
        cout << "the ga generated:\n" << ga4.statistics().bestIndividual() << endl;
        GARealGenome& genome = (GARealGenome&) ga4.statistics().bestIndividual();
        cout << "fitness: " << genome.fitness() << endl;
        
        cout << "statistics: " << ga4.statistics() << endl;
    

        int size = ACTUATOR_SIZE + RIEL;

        std::vector<double> vals;        
//        double arr[size];
        for(int i=0; i < genome.length(); i++)
            vals.push_back(genome.gene(i));
    
        PassiveWalkerExperiment* experiment = PassiveWalkerExperiment::getInstance();
        WalkerBody* body = experiment->selectedBody;
        experiment->setCameraDistance(btScalar(5.));
        experiment->setCameraUp(btVector3(0, 15, 0));
        std::string exePath(argv[0]);
     
//        for (int i = 0; i < vals.size(); i++) {
//            std::cout << "Values: " << vals[i] << std::endl;
//        }
//        

        updateResultFiles(exePath, genome.fitness(), &vals[0], size, getTimeElapsed());
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
        experiment->setConstantRiel(vals.at(vals.size()-1));
        float aux = experiment->getFitness(vals);
        //cout << "fitness: " <<  aux << endl;
        /*for (int i = 0; i < vals.size(); i++) {
            std::cout << "Values: " << vals[i] << std::endl;
        }*/
        return glutmain(argc, argv, 800, 600, "Experiment", experiment);
    }
}
