#include <iostream>
#include <fstream>

#include <cmath>

#include <chrono>
#include <mutex>

#include <sys/stat.h>

#include "PassiveWalkerExperiment.h"
#include "GenericBodyParameters.h"
#include "IOTools.h"

#define FIFO_PATHNAME   "/tmp/passive_walker_exp.fifo"

#define DESIRED_ZSPEED  1

#define FITNESS_EXPONENT_CONSTANT 5


std::mutex lock;

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
	delete body;
    delete params;
}

float PassiveWalkerExperiment::getFitness(const std::vector<double> vals) {
    
    double fitness = 0;
    lock.lock();
    PassiveWalkerExperiment* experiment = PassiveWalkerExperiment::getInstance();
    experiment->setBodyActuatorValues(vals);
    experiment->simulate();
    fitness = experiment->getHeight() * experiment->getDirection() * experiment->getVelocity();
    lock.unlock();
//    std::cout << "Height: " << experiment->getHeight() << std::endl;
//    std::cout << "Direction: " << experiment->getDirection() << std::endl;
//    std::cout << "Velocity: " << experiment->getVelocity() << std::endl;
//    std::cout << "Left foot height: " << experiment->getLeftFootHeight() << std::endl;
//    std::cout << "Right foot height: " << experiment->getRightFootHeight() << std::endl;
//    std::cout << "Foot correctness: " << experiment->getCorrectFootHipPosition() << std::endl;

//    return experiment->getHeight() * experiment->getDirection() * experiment->getVelocity() * experiment->getLeftFootHeight() * experiment->getRightFootHeight() * experiment->getCorrectFootHipPosition();
    
//    std::cout << "Fitness: " << experiment->getHeight() * experiment->getDirection() * experiment->getVelocity() << std::endl;
    return fitness;
}

void PassiveWalkerExperiment::initializeBodies() {
    params = new GenericBodyParameters();
    body = new WalkerBody(m_dynamicsWorld, *params);
}

void PassiveWalkerExperiment::initObjects() {
	objectsInitialized = true;
}

void PassiveWalkerExperiment::worldStep() {
    timeCount += 1. / 60.;
    btDynamicsWorld* w = getDynamicsWorld();
    w->stepSimulation(1 / 60.f);
    body->actuate(timeCount, 0);
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
    double acum_left_foot_height = 0;
    double acum_right_foot_height = 0;
    double acum_velocity = 0;
    
    double current_left_foot_height = 0;
    double current_right_foot_height = 0;

    
    double initial_angle = 0;
    double acum_direction = 0;
    
    double angle = 0;
    
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






