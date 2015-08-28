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

// chromosome

class PfChromosome : public GaMultiValueChromosome<const Experiment*> {
public:
    PfChromosome(GaChromosomeDomainBlock<const Experiment*>* configBlock) : GaMultiValueChromosome(configBlock) {
        _values.resize(VALUES_SIZE);
    };
    
    PfChromosome(const PfChromosome& chromosome,
                 bool setupOnly) : GaMultiValueChromosome<const Experiment*>(chromosome, setupOnly) {
        if( setupOnly ) {
            _values.resize(VALUES_SIZE);
        }
    };
    
    virtual GaChromosomePtr GACALL MakeCopy(bool setupOnly) const {
        return new PfChromosome( *this, setupOnly );
    }
    
    virtual GaChromosomePtr GACALL MakeNewFromPrototype() const;
};

// operations
// crossover

class MiExperimentoCrossover : public GaCrossoverOperation {
    
public:
    
    virtual GaChromosomePtr GACALL operator ()(const GaChromosome* parent1,
                                               const GaChromosome* parent2) const;
    
    virtual GaParameters* GACALL MakeParameters() const { return NULL; }
    
    virtual bool GACALL CheckParameters(const GaParameters& parameters) const { return true; }
    
};

// fitness

class MiExperimentoFitness : public GaFitnessOperation {
    
public:
    
    virtual float GACALL operator ()(const GaChromosome* chromosome) const;
    
    virtual GaParameters* GACALL MakeParameters() const { return NULL; }
    
    virtual bool GACALL CheckParameters(const GaParameters& parameters) const { return true; }
};

// observer

class MiExperimentoObserver : public GaObserverAdapter {
    
public:
    
    virtual void GACALL NewBestChromosome(const GaChromosome& newChromosome, const GaAlgorithm& algorithm);
    
    virtual void GACALL EvolutionStateChanged(GaAlgorithmState newState, const GaAlgorithm& algorithm);
    
};

// mutation

class MiExperimentoMutation : public GaMutationOperation {
    
public:
    
    virtual void GACALL operator ()(GaChromosome* chromosome) const;
    
    virtual GaParameters* GACALL MakeParameters() const { return NULL; }
    
    virtual bool GACALL CheckParameters(const GaParameters& parameters) const { return true; }
    
};

// scaling

class MiExperimentoScaling : public GaScalingOperation {
    
public:
    
    virtual float GACALL operator ()(const GaScaledChromosome& chromosome,
                                     const GaPopulation& population,
                                     const GaScalingParams& parameters) const;
    
    virtual bool GACALL IsRankingBased() const { return false; }
    
    virtual bool GACALL NeedRescaling(const GaPopulation& population,
                                      const GaScalingParams& parameters) const { return true; }
    
    virtual GaParameters* GACALL MakeParameters() const { return NULL; }
    
    virtual bool GACALL CheckParameters(const GaParameters& parameters) const { return true; }
};

// implementations

GaChromosomePtr PfChromosome::MakeNewFromPrototype() const {
    PfChromosome* g = new PfChromosome( (GaChromosomeDomainBlock<const Experiment*>*)_configBlock );
    
    g->_values.resize(VALUES_SIZE);
    g->_values[0] = new PassiveWalkerExperiment();
    const vector<const Experiment*>& v = g->GetCode();
    return g;
}

GaChromosomePtr MiExperimentoCrossover::operator ()(const GaChromosome* parent1,
                                                    const GaChromosome* parent2) const {
    const PfChromosome* p1 = dynamic_cast<const PfChromosome*>( parent1 );
    const PfChromosome* p2 = dynamic_cast<const PfChromosome*>( parent2 );
    
    GaChromosomePtr newChromosome = p1->MakeCopy( false );
    
    return newChromosome;
}

