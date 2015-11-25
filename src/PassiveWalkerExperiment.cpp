#include <iostream>
#include <fstream>

#include <cmath>

#include <chrono>
#include <mutex>

#include <sys/stat.h>

#include "PassiveWalkerExperiment.h"
#include "GenericBodyParameters.h"
#include "GenericBody.h"

#include "FourierBodyParameters.h"
#include "FourierBody.h"

#include "CosineDoubleFrecBodyParameters.h"
#include "CosineDoubleFrecBody.h"

#include "IOTools.h"

#define FIFO_PATHNAME   "/tmp/passive_walker_exp.fifo"

#define DESIRED_ZSPEED  1

#define FITNESS_EXPONENT_CONSTANT 5

#define FIRST_STEP_TIME 0.5

std::mutex fitnessLock;

PassiveWalkerExperiment* PassiveWalkerExperiment::walkerInstance;

PassiveWalkerExperiment* PassiveWalkerExperiment::getInstance() {
    if (walkerInstance == nullptr) {
        walkerInstance = new PassiveWalkerExperiment();
        walkerInstance->initPhysics();
    }
    return walkerInstance;
}

PassiveWalkerExperiment::PassiveWalkerExperiment() {}

PassiveWalkerExperiment::~PassiveWalkerExperiment() {
	delete selectedBody;
    delete params;
}

float PassiveWalkerExperiment::getFitness(const std::vector<double> vals) {
    double fitness = 0;
    fitnessLock.lock();
    PassiveWalkerExperiment* experiment = PassiveWalkerExperiment::getInstance();
    WalkerBody* body = experiment->selectedBody;
    body->setActuatorValues(vals);
    experiment->simulate();
    fitness = experiment->getHeight() * experiment->getDirection() * experiment->getVelocity();
    fitnessLock.unlock();

    return fitness;
}

void PassiveWalkerExperiment::initializeBodies() {
    if (BODY_TYPE == BodyType::generic) {
        params = new GenericBodyParameters(firstStepActuator);
        selectedBody = new GenericBody(m_dynamicsWorld, *params);
    } else if (BODY_TYPE == BodyType::fourier) {
        params = new FourierBodyParameters(firstStepActuator);
        selectedBody = new FourierBody(m_dynamicsWorld, *params);
    } else {
        params = new CosineDoubleFrecBodyParameters(firstStepActuator);
        selectedBody = new CosineDoubleFrecBody(m_dynamicsWorld, *params);
    }
}

void PassiveWalkerExperiment::initObjects() {
	objectsInitialized = true;
}

void PassiveWalkerExperiment::worldStep() {
    btDynamicsWorld* w = getDynamicsWorld();
    w->stepSimulation(1 / 60.f, 10, 1 / 500.);
    int stageValue = 0;
    if(timeCount <= FIRST_STEP_TIME) {
        stageValue = 0;
    } else {
        stageValue = 1;
    }
    selectedBody->actuate(timeCount, stageValue);
    timeCount += 1. / 60.;
}

bool PassiveWalkerExperiment::stopExperiment() {
	return false;
}



double Experiment::getHeight() const {
    return max_height;
}

double Experiment::getVelocity() const {
    return average_velocity;
}

double Experiment::getDirection() const {
    return direction;
}

double Experiment::getLeftFootHeight() const {
    return left_foot_height;
}

double Experiment::getRightFootHeight() const {
    return right_foot_height;
}

double Experiment::getCorrectFootHipPosition() const {
    return correct_foot_hip_position;
}

double PassiveWalkerExperiment::getHeightCoefficient(double h,
                                                     double min_h,
                                                     double optimal_h) {
    
    double diff = optimal_h - h;
    return 1 / exp(diff * diff * FITNESS_EXPONENT_CONSTANT);
}

double PassiveWalkerExperiment::getVelocityCoefficient(btVector3& current_velocity, double desiredZspeed) {
    double diff = current_velocity.norm() - desiredZspeed;
    return 1 / exp(diff * diff * FITNESS_EXPONENT_CONSTANT);
    
}

double PassiveWalkerExperiment::getAngleCoefficient(btVector3& normalizedVel) {
    btVector3 desiredDir(0, 0, -1);
    double cosineVal = normalizedVel.dot(desiredDir);
    double diff = cosineVal - 1;
    return 1 / exp(diff * diff * FITNESS_EXPONENT_CONSTANT);
}


void PassiveWalkerExperiment::simulate() {
    max_height = 0;
    left_foot_height = 0;
    right_foot_height = 0;
    average_velocity = 0;
    correct_foot_hip_position = 1;
    PassiveWalkerExperiment* exp = this;
    WalkerBody* walker = dynamic_cast<WalkerBody*>(exp->getWalkerBody());
    
    double initial_height = 0;
    double acum_height = 0;
    double current_height = 0;
    double min_height = 0.649991;
    double acum_velocity = 0;
    
    double initial_angle = 0;
    double acum_direction = 0;
        
    worldStep();
    initial_height = walker->getHeight();
    initial_angle = walker->getAngleInclination();
    
    exp->objectsInitialized = false;
    exp->clientResetScene();

    for (int i = 0; i < SIMULATION_STEPS; i++) {
        worldStep();

        // Height Fitness
        current_height = walker->getHeight();
        acum_height += getHeightCoefficient(current_height, min_height, initial_height);
        
        // Velocity Fitness
        btVector3 current_velocity = walker->getVelocity();
        acum_velocity += getVelocityCoefficient(current_velocity,
                                                DESIRED_ZSPEED);
        // Angle Fitness
        if (current_velocity != btVector3(0, 0, 0)) {
            current_velocity.normalize();
            acum_direction += getAngleCoefficient(current_velocity);
        }

    }
    
    max_height = acum_height / SIMULATION_STEPS;
    average_velocity = acum_velocity / SIMULATION_STEPS;
    direction = acum_direction / SIMULATION_STEPS;
    timeCount = 0;
}

double getDirectionAngle(double previous_position_x, double previous_position_z,
                         double actual_position_x, double actual_position_z) {
    
    double x = actual_position_x - previous_position_x;
    double z = actual_position_z - previous_position_z;
    if (x == 0){
        return 0;
    }
    return (asin(fmin(1.0, fmax(-1.0,x/z)))*180/M_PI);
     
}

