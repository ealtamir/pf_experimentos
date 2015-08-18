#include "GLDebugDrawer.h"
#include "PassiveWalkerExperiment.h"
//#include "TranslatingCube.h"
//#include "FallingBall.h"
//#include "GenericJointDemo.h"

#include <iostream>

// GA libraries
#include "Initialization.h"
#include "ChromosomeOperations.h"
#include "MultiValueChromosome.h"
#include "Population.h"
#include "StopCriterias.h"
#include "IncrementalAlgorithm.h"


// GA namespaces
using namespace std;

using namespace Algorithm;
using namespace Algorithm::StopCriterias;
using namespace Algorithm::SimpleAlgorithms;

int mainLoop(Experiment*);

// GA Fitness
class fFitness : public GaFitnessOperation
{
public:

    virtual float GACALL operator ()(const GaChromosome* chromosome) const
    {
        const vector<double>& vals = dynamic_cast<const GaMVArithmeticChromosome<double>*>( chromosome )->GetCode();
        return (float)( 5 * vals[ 0 ] * sin( vals[ 0 ] ) + 2 * vals[ 1 ] * sin( vals[ 1 ] ) );
    }

    virtual GaParameters* GACALL MakeParameters() const { return NULL; }

    virtual bool GACALL CheckParameters(const GaParameters& parameters) const { return true; }
};

// GA Observer
class fObserver : public GaObserverAdapter
{
    virtual void GACALL NewBestChromosome(const GaChromosome& newChromosome, const GaAlgorithm& algorithm)
    {
        const vector<double>& vals = dynamic_cast<const GaMVArithmeticChromosome<double>&>( newChromosome ).GetCode();
        cout << "New chromosome found:\n";
        cout << "Fitness: " << newChromosome.GetFitness() << endl;
        cout << "x: " << vals[0] << " y: " << vals[1] << endl;
    }

    virtual void GACALL EvolutionStateChanged(GaAlgorithmState newState, const GaAlgorithm& algorithm)
    {
        if( newState == GAS_RUNNING )
            cout << "start\n";
        else if( newState == GAS_CRITERIA_STOPPED )
            cout << "end";
    }
};

int main(int argc,char* argv[])
{
    PassiveWalkerExperiment demoApp;
    demoApp.enableStoppingCondition(false);
    demoApp.initPhysics();
    demoApp.setCameraDistance(btScalar(3.));
    demoApp.setCameraUp(btVector3(0, 10, 0));
//    return mainLoop(&demoApp);
    return glutmain(argc, argv, 1024, 768, "Experiment",&demoApp);
}

int mainLoop(Experiment* demoApp)
{
    demoApp->initPhysics();

    // GA code
    // Our cromosome will be the 'PassiveWalkerExperiment class'
    GaInitialize();
    
    // make chromosome parameters
    // mutation probability: 3%
    // crossover points: 2
    // no "improving only mutations"
    // crossover probability: 80%
    // number of moved classes per mutation: 2
    GaChromosomeParams chromosomeParams( 0.03f, 2, false, 0.8f, 2 );

    GaValueIntervalBounds<double> valueInt( 0, 10 );
    GaValueIntervalBounds<double> invValueInt( 0, 10 );
    GaIntervalValueSet<double> valueSet( valueInt, invValueInt, GaGlobalRandomDoubleGenerator, false);

    fFitness fitnessOperation;
    GaChromosomeDomainBlock<double> configBlock( &valueSet,
        GaCrossoverCatalogue::Instance().GetEntryData( "GaMultiValueCrossover" ),
        GaMutationCatalogue::Instance().GetEntryData( "GaFlipMutation" ),
        &fitnessOperation, GaFitnessComparatorCatalogue::Instance().GetEntryData( "GaMaxFitnessComparator" ),
        &chromosomeParams );

    GaMVArithmeticChromosome<double> prototype( 2, &configBlock );

    GaPopulationConfiguration populationConfig;
    // make population parameters
    // number of chromosomes in population: 300
    // population always has fixed number of chromosomes
    // population is not sorted
    // non-transformed(non-scaled) fitness values are used for sorting and tracking chromosomes
    // population tracks 5 best and 5 worst chromosomes
    GaPopulationParameters populationParams( 300, false, false, false, 5, 5 );

    populationConfig.SetParameters( populationParams );
    populationConfig.SetSortComparator( &configBlock.GetFitnessComparator() );

    GaPopulation population( &prototype, &populationConfig );

    // make parameters for genetic algorithms
    // algorithm will use 10 workers
    GaMultithreadingAlgorithmParams algorithmParams( 10 );
    Algorithm::SimpleAlgorithms::GaIncrementalAlgorithm algorithm( &population, algorithmParams );

    // make generation count stop criteria
    GaGenerationCriteriaParams criteriaParams( 10000 );
    // make incremental algorithm with periously defined population and parameters
    algorithm.SetStopCriteria( GaStopCriteriaCatalogue::Instance().GetEntryData( "GaGenerationCriteria" ), &criteriaParams);

    fObserver observer;
    // subscribe observer
    algorithm.SubscribeObserver( &observer );
    // Start solving the GA. If false start with clear state. If true start with saved state
    algorithm.StartSolving( false );
    // Waits for threads to finish
    algorithm.WaitForThreads();
    // Free resources used by GA
    GaFinalize();
    // GA code end

    int i = 0;
    while(i<0) {
        i++;
        demoApp->worldStep();
    }
//    demoApp->stopExperiment();
    return 0;
}
