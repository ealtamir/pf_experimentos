#ifndef PASSIVEWALKEREXPERIMENT_H_INCLUDED
#define PASSIVEWALKEREXPERIMENT_H_INCLUDED

#include <vector>

#include "Experiment.h"
#include "WalkerBody.h"

enum BodyType {
    generic, fourier, double_cosine, partida
};

//#define     GENERIC             1
//#define     FOURIER             1
//#define     DOUBLE_COSINE       1
#define     PARTIDA       1

#ifdef      GENERIC
#define     VALUES_SIZE         12
const BodyType BODY_TYPE = BodyType::generic;
#elif       FOURIER
#define     VALUES_SIZE         14
const BodyType BODY_TYPE = BodyType::fourier;
#elif       PARTIDA
#define     VALUES_SIZE         8

const BodyType BODY_TYPE = BodyType::partida;
#elif       DOUBLE_COSINE
#define     VALUES_SIZE         10
const BodyType BODY_TYPE = BodyType::double_cosine;
#endif

const btScalar DEFAULT_EXPERIMENT_INTERVAL = 0.001;
const btScalar SIMULATION_STEPS = 60 * 10; // if it's 60 the simulation is 1 second
const btScalar DIRECTION_CONSTANT = 0.02;
const btScalar VELOCITY_CONSTANT = 4.6;
const btScalar OBJETIVE_VELOCITY = 1;
const btScalar CYCLE_CONSTANT = 30;
const double HALF_PI_IN_DEGREES = 90;


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
