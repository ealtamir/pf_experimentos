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
    const std::vector<double>& vals = dynamic_cast<const GaMVArithmeticChromosome<double>*>( chromosome )->GetCode();
    
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

    cout << endl << "DATA PRINTED TO PLOT SERVER" << endl;
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
    int i;
    algorithm.GetPopulation(statistics.GetCurrentGeneration()).GetBestChromosomes( &i, 0, 1 );
    GaChromosomePtr bestChromo = algorithm.GetPopulation(statistics.GetCurrentGeneration()).GetAt( i ).GetChromosome();
    const std::vector<double>& vals = dynamic_cast<const GaMVArithmeticChromosome<double>*>( &(*bestChromo) )->GetCode();
    storeGenerationInfo("output.dat", statistics.GetCurrentGeneration(), bestChromo->GetFitness(), vals, VALUES_SIZE);
}

int mainLoop(char* executablePath);

int main(int argc,char* argv[]) {
    bool visual = false;

    if(visual) {
        // Visual
        PassiveWalkerExperiment* experiment = new PassiveWalkerExperiment();
        experiment->enableStoppingCondition(false);
        experiment->initPhysics();
        experiment->setCameraDistance(btScalar(5.));
        experiment->setCameraUp(btVector3(0, 15, 0));
    
        std::string exePath(argv[0]);
        std::vector<double> vals = loadPreviousParams(exePath);

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
        */
        //esto es para probar que la función angle de bullet hace bien lo de los cuadrantes (me fijo en el plano y,z)
//        btVector3 v=btVector3(0,1,0);
//        btVector3 v1=btVector3(0,1,1); //primer cuadrante
//        btVector3 v2=btVector3(0,-1,0.5); //segundo cuadrante
//        btVector3 v3=btVector3(0,-1,-1); //tercer cuadrante
//        btVector3 v4=btVector3(0,1,-1); //cuarto cuadrante
//        printf("angle de v1: %f \n",v1.angle(v)*(180/3.1416));
//        printf("angle de v2: %f \n",v2.angle(v)*(180/3.1416));
//        printf("angle de v3: %f \n",v3.angle(v)*(180/3.1416));
//        printf("angle de v4: %f \n",v4.angle(v)*(180/3.1416));
//        
//        printf("anglebetween de v1: %f \n",getAngleBetween(v1,v)*(180/3.1416));
//        printf("anglebetween de v2: %f \n",getAngleBetween(v2,v)*(180/3.1416));
//        printf("anglebetween de v3: %f \n",getAngleBetween(v3,v)*(180/3.1416));
//        printf("anglebetween de v4: %f \n",getAngleBetween(v4,v)*(180/3.1416));
        clearFile("output.dat");
        return mainLoop("end.dat");
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
                                                    &valueSet,&valueSet,&valueSet2,&valueSet2, &valueSet3
                                                    };
    
    GaChromosomeDomainBlock<double>* _ccb = new GaChromosomeDomainBlock<double>(
                        (GaValueSet<double>**)(&multiValueSet),
                        VALUES_SIZE,
                        GaCrossoverCatalogue::Instance().GetEntryData( "GaMultiValueCrossover" ),
                        GaMutationCatalogue::Instance().GetEntryData( "GaFlipMutation" ),
                        new MiExperimentoFitness(),
                        GaFitnessComparatorCatalogue::Instance().GetEntryData( "GaMaxFitnessComparator" ),
                        new GaChromosomeParams( 0.10f, 2, true, 0.80f, 3 ) );
    
    
    
    GaMVArithmeticChromosome<double> _prototype( VALUES_SIZE, _ccb );
    
    GaPopulationParameters populationParams( 10, false, false, false, 0, 0 );
    Population::SelectionOperations::GaSelectRandomBestParams selectParams( 4, false, 2 );
    Population::ReplacementOperations::GaReplaceElitismParams replaceParams( 4, 2 );
    GaCouplingParams couplingParams( 3, false );
    
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
                                    NULL);
    
    GaPopulation* _population = new GaPopulation( &_prototype, _populationConfiguration );
    
    GaMultithreadingAlgorithmParams algParam( 1 );
    Algorithm::SimpleAlgorithms::GaIncrementalAlgorithm* _algorithm = new Algorithm::SimpleAlgorithms::GaIncrementalAlgorithm( _population, algParam );
    
    GaStopCriteria* criteria = GaStopCriteriaCatalogue::Instance().GetEntryData( "GaGenerationCriteria" );
    Algorithm::StopCriterias::GaGenerationCriteriaParams critParam( 300 );
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

double getAngleBetween(btVector3 v1, btVector3 v2){
    double arg1 = (v1.cross(v2)).norm();
    double arg2 = (v1.dot(v2));
    
    return atan2(arg1,arg2);
}
