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

// PF includes
#include "Experiment.h"
#include "PassiveWalkerExperiment.h"

#define VALUES_SIZE 20

int mainLoop();

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
        cout << vals[i] << ",";
    }
    cout << endl << "Fitness: " << newChromosome.GetFitness() << endl;
    
//    PassiveWalkerExperiment demoApp;
//    demoApp.enableStoppingCondition(false);
//    demoApp.initPhysics();
//    demoApp.setCameraDistance(btScalar(5.));
//    demoApp.setCameraUp(btVector3(0, 15, 0));
//    
//    int i = 0;
//    // left leg
//    demoApp.body->getBodyGroups()[0]->getBodyParts()[0]->setActuatorValues(vals[i*4+0],
//                                                                           vals[i*4+1],
//                                                                           vals[i*4+2],
//                                                                           vals[i*4+3]);
//    i++;
//    demoApp.body->getBodyGroups()[0]->getBodyParts()[1]->setActuatorValues(vals[i*4+0],
//                                                                           vals[i*4+1],
//                                                                           vals[i*4+2],
//                                                                           vals[i*4+3]);
//    i++;
//    
//    // right leg
//    demoApp.body->getBodyGroups()[1]->getBodyParts()[0]->setActuatorValues(vals[i*4+0],
//                                                                           vals[i*4+1],
//                                                                           vals[i*4+2],
//                                                                           vals[i*4+3]);
//    i++;
//    demoApp.body->getBodyGroups()[1]->getBodyParts()[1]->setActuatorValues(vals[i*4+0],
//                                                                           vals[i*4+1],
//                                                                           vals[i*4+2],
//                                                                           vals[i*4+3]);
//    i++;
//    // hip
//    demoApp.body->getBodyGroups()[2]->getBodyParts()[0]->setActuatorValues(vals[i*4+0],
//                                                                           vals[i*4+1],
//                                                                           vals[i*4+2],
//                                                                           vals[i*4+3]);
//    
//    
//    
//    
//    glutmain(NULL, NULL, 1024, 768, "Experiment",&demoApp);
    
    
}

void MiExperimentoObserver::EvolutionStateChanged(GaAlgorithmState newState, const GaAlgorithm& algorithm) {
    if( newState == GAS_RUNNING )
        cout << "Start\n";
    else if( newState == GAS_CRITERIA_STOPPED )
        cout << "End";
}

void MiExperimentoObserver::StatisticUpdate(const Common::GaStatistics &statistics, const Algorithm::GaAlgorithm &algorithm) {
    cout << "Generation: " << statistics.GetCurrentGeneration() << endl;
}

