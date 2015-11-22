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

#define POPULATION_SIZE     50
#define GENERATIONS         100
#define VISUAL              true


int mainLoop();
double getTimeElapsed();
double getAngleBetween(btVector3 v1, btVector3 v2);

double values[VALUES_SIZE];
double fitness;

long int time_begin = 0;



// Fitness
class MiExperimentoFitness : public GaFitnessOperation {
    
public:
    
    virtual float GACALL operator ()(const GaChromosome* chromosome) const;
    
    virtual GaParameters* GACALL MakeParameters() const { return NULL; }
    
    virtual bool GACALL CheckParameters(const GaParameters& parameters) const { return true; }
};

// Observer
class MiExperimentoObserver : public GaObserverAdapter {
    
public:
    
    virtual void GACALL NewBestChromosome(const GaChromosome& newChromosome, const GaAlgorithm& algorithm);
    
    virtual void GACALL EvolutionStateChanged(GaAlgorithmState newState, const GaAlgorithm& algorithm);
    
    virtual void GACALL StatisticUpdate(const GaStatistics& statistics, const GaAlgorithm& algorithm);
    
};

// Fitness

float MiExperimentoFitness::operator ()(const GaChromosome* chromosome) const {
    const std::vector<double>& vals = dynamic_cast<const GaMVArithmeticChromosome<double>*>(chromosome)->GetCode();
    
    float fit = PassiveWalkerExperiment::getFitness(vals);
//    cout << "Fitness calculado: " << fit << endl;
    return fit;
}

// Observer

void MiExperimentoObserver::NewBestChromosome(const GaChromosome& newChromosome, const GaAlgorithm& algorithm) {
    const std::vector<double>& vals = dynamic_cast<const GaMVArithmeticChromosome<double>*>( &newChromosome )->GetCode();
    cout << "New chromosome found:" << endl;
    for(int i = 0; i < vals.size(); i++){
        cout << vals[i] << ", ";
        values[i] = vals[i];
    }
    fitness = newChromosome.GetFitness();

    cout << endl << "Fitness: " << fitness << endl;
    cout << endl << "Generation: " << algorithm.GetAlgorithmStatistics().GetCurrentGeneration() << endl;
}

void MiExperimentoObserver::EvolutionStateChanged(GaAlgorithmState newState, const GaAlgorithm& algorithm) {
    if( newState == GAS_RUNNING )
        cout << "Start\n";
    else if( newState == GAS_CRITERIA_STOPPED )
        cout << "End";
}

void MiExperimentoObserver::StatisticUpdate(const Common::GaStatistics &statistics, const Algorithm::GaAlgorithm &algorithm) {
    int gen = statistics.GetCurrentGeneration();
    if (gen % 50 == 0) {
        cout << "Generation: " << gen << endl;
    }
//    algorithm.GetPopulation(statistics.GetCurrentGeneration()).GetBestChromosomes( &i, 0, 1 );
//    GaChromosomePtr bestChromo = algorithm.GetPopulation(statistics.GetCurrentGeneration()).GetAt( i ).GetChromosome();
//    const std::vector<double>& vals = dynamic_cast<const GaMVArithmeticChromosome<double>*>( &(*bestChromo) )->GetCode();
    GaChromosomePtr bestChromo;
    for (int i = 0; i < POPULATION_SIZE; i++) {
        bestChromo = algorithm.GetPopulation(statistics.GetCurrentGeneration()).GetAt(i);
        const std::vector<double>& vals = dynamic_cast<const GaMVArithmeticChromosome<double>*>( &(*bestChromo) )->GetCode();
        storeGenerationInfo("output.dat", statistics.GetCurrentGeneration(), bestChromo->GetFitness(), vals, VALUES_SIZE);
    }
}

