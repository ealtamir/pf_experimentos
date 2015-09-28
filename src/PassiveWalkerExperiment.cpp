#include <iostream>
#include <fstream>

#include <cmath>

#include <chrono>

#include <sys/stat.h>

#include "PassiveWalkerExperiment.h"
#include "GenericBodyParameters.h"
#include "IOTools.h"

#define FIFO_PATHNAME   "/tmp/passive_walker_exp.fifo"


PassiveWalkerExperiment::PassiveWalkerExperiment() {

}

PassiveWalkerExperiment::~PassiveWalkerExperiment() {
	delete body;
    delete params;
}

float PassiveWalkerExperiment::getFitness(const std::vector<double> vals) {
    experiment->initPhysics();
    experiment->objectsInitialized = false;
    setWalkerActuatorValues(vals, experiment);
    
    experiment->simulate();
//    std::cout << "Height: " << experiment->getHeight() << std::endl;
//    std::cout << "Direction: " << experiment->getDirection() << std::endl;
//    std::cout << "Velocity: " << experiment->getVelocity() << std::endl;
//    std::cout << "Left foot height: " << experiment->getLeftFootHeight() << std::endl;
//    std::cout << "Right foot height: " << experiment->getRightFootHeight() << std::endl;
//    std::cout << "Foot correctness: " << experiment->getCorrectFootHipPosition() << std::endl;

    return experiment->getHeight() * experiment->getDirection() * experiment->getVelocity() * experiment->getLeftFootHeight() * experiment->getRightFootHeight() * experiment->getCorrectFootHipPosition();
}

void PassiveWalkerExperiment::initializeBodies() {
    params = new GenericBodyParameters();
    body = new WalkerBody(m_dynamicsWorld, *params);
}

void PassiveWalkerExperiment::initObjects() {
	objectsInitialized = true;
}

