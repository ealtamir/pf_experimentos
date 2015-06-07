#ifndef PASSIVEWALKEREXPERIMENT_H_INCLUDED
#define PASSIVEWALKEREXPERIMENT_H_INCLUDED

#include "Experiment.h"
#include "PassiveWalkerBody.h"

class PassiveWalkerExperiment : public Experiment {

public:
	PassiveWalkerExperiment();
	~PassiveWalkerExperiment();

private:
	PassiveWalkerBody* body;

protected:
	virtual void initializeBodies();

	virtual void initObjects();

	virtual void worldStep();

	virtual bool stopExperiment();
};

#endif