int mainLoop(char* executablePath) {
    struct timeval before;
    gettimeofday(&before, NULL);
    time_begin = before.tv_sec * 1000 + before.tv_usec / 1000;
    
    cout << "Starting GA runloop..." << endl;
    GaInitialize();
    
    GaValueIntervalBounds<double> amplitudeLower(1, 25);
    GaValueIntervalBounds<double> amplitudeUpper(1, 55);
    GaValueIntervalBounds<double> frequency(0.01, 3);
    GaValueIntervalBounds<double> phase(-SIMD_PI, SIMD_PI);
    GaValueIntervalBounds<double> independentTerm(-5, 5);
    
    GaIntervalValueSet<double> amplitudeLowerValueSet(amplitudeLower, amplitudeLower, GaGlobalRandomDoubleGenerator, false);
    GaIntervalValueSet<double> amplitudeUpperValueSet(amplitudeUpper, amplitudeUpper, GaGlobalRandomDoubleGenerator, false);
    GaIntervalValueSet<double> frequencyValueSet(frequency, frequency, GaGlobalRandomDoubleGenerator, false);
    GaIntervalValueSet<double> phaseValueSet(phase, phase, GaGlobalRandomDoubleGenerator, false);
    GaIntervalValueSet<double> independentTermValueSet(independentTerm, independentTerm, GaGlobalRandomDoubleGenerator, false);

#if GENERIC
    GaIntervalValueSet<double> *multiValueSet[VALUES_SIZE] = {
        &amplitudeLowerValueSet, &amplitudeLowerValueSet, &frequencyValueSet, &frequencyValueSet, &phaseValueSet, &independentTermValueSet,
        &amplitudeUpperValueSet, &amplitudeUpperValueSet, &frequencyValueSet, &frequencyValueSet, &phaseValueSet, &independentTermValueSet
    };
#elif FOURIER
    GaIntervalValueSet<double> *multiValueSet[VALUES_SIZE] = {
        &amplitudeLowerValueSet, &amplitudeUpperValueSet, &amplitudeLowerValueSet, &amplitudeUpperValueSet, &frequencyValueSet, &phaseValueSet, &independentTermValueSet,
        &amplitudeLowerValueSet, &amplitudeUpperValueSet, &amplitudeLowerValueSet, &amplitudeUpperValueSet, &frequencyValueSet, &phaseValueSet, &independentTermValueSet
    };
#else
    GaIntervalValueSet<double> *multiValueSet[VALUES_SIZE] = {
        &amplitudeLowerValueSet, &frequencyValueSet, &frequencyValueSet, &phaseValueSet, &independentTermValueSet,
        &amplitudeUpperValueSet, &frequencyValueSet, &frequencyValueSet, &phaseValueSet, &independentTermValueSet
    };
#endif

    
    // CHROMOSOME PARAMETERS
    double  mutationProbability = 0.1;
    int     numOfMutatedValues = 3;
    bool    onlyAcceptImprovingMutations = false;
    double  crossoverProbability = 0.7;
    int     crossoverPoints = 2;
//    GaChromosomeParams* chromosomeParams = new GaChromosomeParams(mutationProbability,
//                                        numOfMutatedValues,
//                                        onlyAcceptImprovingMutations,
//                                        crossoverProbability,
//                                        crossoverPoints);
    
    GaChromosomeParams* chromosomeParams = new GaChromosomeParams( 0.08F, 2, false, 0.8F, 4 );
    
    //CHROMOSOME CONFIGURATION BLOCK (CCB)
    GaCrossoverOperation*   crossoverMethod = GaCrossoverCatalogue::Instance().GetEntryData("GaMultiValueCrossover");
    GaMutationOperation*    mutationOperation = GaMutationCatalogue::Instance().GetEntryData("GaFlipMutation");
    GaFitnessOperation*     fitnessCalculator = new MiExperimentoFitness();
    GaFitnessComparator* 	fitnessComparator = GaFitnessComparatorCatalogue::Instance().GetEntryData("GaMaxFitnessComparator");
    GaChromosomeDomainBlock<double>* _ccb = new GaChromosomeDomainBlock<double>(
                        (GaValueSet<double>**)(multiValueSet),
                        VALUES_SIZE,
                        crossoverMethod,
                        mutationOperation,
                        fitnessCalculator,
                        fitnessComparator,
                        chromosomeParams);
    
    
    
    // Used as prototype to initilize other chromosomes
    GaMVArithmeticChromosome<double> chromosomePrototype(VALUES_SIZE, _ccb);
    
    
    // POPULATION PARAMETERS
    int 	populationSize = POPULATION_SIZE;
    bool    resizablePopulation = false;
    bool    sortedPopulation = false;
    bool    scaledValueFitness = false;
    int     bestChromosomesToTrack = 5;
    int     worstChromosomesToTrack = 5;
    GaPopulationParameters populationParams(populationSize,
                                            resizablePopulation,
                                            sortedPopulation,
                                            scaledValueFitness,
                                            bestChromosomesToTrack,
                                            worstChromosomesToTrack);
    
    int selectionSize = 50;
    bool duplicates = false;
    
    Population::SelectionOperations::GaSelectRandomBestParams selectParams(30, false, 40);
    
    int replacementSize = 10;
    int bestChromosomesThatRemain = 1;
    Population::ReplacementOperations::GaReplaceElitismParams replaceParams(replacementSize,
                                                                            bestChromosomesThatRemain);
    
    
    int numberOfOffsprings = 3;
    int checkForDuplicates = false;
    GaCouplingParams couplingParams(numberOfOffsprings, checkForDuplicates);
    
    GaPopulationConfiguration* populationConfiguration = new GaPopulationConfiguration(
                                    populationParams,
                                    &_ccb->GetFitnessComparator(),
                                    GaSelectionCatalogue::Instance().GetEntryData("GaSelectRandom"),
                                    &selectParams,
                                    GaReplacementCatalogue::Instance().GetEntryData("GaReplaceWorst"),
                                    &replaceParams,
                                    GaCouplingCatalogue::Instance().GetEntryData("GaSimpleCoupling"),
                                    &couplingParams,
                                    NULL,
                                    NULL);
    
    GaPopulation* population = new GaPopulation(&chromosomePrototype,
                                                 populationConfiguration);
    
    
    int numberOfWorkers = 1;
    GaMultithreadingAlgorithmParams algParam(numberOfWorkers);
    Algorithm::SimpleAlgorithms::GaIncrementalAlgorithm* algorithm = new Algorithm::SimpleAlgorithms::GaIncrementalAlgorithm( population, algParam );
    
    
    GaStopCriteria* criteria = GaStopCriteriaCatalogue::Instance().GetEntryData("GaGenerationCriteria");
    
    int numberOfGenerations = GENERATIONS;
    Algorithm::StopCriterias::GaGenerationCriteriaParams critParam(numberOfGenerations);
    algorithm->SetStopCriteria(criteria, &critParam);
    
    // subscribe observer
    algorithm->SubscribeObserver(new MiExperimentoObserver());
    algorithm->StartSolving(false);
    algorithm->WaitForThreads();
    
    GaFinalize();
    
    
    cout << endl << "Mejor cromosoma encontrado:  ";
    for(int i = 0; i < VALUES_SIZE; i++){
        cout << values[i] << ",";
    }
    cout << endl << "Fitness: " << fitness;
    cout << "\n Tiempo transcurrido:  ";
    cout << getTimeElapsed() / 1000.0;
    cout << " segundos ";
    
    updateResultFiles(std::string(executablePath), fitness, values, VALUES_SIZE, getTimeElapsed());
    return 0;
}


