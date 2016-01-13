#ifndef PASSIVEWALKEREXPERIMENT_H_INCLUDED
#define PASSIVEWALKEREXPERIMENT_H_INCLUDED

#include <vector>

#include "Experiment.h"
#include "WalkerBody.h"
#include "Actuator.h"
#include "GenericActuator.h"
#include "FourierActuator.h"
#include "CosineDoubleFrecActuator.h"
#include "ExtraFourierActuator.h"

enum BodyType {
    generic, fourier, double_cosine, extra_fourier
};

// PARAMETERS
#define POPULATION_SIZE             10
#define GENERATIONS                 20
#define GENOME_MUTATION             0.3
#define REPLACEMENT_PORCENTAGE      0.7
#define LAST_RESULTS                false

// FIRST STEP
#define     FIRST_STEP_GENERIC             1
//#define     FIRST_STEP_FOURIER             1
//#define     FIRST_STEP_DOUBLE_COSINE       1

// SECOND STEP
//#define     GENERIC             1
//#define     FOURIER             1
#define     DOUBLE_COSINE       1
//#define     EXTRA_FOURIER             1

#if FIRST_STEP_GENERIC
#define FIRST_STEP_VALUES_SIZE  12
#define FIRST_STEP_ACTUATOR_SIZE 24

#elif FIRST_STEP_FOURIER
#define FIRST_STEP_VALUES_SIZE  14
#define FIRST_STEP_ACTUATOR_SIZE 14

#elif FIRST_STEP_DOUBLE_COSINE
#define FIRST_STEP_VALUES_SIZE  10
#define FIRST_STEP_ACTUATOR_SIZE 10

#else
#define FIRST_STEP_VALUES_SIZE 0
#endif


#ifdef      GENERIC
#define     VALUES_SIZE         (12 + (FIRST_STEP_VALUES_SIZE))
const BodyType BODY_TYPE = BodyType::generic;
#define SECOND_STEP_ACTUATOR_SIZE 12;

#elif       FOURIER
#define     VALUES_SIZE         (14 + (FIRST_STEP_VALUES_SIZE))
const BodyType BODY_TYPE = BodyType::fourier;
#define SECOND_STEP_ACTUATOR_SIZE 14;

#elif       DOUBLE_COSINE
#define     VALUES_SIZE         (10 + (FIRST_STEP_VALUES_SIZE))
const BodyType BODY_TYPE = BodyType::double_cosine;
#define SECOND_STEP_ACTUATOR_SIZE 10;

#elif       EXTRA_FOURIER
#define     VALUES_SIZE         (42 + (FIRST_STEP_VALUES_SIZE))
const BodyType BODY_TYPE = BodyType::extra_fourier;
#endif

const int ACTUATOR_SIZE = FIRST_STEP_ACTUATOR_SIZE + SECOND_STEP_ACTUATOR_SIZE;

const btScalar DEFAULT_EXPERIMENT_INTERVAL = 0.001;
const btScalar SIMULATION_STEPS = 60 * 5; // if it's 60 the simulation is 1 second
const btScalar DIRECTION_CONSTANT = 0.02;
const btScalar VELOCITY_CONSTANT = 4.6;
const btScalar TARGET_SPEED = 2;
const btScalar CYCLE_CONSTANT = 30;
const double HALF_PI_IN_DEGREES = 90;

class PassiveWalkerExperiment : public Experiment {

public:
    
#if FIRST_STEP_GENERIC
    Actuator *firstStepActuator = new GenericActuator();
#elif FIRST_STEP_FOURIER
    Actuator *firstStepActuator = new FourierActuator();
#elif FIRST_STEP_DOUBLE_COSINE
    Actuator *firstStepActuator = new CosineDoubleFrecActuator();
#endif
    
    ~PassiveWalkerExperiment();
    
    static float getFitness(const std::vector<double> vals);
    
    static void setWalkerActuatorValues(std::vector<double> vals,
                                        Body* walkerExperiment);
    virtual void simulate();
    
    static PassiveWalkerExperiment* getInstance();
    
    virtual void worldStep();

    
private:
    PassiveWalkerExperiment();
    
    static PassiveWalkerExperiment* walkerInstance;
    
    BodyParameters* params{};
    
    double getHeightCoefficient(double h, double min_h, double optimal_h);
    
    double getVelocityCoefficient(btVector3& current_velocity, double desiredZspeed);
    
    double getAngleCoefficient(btVector3& normalizedVel);
    
    double getFeetSimmetry();
	    
protected:
        
	virtual void initializeBodies();

	virtual void initObjects();

	virtual bool stopExperiment();
    
};
#endif
