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


#define VALUES_SIZE         12
#define POPULATION_SIZE     20
#define GENERATIONS         500
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
    int numberOfValueSets = VALUES_SIZE;
    
    cout << "Starting GA runloop..." << endl;
    
    GaInitialize();
    
    GaValueIntervalBounds<double> amplitude(-200, 200);
    GaValueIntervalBounds<double> frequency(0.1, 2);
    GaValueIntervalBounds<double> phase(0, SIMD_2_PI);
    GaValueIntervalBounds<double> independentTerm(-5, 5);
    
    GaIntervalValueSet<double> amplitudeValueSet(amplitude, amplitude, GaGlobalRandomDoubleGenerator, false);
    GaIntervalValueSet<double> frequencyValueSet(frequency, frequency, GaGlobalRandomDoubleGenerator, false);
    GaIntervalValueSet<double> phaseValueSet(phase, phase, GaGlobalRandomDoubleGenerator, false);
    GaIntervalValueSet<double> independentTermValueSet(independentTerm, independentTerm, GaGlobalRandomDoubleGenerator, false);
    
//    // Generic actuator
    GaIntervalValueSet<double> *multiValueSet[VALUES_SIZE] = {
        &amplitudeValueSet, &amplitudeValueSet, &frequencyValueSet, &frequencyValueSet, &phaseValueSet, &independentTermValueSet,
        &amplitudeValueSet, &amplitudeValueSet, &frequencyValueSet, &frequencyValueSet, &phaseValueSet, &independentTermValueSet,
    };
//    // Fourier actuator
//    GaIntervalValueSet<double> *multiValueSet[VALUES_SIZE] = {
//        &amplitudeValueSet, &amplitudeValueSet, &amplitudeValueSet, &amplitudeValueSet, &frequencyValueSet, &phaseValueSet, &independentTermValueSet,
//        &amplitudeValueSet, &amplitudeValueSet, &amplitudeValueSet, &amplitudeValueSet, &frequencyValueSet, &phaseValueSet, &independentTermValueSet,
//    };
    // Double frec cos actuator
//    GaIntervalValueSet<double> *multiValueSet[VALUES_SIZE] = {
//        &amplitudeValueSet, &frequencyValueSet, &frequencyValueSet, &phaseValueSet, &independentTermValueSet,
//        &amplitudeValueSet, &frequencyValueSet, &frequencyValueSet, &phaseValueSet, &independentTermValueSet
//    };
    
    
    // CHROMOSOME PARAMETERS
    double  mutationProbability = 0.5;
    int     numOfMutatedValues = VALUES_SIZE / 2;
    bool    onlyAcceptImprovingMutations = false;
    double  crossoverProbability = 0.3;
    int     crossoverPoints = VALUES_SIZE / 2;
    GaChromosomeParams* chromosomeParams = new GaChromosomeParams(mutationProbability,
                                        numOfMutatedValues,
                                        onlyAcceptImprovingMutations,
                                        crossoverProbability,
                                        crossoverPoints);
    
    //CHROMOSOME CONFIGURATION BLOCK (CCB)
    GaCrossoverOperation*   crossoverMethod = GaCrossoverCatalogue::Instance().GetEntryData("GaMultiValueCrossover");
    GaMutationOperation*    mutationOperation = GaMutationCatalogue::Instance().GetEntryData("GaFlipMutation");
    GaFitnessOperation*     fitnessCalculator = new MiExperimentoFitness();
    GaFitnessComparator* 	fitnessComparator = GaFitnessComparatorCatalogue::Instance().GetEntryData("GaMaxFitnessComparator");
    GaChromosomeDomainBlock<double>* _ccb = new GaChromosomeDomainBlock<double>(
                        (GaValueSet<double>**)(&multiValueSet),
                        numberOfValueSets,
                        crossoverMethod,
                        mutationOperation,
                        fitnessCalculator,
                        fitnessComparator,
                        chromosomeParams);
    
    
    
    // Used as prototype to initilize other chromosomes
    GaMVArithmeticChromosome<double> chromosomePrototype(numberOfValueSets, _ccb);
    
    
    // POPULATION PARAMETERS
    int 	populationSize = POPULATION_SIZE;
    bool    resizablePopulation = false;
    bool    sortedPopulation = false;
    bool    scaledValueFitness = false;
    int     bestChromosomesToTrack = 1;
    int     worstChromosomesToTrack = 0;
    GaPopulationParameters populationParams(populationSize,
                                            resizablePopulation,
                                            sortedPopulation,
                                            scaledValueFitness,
                                            bestChromosomesToTrack,
                                            worstChromosomesToTrack);
    
    int selectionSize = 20;
    bool duplicates = false;
    int groupSize = 20;
    Population::SelectionOperations::GaSelectRandomBestParams selectParams(selectionSize, false, groupSize);
    
    int replacementSize = 20;
    int bestChromosomesThatRemain = 1;
    Population::ReplacementOperations::GaReplaceElitismParams replaceParams(replacementSize,
                                                                            bestChromosomesThatRemain);
    
    
    int numberOfOffsprings = 11;
    int checkForDuplicates = false;
    GaCouplingParams couplingParams(numberOfOffsprings, checkForDuplicates);
    
    GaPopulationConfiguration* populationConfiguration = new GaPopulationConfiguration(
                                    populationParams,
                                    &_ccb->GetFitnessComparator(),
                                    GaSelectionCatalogue::Instance().GetEntryData("GaSelectRouletteWheel"),
                                    &selectParams,
                                    GaReplacementCatalogue::Instance().GetEntryData("GaReplaceRandom"),
                                    &replaceParams,
                                    GaCouplingCatalogue::Instance().GetEntryData("GaSimpleCoupling"),
                                    &couplingParams,
                                    NULL,
                                    NULL);
    
    GaPopulation* population = new GaPopulation(&chromosomePrototype,
                                                 populationConfiguration);
    
    
    int numberOfWorkers = 8;
    GaMultithreadingAlgorithmParams algParam(numberOfWorkers);
    Algorithm::SimpleAlgorithms::GaIncrementalAlgorithm* algorithm = new Algorithm::SimpleAlgorithms::GaIncrementalAlgorithm( population, algParam);
    
    
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

int main(int argc,char* argv[]) {
    if(VISUAL) {
        PassiveWalkerExperiment* experiment = PassiveWalkerExperiment::getInstance();
        experiment->initPhysics();
        experiment->setCameraDistance(btScalar(5.));
        experiment->setCameraUp(btVector3(0, 15, 0));
        std::string exePath(argv[0]);
        std::vector<double> vals = loadPreviousParams(exePath);
        experiment->setBodyActuatorValues(vals);
        return glutmain(argc, argv, 800, 600, "Experiment",experiment);
    } else {
        clearFile("output.dat");
        return mainLoop(argv[0]);
    }
}
