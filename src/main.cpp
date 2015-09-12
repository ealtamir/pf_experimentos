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


#define VALUES_SIZE 15

int mainLoop();
double getTimeElapsed();

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
    const std::vector<double>& vals = dynamic_cast<const GaMVArithmeticChromosome<double>*>( chromosome )->GetCode();
    
    float fit = PassiveWalkerExperiment::getFitness(vals);
    cout << "Fitness calculado: " << fit << endl;
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
    cout << endl << "Fitness: " << fitness;
    cout << endl << "Generation: " << algorithm.GetAlgorithmStatistics().GetCurrentGeneration() << endl;
}

void MiExperimentoObserver::EvolutionStateChanged(GaAlgorithmState newState, const GaAlgorithm& algorithm) {
    if( newState == GAS_RUNNING )
        cout << "Start\n";
    else if( newState == GAS_CRITERIA_STOPPED )
        cout << "End";
}

void MiExperimentoObserver::StatisticUpdate(const Common::GaStatistics &statistics, const Algorithm::GaAlgorithm &algorithm) {
//    cout << "Generation: " << statistics.GetCurrentGeneration() << endl;
//    cout << "Number of chromosomes: " << algorithm.GetPopulation(0).GetCurrentSize() << endl;
}

int mainLoop(char* executablePath);

int main(int argc,char* argv[]) {
    bool visual = false;
    
<<<<<<< HEAD
    

    if(visual) {
        // Visual
        PassiveWalkerExperiment demoApp;
        demoApp.enableStoppingCondition(false);
        demoApp.initPhysics();
        demoApp.setCameraDistance(btScalar(5.));
        demoApp.setCameraUp(btVector3(0, 15, 0));
//    
//        const std::vector<double> vals = {18.1344,75.2887,0.461302,2.16036,42.165,24.7066,2.60708,2.25458,21.4392,16.0233,3.06373,0.542407,82.897,80.8128,0.017934,2.14528,67.6801,19.7501,2.44676,0.263374};
//        std::vector<double> vals = {9.20204,0.0554247,0.808715,2.52892,7.42943,67.5075,45.3359,18.2351,49.7803,18.6819,53.7379,2.4818,15.4646,39.2329,49.2822,0.760422,33.191,21.9214,0.0776573,96.7167};
//        double* values = &vals[0];
    
        std::string exePath(argv[0]);
        std::vector<double> vals = loadPreviousParams(exePath);
        
        
=======
    if(visual) {
        // Visual
        PassiveWalkerExperiment* experiment = new PassiveWalkerExperiment();
        experiment->enableStoppingCondition(false);
        experiment->initPhysics();
        experiment->setCameraDistance(btScalar(5.));
        experiment->setCameraUp(btVector3(0, 15, 0));
    
        const std::vector<double> vals = {146.032, 86.2208, 3.81322, 9.65075, 86.7628, 90.9459, 107.96, 9.82448, 5.35343, 5.68214, 0.0324722, 0.0664948, 0.0309905, 0.0995999, 0.072406};
    
>>>>>>> 89ed950e641d526f8c60b87b8d32150cbf1cbd29
        int i = 0;
        // left leg
        experiment->body->getBodyGroups()[0]->getBodyParts()[0]->setActuatorValues(vals[i*5+0],
                                                                                   vals[i*5+1],
                                                                                   vals[i*5+2],
                                                                                   vals[i*5+3],
                                                                                   vals[i*5+4]);
        // right leg
        experiment->body->getBodyGroups()[1]->getBodyParts()[0]->setActuatorValues(vals[i*5+0],
                                                                                   vals[i*5+1],
                                                                                   vals[i*5+2],
                                                                                   vals[i*5+3],
                                                                                   vals[i*5+4] + SIMD_PI);
        i++;
        
        // left leg
        experiment->body->getBodyGroups()[0]->getBodyParts()[1]->setActuatorValues(vals[i*5+0],
                                                                                   vals[i*5+1],
                                                                                   vals[i*5+2],
                                                                                   vals[i*5+3],
                                                                                   vals[i*5+4]);
        // right leg
        experiment->body->getBodyGroups()[1]->getBodyParts()[1]->setActuatorValues(vals[i*5+0],
                                                                                   vals[i*5+1],
                                                                                   vals[i*5+2],
                                                                                   vals[i*5+3],
                                                                                   vals[i*5+4] + SIMD_PI);
        i++;
        // hip
        experiment->body->getBodyGroups()[2]->getBodyParts()[0]->setActuatorValues(vals[i*5+0],
                                                                                   vals[i*5+1],
                                                                                   vals[i*5+2],
                                                                                   vals[i*5+3],
                                                                                   vals[i*5+4]);
    
    
        return glutmain(argc, argv, 1024, 768, "Experiment",experiment);
    } else {
        /*PassiveWalkerExperiment* exp= new PassiveWalkerExperiment();
        exp->initPhysics();
        
        exp->simulate();
         
        printf("la height: %f",exp->getHeight());
        */
        
<<<<<<< HEAD
    }
    exp->simulate();
    
    printf("la height: %f",exp->getHeight());
    */
    
    // GA
    
       return mainLoop(argv[0]);
=======
        // GA
       return mainLoop();
>>>>>>> 89ed950e641d526f8c60b87b8d32150cbf1cbd29
    }
}