double getTimeElapsed(){
    struct timeval after;
    gettimeofday(&after, NULL);
    
    return (after.tv_sec * 1000 + after.tv_usec / 1000) - time_begin;
}

// This objective function tries to maximize the occurance of the first and
// fourth alleles.  It tries to put the first allele in the even elements and
// the fourth allele in the odd elements.

float
Objective1(GAGenome& g)
{
    GARealGenome& genome = (GARealGenome&)g;
    float value=0.0;
    for(int i=0; i<genome.length(); i++){
        if(i%2 == 0 && genome.gene(i) == genome.alleleset().allele(0))
            value += 1.0;
        if(i%2 != 0 && genome.gene(i) == genome.alleleset().allele(3))
            value += 1.0;
    }
    return value;
}


// This objective function tries to generate a straight - it gives higher score
// to a genome whose elements descend in value.  If two genomes both have
// elements in strictly descending order, they get the same score regardless
// of their values.

float
Objective2(GAGenome& g)
{
    GARealGenome& genome = (GARealGenome&)g;
    float value=0.0;
    for(int i=1; i<genome.length(); i++)
        if(genome.gene(i) < genome.gene(i-1)) value += 1.0;
    return value;
}


// This objective function generates a straight by giving higher score to a
// genome whose elements ascend in value.

