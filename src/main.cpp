// GA libraries
#include "Initialization.h"
#include "ChromosomeOperations.h"
#include "SelectionOperations.h"
#include "ReplacementOperations.h"
#include "MultiValueChromosome.h"
#include "Population.h"
#include "StopCriterias.h"
#include "IncrementalAlgorithm.h"
#include "CouplingOperations.h"
#include "DomainChromosome.h"
#include "MutationOperations.h"
#include "Algorithm.h"
#include "Population.h"
#include "PopulationOperations.h"
#include "Chromosome.h"

// System libraries
#include <stdlib.h>
#include <vector>
#include <iostream>

// PF includes
#include "Experiment.h"
#include "PassiveWalkerExperiment.h"

// Namespaces
using namespace std;

int mainLoop();

// experiment

class MiExperimento {
public:
    int caca;
    
    MiExperimento(int _caca) {
        caca = _caca;
    }
    
    void setCaca(int _caca) const {
        *((int*)( &caca )) = _caca;
    }
};

// chromosome

class PfChromosome : public GaMultiValueChromosome<const Experiment*> {
public:
    PfChromosome(GaChromosomeDomainBlock<const Experiment*>* configBlock) : GaMultiValueChromosome(configBlock) {
        _values.resize(1);
    };
    
    PfChromosome(const PfChromosome& chromosome,
                 bool setupOnly) : GaMultiValueChromosome<const Experiment*>(chromosome, setupOnly) {
        if( setupOnly ) {
            _values.resize(1);
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

// implementations

GaChromosomePtr PfChromosome::MakeNewFromPrototype() const {
    PfChromosome* g = new PfChromosome( (GaChromosomeDomainBlock<const Experiment*>*)_configBlock );
    
    g->_values.resize( 1 );
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
    const PfChromosome* c = dynamic_cast<const PfChromosome*>( chromosome );
    const vector<const Experiment*>& v = c->GetCode();
    return 3; // return v[0]->getFitness(); // Impement method getFitness()
}

void MiExperimentoObserver::NewBestChromosome(const GaChromosome& newChromosome, const GaAlgorithm& algorithm) {
    const PfChromosome* c = dynamic_cast<const PfChromosome*>( &newChromosome );
    const vector<const Experiment*>& v = c->GetCode();
    cout << "New chromosome found:\n";
    cout << "Fitness: " << newChromosome.GetFitness() << endl;
//    cout << "x: " << v[0]->caca << endl;
}

void MiExperimentoObserver::EvolutionStateChanged(GaAlgorithmState newState, const GaAlgorithm& algorithm) {
    if( newState == GAS_RUNNING )
        cout << "start\n";
    else if( newState == GAS_CRITERIA_STOPPED )
        cout << "end";
}

void MiExperimentoMutation::operator ()(GaChromosome* chromosome) const {
    const PfChromosome* c = dynamic_cast<const PfChromosome*>( chromosome );
    const vector<const Experiment*>& v = c->GetCode();
    if (!v.empty() && v[0] != NULL) {
//        cout << v[0]->caca;
//        v[0]->setCaca(22); // v[0]->mutateExperiment(); // implement method mutateExperiment()
    } else {
        cout << "empty";
    }
}


int main(int argc,char* argv[]) {
    PassiveWalkerExperiment* exp= new PassiveWalkerExperiment();
    exp->initPhysics();
    for (int i = 0; i < 100; i++) {
        btDynamicsWorld* w = exp->getDynamicsWorld();
        w->stepSimulation(1 / 60.f);
        //exp->getDynamicsWorld()->stepSimulation(1 / 60.f, 10);
        double value = exp->getWalkerBody()->getHeight();
        std::cout << "altura? " << value << std::endl;
        btTransform trans;
        //fallRigidBody->getMotionState()->getWorldTransform(trans);
        
        //std::cout << "altura? " << trans.getOrigin().getY() << std::endl;
    }
    return mainLoop();
}

int mainLoop() {
    GaInitialize();
    
    GaChromosomeDomainBlock<const Experiment*>* _ccb = new GaChromosomeDomainBlock<const Experiment*>( NULL, 0, new MiExperimentoCrossover(), new MiExperimentoMutation(),
                                                       new MiExperimentoFitness(), GaFitnessComparatorCatalogue::Instance().GetEntryData( "GaMaxFitnessComparator" ),
                                                       new GaChromosomeParams( 0.3f, 2, false, 0.8f, 2 ) );
    
    PfChromosome* _prototype = new PfChromosome( _ccb );
    
    GaPopulationParameters populationParams( 2, false, false, false, 0, 0 );
    Population::SelectionOperations::GaSelectRandomBestParams selectParams( 8, true, 10 );
    Population::ReplacementOperations::GaReplaceElitismParams replaceParams( 8, 10 );
    GaCouplingParams couplingParamss( 8, true );
    
    GaPopulationConfiguration* _populationConfiguration = new GaPopulationConfiguration( populationParams, &_ccb->GetFitnessComparator(),
                                                             GaSelectionCatalogue::Instance().GetEntryData( "GaSelectRandomBest" ), &selectParams,
                                                             GaReplacementCatalogue::Instance().GetEntryData( "GaReplaceRandom" ), &replaceParams,
                                                             GaCouplingCatalogue::Instance().GetEntryData( "GaSimpleCoupling" ), &couplingParamss,
                                                             NULL, NULL);
    
    GaPopulation* _population = new GaPopulation( _prototype, _populationConfiguration );
    
    GaMultithreadingAlgorithmParams algParam( 1 );
    Algorithm::SimpleAlgorithms::GaIncrementalAlgorithm* _algorithm = new Algorithm::SimpleAlgorithms::GaIncrementalAlgorithm( _population, algParam );
    
    GaStopCriteria* criteria = GaStopCriteriaCatalogue::Instance().GetEntryData( "GaFitnessProgressCriteria" );
    Algorithm::StopCriterias::GaFitnessProgressCriteriaParams critParam( 1, true, Algorithm::StopCriterias::GFC_LESS_THEN, GSV_BEST_FITNESS, 50000 );
    _algorithm->SetStopCriteria( criteria, &critParam );
    
    // subscribe observer
    _algorithm->SubscribeObserver( new MiExperimentoObserver() );
    
    _algorithm->StartSolving(false);
    
    _algorithm->WaitForThreads();
    
    GaFinalize();
    
    return 0;
}
