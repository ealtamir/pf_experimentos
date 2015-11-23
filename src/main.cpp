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

#define POPULATION_SIZE     55
#define REPLACEMENT_PERCENTAGE 90
#define GENERATIONS         1000
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
#elif PARTIDA
    GaIntervalValueSet<double> *multiValueSet[VALUES_SIZE] = {
        &amplitudeLowerValueSet, &frequencyValueSet, &phaseValueSet, &independentTermValueSet,
        &amplitudeUpperValueSet, &frequencyValueSet, &phaseValueSet, &independentTermValueSet
    };
#else
    GaIntervalValueSet<double> *multiValueSet[VALUES_SIZE] = {
        &amplitudeLowerValueSet, &frequencyValueSet, &frequencyValueSet, &phaseValueSet, &independentTermValueSet,
        &amplitudeUpperValueSet, &frequencyValueSet, &frequencyValueSet, &phaseValueSet, &independentTermValueSet
    };
#endif

    
    // CHROMOSOME PARAMETERS
    double  mutationProbability = 0.8;
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
    
    int selectionSize = 250;
    bool duplicates = false;
    
    Population::SelectionOperations::GaSelectRandomBestParams selectParams(100, false, 150);
    
    int replacementSize = 100;
    int bestChromosomesThatRemain = 2;
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

int main(int argc,char* argv[]) {
    if(VISUAL) {
//        BasicDemo* bd = new BasicDemo();
//        bd->initPhysics();
        PassiveWalkerExperiment* experiment = PassiveWalkerExperiment::getInstance();
        WalkerBody* body = experiment->selectedBody;
        experiment->setCameraDistance(btScalar(5.));
        experiment->setCameraUp(btVector3(0, 15, 0));
        std::string exePath(argv[0]);
        std::vector<double> vals = loadPreviousParams(exePath);
        
//        static const double arr[] = { -20.8932, 9.77636, 0.91726, 0.180875, 1.95841, -6.66473, -7.68414, 105.134, 0.517725, 0.491385, 1.70121, -3.30518 };
//        std::vector<double> vals(arr, arr + sizeof(arr) / sizeof(arr[0]));
        
        for (int i = 0; i < vals.size(); i++) {
            std::cout << "Values: " << vals[i] << std::endl;
        }
//        const std::vector<double> arr = {10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10};
//        const std::vector<double> arr = {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1};
        if(BODY_TYPE==BodyType::partida){
            body->setActuatorValues(0,vals);
            body->setActuatorValues(1,vals);
        }
        else{
            body->setActuatorValues(0,vals);
        }

        //experiment->simulate();
        return glutmain(argc, argv, 800, 600, "Experiment",experiment);
//        return glutmain(argc, argv, 800, 600, "BasicDemo",bd);
    } else {
        clearFile("output.dat");
        return mainLoop(argv[0]);
    }
}
