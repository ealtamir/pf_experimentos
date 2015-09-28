#ifndef PASSIVEWALKEREXPERIMENT_H_INCLUDED
#define PASSIVEWALKEREXPERIMENT_H_INCLUDED

#include <vector>

#include "Experiment.h"
#include "WalkerBody.h"

class PassiveWalkerExperiment : public Experiment {

public:
    ~PassiveWalkerExperiment();
    
    static float getFitness(const std::vector<double> vals);
    
    static void setWalkerActuatorValues(std::vector<double> vals,
                                        Body* walkerExperiment);
    virtual void simulate();
    
    static PassiveWalkerExperiment* getInstance();

    
private:
    PassiveWalkerExperiment();
    
    static PassiveWalkerExperiment* walkerInstance;
    
    BodyParameters* params{};
    
    double getHeightCoefficient(double h, double min_h, double optimal_h);
    
    double getVelocityCoefficient(btVector3& current_velocity, double desiredZspeed);
    
    double getAngleCoefficient(btVector3& normalizedVel);
	    
protected:
        
	virtual void initializeBodies();

	virtual void initObjects();

	virtual void worldStep();

	virtual bool stopExperiment();
    
};
#endif
