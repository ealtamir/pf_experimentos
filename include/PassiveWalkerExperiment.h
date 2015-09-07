#ifndef PASSIVEWALKEREXPERIMENT_H_INCLUDED
#define PASSIVEWALKEREXPERIMENT_H_INCLUDED

#include <vector>

#include "Experiment.h"
#include "WalkerBody.h"

class PassiveWalkerExperiment : public Experiment {

public:
	PassiveWalkerExperiment();
	~PassiveWalkerExperiment();

    virtual WalkerBody* getWalkerBody();
    
    static float getFitness(const std::vector<double> vals);

    
private:
    BodyParameters* params;
	WalkerBody* body;
    

protected:
        
	virtual void initializeBodies();

	virtual void initObjects();

	virtual void worldStep();

	virtual bool stopExperiment();
    
    
};

static PassiveWalkerExperiment* experiment = new PassiveWalkerExperiment();

#endif