int main(int argc,char* argv[]) {
    bool visual = false;
    
    if(visual) {
    
    // Visual
    PassiveWalkerExperiment demoApp;
    demoApp.enableStoppingCondition(false);
    demoApp.initPhysics();
    demoApp.setCameraDistance(btScalar(5.));
    demoApp.setCameraUp(btVector3(0, 15, 0));
    
    const std::vector<double> vals = {22.6753,51.3633,33.0611,43.0724,9.53979,49.3043,43.6125,44.5845,21.3196,53.8534,13.7494,48.21,21.4231,37.8418,21.2192,66.0937,26.6465,37.3201,6.76354,43.3251};
    
    int i = 0;
    // left leg
    demoApp.body->getBodyGroups()[0]->getBodyParts()[0]->setActuatorValues(vals[i*4+0],
                                                                                vals[i*4+1],
                                                                                vals[i*4+2],
                                                                                vals[i*4+3]);
    i++;
    demoApp.body->getBodyGroups()[0]->getBodyParts()[1]->setActuatorValues(vals[i*4+0],
                                                                                vals[i*4+1],
                                                                                vals[i*4+2],
                                                                                vals[i*4+3]);
    i++;
    
    // right leg
    demoApp.body->getBodyGroups()[1]->getBodyParts()[0]->setActuatorValues(vals[i*4+0],
                                                                                vals[i*4+1],
                                                                                vals[i*4+2],
                                                                                vals[i*4+3]);
    i++;
    demoApp.body->getBodyGroups()[1]->getBodyParts()[1]->setActuatorValues(vals[i*4+0],
                                                                                vals[i*4+1],
                                                                                vals[i*4+2],
                                                                                vals[i*4+3]);
    i++;
    // hip
    demoApp.body->getBodyGroups()[2]->getBodyParts()[0]->setActuatorValues(vals[i*4+0],
                                                                                vals[i*4+1],
                                                                                vals[i*4+2],
                                                                                vals[i*4+3]);
    
    
    
    
    return glutmain(argc, argv, 1024, 768, "Experiment",&demoApp);
    } else {
    /*PassiveWalkerExperiment* exp= new PassiveWalkerExperiment();
    exp->initPhysics();
    for (int i = 0; i < 100; i++) {
        btDynamicsWorld* w = exp->getDynamicsWorld();
        w->stepSimulation(1 / 60.f);
        
        double value = exp->getWalkerBody()->getHeight();
        std::cout << "altura? " << value << std::endl;
        
    }
    exp->simulate();
    
    printf("la height: %f",exp->getHeight());
    */
    
    // GA
        return mainLoop();
    }
}

int mainLoop() {
    GaInitialize();
    
    GaValueIntervalBounds<double> valueInt( 0, 70 );
    GaValueIntervalBounds<double> invValueInt( 0, 70 );
    GaIntervalValueSet<double> valueSet( valueInt, invValueInt, GaGlobalRandomDoubleGenerator, false);
    GaIntervalValueSet<double> multiValueSet[20] = {
                                                    valueSet,valueSet,valueSet,valueSet,
                                                    valueSet,valueSet,valueSet,valueSet,
                                                    valueSet,valueSet,valueSet,valueSet,
                                                    valueSet,valueSet,valueSet,valueSet,
                                                    valueSet,valueSet,valueSet,valueSet
                                                   };

    GaChromosomeDomainBlock<double>* _ccb = new GaChromosomeDomainBlock<double>(
                        multiValueSet,
                        GaCrossoverCatalogue::Instance().GetEntryData( "GaMultiValueCrossover" ),
                        GaMutationCatalogue::Instance().GetEntryData( "GaFlipMutation" ),
                        new MiExperimentoFitness(),
                        GaFitnessComparatorCatalogue::Instance().GetEntryData( "GaMaxFitnessComparator" ),
                        new GaChromosomeParams( 0.08f, 4, false, 0.8f, 5 ) );
    
    GaMVArithmeticChromosome<double> _prototype( VALUES_SIZE, _ccb );
    
    GaPopulationParameters populationParams( 10, false, false, false, 0, 0 );
    Population::SelectionOperations::GaSelectRandomBestParams selectParams( 5, false, 2 );
    Population::ReplacementOperations::GaReplaceElitismParams replaceParams( 3, 1 );
    GaCouplingParams couplingParams( 4, false );
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
    
    GaMultithreadingAlgorithmParams algParam( 10 );
    Algorithm::SimpleAlgorithms::GaIncrementalAlgorithm* _algorithm = new Algorithm::SimpleAlgorithms::GaIncrementalAlgorithm( _population, algParam );
    
    GaStopCriteria* criteria = GaStopCriteriaCatalogue::Instance().GetEntryData( "GaGenerationCriteria" );
    Algorithm::StopCriterias::GaGenerationCriteriaParams critParam( 1000 );
    _algorithm->SetStopCriteria( criteria, &critParam );
    
    // subscribe observer
    _algorithm->SubscribeObserver( new MiExperimentoObserver() );
    
    _algorithm->StartSolving(false);
    
    _algorithm->WaitForThreads();
    
    GaFinalize();
    
    return 0;
}