float
Objective3(GAGenome& g)
{
    GARealGenome& genome = (GARealGenome&)g;
    float value=0.0;
    for(int i=1; i<genome.length(); i++)
        if(genome.gene(i) > genome.gene(i-1)) value += 1.0;
    return value;
}


// This objective tries to maximize each element in the genome.

float
Objective4(GAGenome& g)
{
    GARealGenome& genome = (GARealGenome&)g;
    static double arr[] = { -20.8932, 9.77636, 0.91726, 0.180875, 1.95841, -6.66473, -7.68414, 105.134, 0.517725, 0.491385 };
    for(int i=0; i < genome.length(); i++)
        arr[i] = genome.gene(i);
    std::vector<double> vals(arr, arr + sizeof(arr) / sizeof(arr[0]));
    return PassiveWalkerExperiment::getFitness(vals);
}

int main(int argc,char* argv[]) {
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
    alleles4.add(-60,60);
    alleles4.add(0.01, 10);
    alleles4.add(0.01, 10);
    alleles4.add(-SIMD_PI, SIMD_PI);
    alleles4.add(-10,10);
    alleles4.add(-30, -30);
    alleles4.add(0.01, 10);
    alleles4.add(0.01, 10);
    alleles4.add(-SIMD_PI, SIMD_PI);
    alleles4.add(-10,10);
    GARealGenome genome4(alleles4, Objective4);
    
    
    // Now that we have the genomes, create a parameter list that will be used for
    // all of the genetic algorithms and all of the genomes.
    
    GAParameterList params;
    GASteadyStateGA::registerDefaultParameters(params);
    params.set(gaNnGenerations, 1000);
    params.set(gaNpopulationSize, 110);
    params.set(gaNscoreFrequency, 1);
    // generation  TAB  mean  TAB  max  TAB  min  TAB deviation  TAB  diversity NEWLINE
    params.set(gaNselectScores, (int)GAStatistics::AllScores);
    params.set(gaNflushFrequency, 1);
    params.parse(argc, argv, gaFalse);
    
    GASteadyStateGA ga4(genome4);
    ga4.parameters(params);
    ga4.set(gaNscoreFilename, "bog4.dat");
    cout << "\nrunning ga number 4 (maximize each gene)..." << endl;
    ga4.evolve();
    cout << "the ga generated:\n" << ga4.statistics().bestIndividual() << endl;
    
    GARealGenome& genome = (GARealGenome&)ga4.statistics().bestIndividual();
    
    static double arr[] = { -20.8932, 9.77636, 0.91726, 0.180875, 1.95841, -6.66473, -7.68414, 105.134, 0.517725, 0.491385 };
    for(int i=0; i < genome.length(); i++)
        arr[i] = genome.gene(i);
    std::vector<double> vals(arr, arr + sizeof(arr) / sizeof(arr[0]));
    
    
    if(VISUAL) {
//        BasicDemo* bd = new BasicDemo();
//        bd->initPhysics();
        PassiveWalkerExperiment* experiment = PassiveWalkerExperiment::getInstance();
        WalkerBody* body = experiment->selectedBody;
        experiment->setCameraDistance(btScalar(5.));
        experiment->setCameraUp(btVector3(0, 15, 0));
        std::string exePath(argv[0]);
//        std::vector<double> vals = loadPreviousParams(exePath);
        
//        static const double arr[] = { -20.8932, 9.77636, 0.91726, 0.180875, 1.95841, -6.66473, -7.68414, 105.134, 0.517725, 0.491385, 1.70121, -3.30518 };
//        std::vector<double> vals(arr, arr + sizeof(arr) / sizeof(arr[0]));
        
        for (int i = 0; i < vals.size(); i++) {
            std::cout << "Values: " << vals[i] << std::endl;
        }
//        const std::vector<double> arr = {10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10};
//        const std::vector<double> arr = {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1};
        body->setActuatorValues(vals);
        return glutmain(argc, argv, 800, 600, "Experiment",experiment);
//        return glutmain(argc, argv, 800, 600, "BasicDemo",bd);
    } else {
        clearFile("output.dat");
        return mainLoop(argv[0]);
    }
}