float MiExperimentoFitness::operator ()(const GaChromosome* chromosome) const {
    const std::vector<double>& vals = dynamic_cast<const GaMVArithmeticChromosome<double>*>( chromosome )->GetCode();
//    const PfChromosome* c = dynamic_cast<const PfChromosome*>( chromosome );
//    const vector<const double*>& v = c->GetCode();
    
    return PassiveWalkerExperiment::getFitness(vals);
//    return v[0]->getHeight()* v[0]->getVelocity();
    //return 3; // return v[0]->getFitness(); // Impement method getFitness()
}

void MiExperimentoObserver::NewBestChromosome(const GaChromosome& newChromosome, const GaAlgorithm& algorithm) {
    const std::vector<double>& vals = dynamic_cast<const GaMVArithmeticChromosome<double>*>( &newChromosome )->GetCode();
    cout << "New chromosome found:\n";
    for(int i = 0; i < vals.size(); i++){
        cout << vals[i] << ",";
    }
    cout << "Fitness: " << newChromosome.GetFitness() << endl;
}

void MiExperimentoMutation::operator ()(GaChromosome* chromosome) const {
    const PfChromosome* c = dynamic_cast<const PfChromosome*>( chromosome );
    const vector<const Experiment*>& v = c->GetCode();
    if (!v.empty() && v[0] != NULL) {

    } else {
        cout << "empty";
    }
}

float MiExperimentoScaling::operator ()(const Chromosome::GaScaledChromosome &chromosome,
                                        const Population::GaPopulation &population,
                                        const Population::GaScalingParams &parameters) const {
//    const PfChromosome* c = dynamic_cast<const PfChromosome*>( chromosome.GetChromosome().GetRawPtr() );
//    const vector<const Experiment*>& v = c->GetCode();
//    v[0]->simulate(); cannot call this method because simulate isn't const
//    return v[0]->getHeight();
    return 0;
}

void MiExperimentoObserver::EvolutionStateChanged(GaAlgorithmState newState, const GaAlgorithm& algorithm) {
    if( newState == GAS_RUNNING )
        cout << "start\n";
    else if( newState == GAS_CRITERIA_STOPPED )
        cout << "end";
}

int main(int argc,char* argv[]) {
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
    return mainLoop();
}

int mainLoop() {
    GaInitialize();
    
    GaValueIntervalBounds<double> valueInt( 5, 15 );
    GaValueIntervalBounds<double> invValueInt( 5, 15 );
    GaIntervalValueSet<double> valueSet( valueInt, invValueInt, GaGlobalRandomDoubleGenerator, false);
    
    GaChromosomeDomainBlock<double>* _ccb = new GaChromosomeDomainBlock<double>(
                        &valueSet,
                        GaCrossoverCatalogue::Instance().GetEntryData( "GaMultiValueCrossover" ), // here we could use our own crossover "new MiExperimentoCrossover()"
                        GaMutationCatalogue::Instance().GetEntryData( "GaFlipMutation" ), // here we could use our own mutation "new MiExperimentoMutation()"
                        new MiExperimentoFitness(),
                        GaFitnessComparatorCatalogue::Instance().GetEntryData( "GaMaxFitnessComparator" ),
                        new GaChromosomeParams( 0.08f, 2, false, 0.8f, 2 ) );
    
    GaMVArithmeticChromosome<double> _prototype( VALUES_SIZE, _ccb );
    
    GaPopulationParameters populationParams( 20, false, false, false, 0, 0 );
    Population::SelectionOperations::GaSelectRandomBestParams selectParams( 15, false, 5 );
    Population::ReplacementOperations::GaReplaceElitismParams replaceParams( 10, 4 );
    GaCouplingParams couplingParams( 8, false );
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
    Algorithm::StopCriterias::GaGenerationCriteriaParams critParam( 100 );
    _algorithm->SetStopCriteria( criteria, &critParam );
    
    // subscribe observer
    _algorithm->SubscribeObserver( new MiExperimentoObserver() );
    
    _algorithm->StartSolving(false);
    
    _algorithm->WaitForThreads();
    
    GaFinalize();
    
    return 0;
}