void PassiveWalkerExperiment::worldStep(int stage) {
    timeCount += 1. / 60.;
    btDynamicsWorld* w = getDynamicsWorld();
    w->stepSimulation(1 / 60.f);
    body->actuate(timeCount, stage);
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

void Experiment::simulate(){
    max_height = 0;
    left_foot_height = 0;
    right_foot_height = 0;
    average_velocity = 0;
    correct_foot_hip_position = 1;
    PassiveWalkerExperiment* exp = dynamic_cast<PassiveWalkerExperiment*>(this);
    WalkerBody* walker = exp->getWalkerBody();
    
    double initial_height = 0;
    double acum_height = 0;
    double acum_left_foot_height = 0;
    double acum_right_foot_height = 0;
    double acum_velocity = 0;
    
    double initial_angle = 0;
    double acum_direction = 0;
    
    for (int i = 0; i < SIMULATION_STEPS; i++) {
        if(SIMULATION_STEPS < 60) {
            worldStep(0);
        } else {
            worldStep(1);
        }
        if(i == 0) {
            initial_height = walker->getHeight();
            initial_angle = walker->getAngleInclination();
        }
        double current_height = walker->getHeight();
        acum_height += current_height;
        
        double current_left_foot_height = walker->getLeftFootHeight();
        double current_right_foot_height = walker->getRightFootHeight();
        acum_left_foot_height += current_left_foot_height;
        acum_right_foot_height += current_right_foot_height;
        
        if(current_left_foot_height >= current_height){
            correct_foot_hip_position -= 0.5 * 1/SIMULATION_STEPS;
        }
        if(current_right_foot_height >= current_height){
            correct_foot_hip_position -= 0.5 * 1/SIMULATION_STEPS;
        }
        
        btVector3 current_velocity = walker->getVelocity();
        acum_velocity += fabs(current_velocity.getZ());
        
        double angle = walker->getAngleInclination();
        acum_direction += angle;
    }
    
    max_height = 1 - fabs (1 - acum_height / ((SIMULATION_STEPS) * initial_height));
    
    if ((initial_height * 0.8 - (acum_left_foot_height / SIMULATION_STEPS)) > 0) {
        left_foot_height = 1;
    } else {
        left_foot_height = 0.1;
    }
    
    if ((initial_height * 0.8 - (acum_right_foot_height / SIMULATION_STEPS)) > 0) {
        right_foot_height = 1;
    } else {
        right_foot_height = 0.1;
    }
    
    average_velocity = (acum_velocity/SIMULATION_STEPS) / OBJETIVE_VELOCITY;
    if (average_velocity > OBJETIVE_VELOCITY) {
        average_velocity = 0.1;
    }
    
    direction = 1 - (initial_angle - (acum_direction/SIMULATION_STEPS))/180;
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

void PassiveWalkerExperiment::setWalkerActuatorValues(vector<double> vals, PassiveWalkerExperiment* experiment) {
    BodyPart* bodyPart;
    
    int LEFT_LEG = 0;
    int RIGHT_LEG = 1;
    
    int LOWER_LEG = 0;
    int UPPER_LEG = 1;
    
//    // Generic
//    // left lower leg
//    bodyPart = experiment->body->getBodyGroups()[LEFT_LEG]->getBodyParts()[LOWER_LEG];
//    bodyPart->setActuatorValues(vals[0], vals[1], vals[2], vals[3], vals[4], vals[5]);
//    
//    // left upper leg
//    bodyPart = experiment->body->getBodyGroups()[LEFT_LEG]->getBodyParts()[UPPER_LEG];
//    bodyPart->setActuatorValues(vals[6], vals[7], vals[8], vals[9], vals[10], vals[11]);
//    
//    // right lower leg
//    bodyPart = experiment->body->getBodyGroups()[RIGHT_LEG]->getBodyParts()[LOWER_LEG];
//    bodyPart->setActuatorValues(vals[0], vals[1], vals[2], vals[3], vals[4] + SIMD_PI, vals[5]);
//    
//    // right upper leg
//    bodyPart = experiment->body->getBodyGroups()[RIGHT_LEG]->getBodyParts()[UPPER_LEG];
//    bodyPart->setActuatorValues(vals[6], vals[7], vals[8], vals[9], vals[10] + SIMD_PI, vals[11]);
    
//    // Fourier
//    // left lower leg
//    bodyPart = experiment->body->getBodyGroups()[LEFT_LEG]->getBodyParts()[LOWER_LEG];
//    bodyPart->setActuatorValues(vals[0], vals[1], vals[2], vals[3], vals[4], vals[5], vals[6]);
//    
//    // left upper leg
//    bodyPart = experiment->body->getBodyGroups()[LEFT_LEG]->getBodyParts()[UPPER_LEG];
//    bodyPart->setActuatorValues(vals[7], vals[8], vals[9], vals[10], vals[11], vals[12], vals[13]);
//    
//    // right lower leg
//    bodyPart = experiment->body->getBodyGroups()[RIGHT_LEG]->getBodyParts()[LOWER_LEG];
//    bodyPart->setActuatorValues(vals[0], vals[1], vals[2], vals[3], vals[4], vals[5] + SIMD_PI, vals[6]);
//    
//    // right upper leg
//    bodyPart = experiment->body->getBodyGroups()[RIGHT_LEG]->getBodyParts()[UPPER_LEG];
//    bodyPart->setActuatorValues(vals[7], vals[8], vals[9], vals[10], vals[11], vals[12] + SIMD_PI, vals[13]);
    
    // Double frec cos
    // left lower leg
    bodyPart = experiment->body->getBodyGroups()[LEFT_LEG]->getBodyParts()[LOWER_LEG];
    bodyPart->setActuatorValues(vals[0], vals[1], vals[2], vals[3], vals[4],
                                vals[10], vals[11], vals[12], vals[13], vals[14]);
    
    // left upper leg
    bodyPart = experiment->body->getBodyGroups()[LEFT_LEG]->getBodyParts()[UPPER_LEG];
    bodyPart->setActuatorValues(vals[5], vals[6], vals[7], vals[8], vals[9],
                                vals[15], vals[16], vals[17], vals[18], vals[19]);
    
    // right lower leg
    bodyPart = experiment->body->getBodyGroups()[RIGHT_LEG]->getBodyParts()[LOWER_LEG];
    bodyPart->setActuatorValues(vals[0], vals[1], vals[2], vals[3] + SIMD_PI, vals[4],
                                vals[10], vals[11], vals[12], vals[13], vals[14]);
    
    // right upper leg
    bodyPart = experiment->body->getBodyGroups()[RIGHT_LEG]->getBodyParts()[UPPER_LEG];
    bodyPart->setActuatorValues(vals[5], vals[6], vals[7], vals[8] + SIMD_PI, vals[9],
                                vals[15], vals[16], vals[17], vals[18], vals[19]);
}





