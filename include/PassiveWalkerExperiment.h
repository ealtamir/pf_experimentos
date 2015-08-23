#ifndef PASSIVEWALKEREXPERIMENT_H_INCLUDED
#define PASSIVEWALKEREXPERIMENT_H_INCLUDED

#include "Experiment.h"
#include "WalkerBody.h"

class PassiveWalkerExperiment : public Experiment {

public:
	PassiveWalkerExperiment();
	~PassiveWalkerExperiment();

    virtual WalkerBody* getWalkerBody();
    

    
private:
    BodyParameters* params;
	WalkerBody* body;
    

protected:
        
	virtual void initializeBodies();

	virtual void initObjects();

	virtual void worldStep();

	virtual bool stopExperiment();
    
    
};

#endif