int mainLoop(char* executablePath) {
    struct timeval before;
    gettimeofday(&before, NULL);
    time_begin = before.tv_sec * 1000 + before.tv_usec / 1000;
    
    
    GaInitialize();
    
    GaValueIntervalBounds<double> valueInt( 0, 150 );
    GaValueIntervalBounds<double> invValueInt( 0, 150 );
    GaValueIntervalBounds<double> valueInt2( 0.5, 10 );
    GaValueIntervalBounds<double> invValueInt2( 0.5, 10 );
    GaValueIntervalBounds<double> valueInt3( 0, 3.14*2 );
    GaValueIntervalBounds<double> invValueInt3( 0, 3.14*2 );
    GaValueIntervalBounds<double> valueInt4( 0, 0.1 );
    GaValueIntervalBounds<double> invValueInt4( 0, 0.1 );
    GaIntervalValueSet<double> valueSet( valueInt, invValueInt, GaGlobalRandomDoubleGenerator, false);
    GaIntervalValueSet<double> valueSet2( valueInt2, invValueInt2, GaGlobalRandomDoubleGenerator, false);
    GaIntervalValueSet<double> valueSet3( valueInt3, invValueInt3, GaGlobalRandomDoubleGenerator, false);
    GaIntervalValueSet<double> valueSet4( valueInt4, invValueInt4, GaGlobalRandomDoubleGenerator, false);
    GaIntervalValueSet<double> *multiValueSet[VALUES_SIZE] = {
                                                    &valueSet,&valueSet,&valueSet2,&valueSet2, &valueSet3,
                                                    &valueSet,&valueSet,&valueSet2,&valueSet2, &valueSet3,
                                                    &valueSet4,&valueSet4,&valueSet4,&valueSet4, &valueSet4
                                                    };
    
    GaChromosomeDomainBlock<double>* _ccb = new GaChromosomeDomainBlock<double>(
                        (GaValueSet<double>**)(&multiValueSet),
                        VALUES_SIZE,
                        GaCrossoverCatalogue::Instance().GetEntryData( "GaMultiValueCrossover" ),
                        GaMutationCatalogue::Instance().GetEntryData( "GaFlipMutation" ),
                        new MiExperimentoFitness(),
                        GaFitnessComparatorCatalogue::Instance().GetEntryData( "GaMaxFitnessComparator" ),
                        new GaChromosomeParams( 0.08f, 4, true, 0.75f, 2 ) );
    
    
    
    GaMVArithmeticChromosome<double> _prototype( VALUES_SIZE, _ccb );
    
    GaPopulationParameters populationParams( 50, false, false, false, 0, 0 );
    Population::SelectionOperations::GaSelectRandomBestParams selectParams( 15, false, 4 );
    Population::ReplacementOperations::GaReplaceElitismParams replaceParams( 6, 3 );
    GaCouplingParams couplingParams( 6, false );
    Population::ScalingOperations::GaScaleFactorParams scalingParams(1);
    
    GaPopulationConfiguration* _populationConfiguration = new GaPopulationConfiguration(
                                    populationParams,
                                    &_ccb->GetFitnessComparator(),
                                    GaSelectionCatalogue::Instance().GetEntryData( "GaSelectRandomBest" ),
                                    &selectParams,
                                    GaReplacementCatalogue::Instance().GetEntryData( "GaReplaceRandom" ),
                                    &replaceParams,
                                    GaCouplingCatalogue::Instance().GetEntryData( "GaSimpleCoupling" ),
                                    &couplingParams,
                                    NULL,
                                    &scalingParams);
    
    GaPopulation* _population = new GaPopulation( &_prototype, _populationConfiguration );
    
    GaMultithreadingAlgorithmParams algParam( 1 );
    Algorithm::SimpleAlgorithms::GaIncrementalAlgorithm* _algorithm = new Algorithm::SimpleAlgorithms::GaIncrementalAlgorithm( _population, algParam );
    
    GaStopCriteria* criteria = GaStopCriteriaCatalogue::Instance().GetEntryData( "GaGenerationCriteria" );
    Algorithm::StopCriterias::GaGenerationCriteriaParams critParam( 2000 );
    _algorithm->SetStopCriteria( criteria, &critParam );
    
    // subscribe observer
    _algorithm->SubscribeObserver( new MiExperimentoObserver() );
    
    _algorithm->StartSolving(false);
    
    _algorithm->WaitForThreads();
    
    GaFinalize();
    
    
    cout << endl << "Mejor cromosoma encontrado:  ";
    for(int i = 0; i < VALUES_SIZE; i++){
        cout << values[i] << ",";
    }
    cout << endl << "Fitness: " << fitness;
    cout << "\n Tiempo transcurrido:  ";
    cout << getTimeElapsed() / 1000.0;
    cout << " segundos ";
    
    
    
    updateResultFiles(std::string(executablePath), fitness, values, 20, getTimeElapsed());
    return 0;
}


double getTimeElapsed(){
    struct timeval after;
    gettimeofday(&after, NULL);
    
    return (after.tv_sec * 1000 + after.tv_usec / 1000) - time_begin;

}
