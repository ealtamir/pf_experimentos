#include <iostream>

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


void Experiment::simulate(){
    if (!simulated) {
        for (int i = 0; i < 10; i++) {
            worldStep();
            PassiveWalkerExperiment* exp = dynamic_cast<PassiveWalkerExperiment*>(this);
            double value = exp->getWalkerBody()->getHeight();
            max_height = (value>max_height)? value : max_height;
            std::cout << "altura? " << value << std::endl;
            
        }
    }
    simulated = true;
}



