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
    
    
    double value = experiment2->getHeight() * experiment2->getVelocity() * experiment2->getDirection();
    printf("la velocity es: %f\n",experiment2->getVelocity());
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

double Experiment::getDirection() const {
    return average_velocity;
}

void Experiment::simulate(){
    max_height = 0;
    average_velocity = 0;
    PassiveWalkerExperiment* exp = dynamic_cast<PassiveWalkerExperiment*>(this);
    WalkerBody* walker = exp->getWalkerBody();
    double acum_height = 0;
    
    double initial_position = 0;
    double acum_position = 0;
    double acum_direction = 0;
    double initial_angle = 0;
    
    
    initial_height = walker->getHeight();
    initial_position = walker->getPosition();
    initial_angle = walker->getAngleInclination();
    
    printf("position inicial: %f \n",initial_position);
        
    for (int i = 0; i < DEFAULT_CHANGE_COUNTER; i++) {
        worldStep();
        double t = (i+1) * DEFAULT_EXPERIMENT_INTERVAL;
        double value = walker->getHeight();
        acum_height += fabs(value - initial_height);
        
        double final_position = walker->getPosition();
        
        acum_position += fabs(final_position-(initial_position+OBJETIVE_VELOCITY*t*DEFAULT_EXPERIMENT_INTERVAL));
        average_velocity = (final_position - initial_position);
        
        double angle = walker->getAngleInclination();
        acum_direction += fabs( angle - initial_angle);
    }
    max_height = 1 - acum_height/ (DEFAULT_CHANGE_COUNTER * initial_height);
    
    average_velocity = 1 - acum_position/(pow(DEFAULT_CHANGE_COUNTER,2) * VELOCITY_CONSTANT * OBJETIVE_VELOCITY * DEFAULT_EXPERIMENT_INTERVAL);
    
    direction = 1 - acum_direction/(DIRECTION_CONSTANT * DEFAULT_CHANGE_COUNTER);
    
    printf("velocity final: %f \n",average_velocity);
    printf("inclination final: %f \n",direction);
    printf("height final: %f \n",max_height);

}

