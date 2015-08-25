#include <iostream>
#include <cmath>

#include "PassiveWalkerExperiment.h"
#include "GenericBodyParameters.h"

PassiveWalkerExperiment::PassiveWalkerExperiment() {
    initPhysics();
    simulate();
}

PassiveWalkerExperiment::~PassiveWalkerExperiment() {
	delete body;
    delete params;
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
//    body->actuate(timeCount);
    printf("time: %f \n", timeCount);
    
}

bool PassiveWalkerExperiment::stopExperiment() {
	return false;
}

WalkerBody* PassiveWalkerExperiment::getWalkerBody() {
    return body;
}


double Experiment::getHeight() const {
    return max_height;
}

double Experiment::getVelocity() const {
    return max_height;
}

void Experiment::simulate(){
    if (!simulated) {
        PassiveWalkerExperiment* exp = dynamic_cast<PassiveWalkerExperiment*>(this);
        WalkerBody* walker = exp->getWalkerBody();
        double acum_height = 0;
        double initial_x_position = 0;
        
        initial_height = walker->getHeight();
        initial_x_position = walker->getPosition();
        
        for (int i = 0; i < DEFAULT_CHANGE_COUNTER; i++) {
            worldStep();

            exp->getWalkerBody()->actuate(i);
                
            double value = walker->getHeight();
            acum_height += std::abs(value - initial_height);
                std::cout << "altura? " << value << std::endl;
            
        
        
        std::cout << "altura inicial " << initial_height << std::endl;
        max_height = 1 - acum_height/ (DEFAULT_CHANGE_COUNTER*initial_height);
        this->average_velocity = (initial_x_position - walker->getPosition()) / (DEFAULT_CHANGE_COUNTER*DEFAULT_EXPERIMENT_INTERVAL);
        std::cout << "velocity " << average_velocity << std::endl;
        }
    simulated = true;
    }

}

