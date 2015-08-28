#include <iostream>
#include <cmath>

#include "PassiveWalkerExperiment.h"
#include "GenericBodyParameters.h"

PassiveWalkerExperiment::PassiveWalkerExperiment() {
    initPhysics();
}

PassiveWalkerExperiment::~PassiveWalkerExperiment() {
	delete body;
    delete params;
}

float PassiveWalkerExperiment::getFitness(const std::vector<double> vals) {
    PassiveWalkerExperiment *experiment2 = new PassiveWalkerExperiment();
    int i = 0;
    // left leg
    experiment2->body->getBodyGroups()[0]->getBodyParts()[0]->setActuatorValues(vals[i*4+0],
                                                                               vals[i*4+1],
                                                                               vals[i*4+2],
                                                                               vals[i*4+3]);
    i++;
    experiment2->body->getBodyGroups()[0]->getBodyParts()[1]->setActuatorValues(vals[i*4+0],
                                                                               vals[i*4+1],
                                                                               vals[i*4+2],
                                                                               vals[i*4+3]);
    i++;
    
    // right leg
    experiment2->body->getBodyGroups()[1]->getBodyParts()[0]->setActuatorValues(vals[i*4+0],
                                                                               vals[i*4+1],
                                                                               vals[i*4+2],
                                                                               vals[i*4+3]);
    i++;
    experiment2->body->getBodyGroups()[1]->getBodyParts()[1]->setActuatorValues(vals[i*4+0],
                                                                               vals[i*4+1],
                                                                               vals[i*4+2],
                                                                               vals[i*4+3]);
    i++;
    // hip
    experiment2->body->getBodyGroups()[2]->getBodyParts()[0]->setActuatorValues(vals[i*4+0],
                                                                               vals[i*4+1],
                                                                               vals[i*4+2],
                                                                               vals[i*4+3]);
    
    // run simulation
    experiment2->simulate();
    
    double value = experiment2->getHeight() + experiment2->getVelocity();
    std::cout << value << std::endl;
    return value;
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
    body->actuate(timeCount);
//    printf("time: %f \n", timeCount);
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
    return average_velocity;
}

void Experiment::simulate(){
    max_height = 0;
    average_velocity = 0;
    PassiveWalkerExperiment* exp = dynamic_cast<PassiveWalkerExperiment*>(this);
    WalkerBody* walker = exp->getWalkerBody();
    double acum_height = 0;
    double initial_x_position = 0;
        
    initial_height = walker->getHeight();
    initial_x_position = walker->getPosition();
        
    for (int i = 0; i < DEFAULT_CHANGE_COUNTER; i++) {
        worldStep();
            
        double value = walker->getHeight();
        max_height += value;
        average_velocity = (initial_x_position - walker->getPosition());
    }

}

