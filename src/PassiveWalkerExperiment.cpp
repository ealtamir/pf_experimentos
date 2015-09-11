#include <iostream>
#include <fstream>

#include <cmath>

#include <chrono>

#include "PassiveWalkerExperiment.h"
#include "GenericBodyParameters.h"

PassiveWalkerExperiment::PassiveWalkerExperiment() {
}

PassiveWalkerExperiment::~PassiveWalkerExperiment() {
	delete body;
    delete params;
}

float PassiveWalkerExperiment::getFitness(const std::vector<double> vals) {
    experiment->initPhysics();
    experiment->objectsInitialized = false;
    int i = 0;
    // left leg
    experiment->body->getBodyGroups()[0]->getBodyParts()[0]->setActuatorValues(vals[i*5+0],
                                                                               vals[i*5+1],
                                                                               vals[i*5+2],
                                                                               vals[i*5+3],
                                                                               vals[i*5+4]);
    // right leg
    experiment->body->getBodyGroups()[1]->getBodyParts()[0]->setActuatorValues(vals[i*5+0],
                                                                               vals[i*5+1],
                                                                               vals[i*5+2],
                                                                               vals[i*5+3],
                                                                               vals[i*5+4] + SIMD_PI);
    i++;
    
    // left leg
    experiment->body->getBodyGroups()[0]->getBodyParts()[1]->setActuatorValues(vals[i*5+0],
                                                                               vals[i*5+1],
                                                                               vals[i*5+2],
                                                                               vals[i*5+3],
                                                                               vals[i*5+4]);
    // right leg
    experiment->body->getBodyGroups()[1]->getBodyParts()[1]->setActuatorValues(vals[i*5+0],
                                                                               vals[i*5+1],
                                                                               vals[i*5+2],
                                                                               vals[i*5+3],
                                                                               vals[i*5+4] + SIMD_PI);
    i++;
    // hip
    experiment->body->getBodyGroups()[2]->getBodyParts()[0]->setActuatorValues(vals[i*5+0],
                                                                               vals[i*5+1],
                                                                               vals[i*5+2],
                                                                               vals[i*5+3],
                                                                               vals[i*5+4]);
    
    // run simulation
    experiment->simulate();
    
    
    double value = experiment->getHeight() * experiment->getDirection();// * experiment->getVelocity();
//    std::cout << value << std::endl;
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
//    body->cicleQuantity();
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
    double acum_cycles = 0;
    int cycles = -1;
    double* last_cycles = walker->getAnglesLegs();
    
    
    initial_position = walker->getPosition();
    initial_angle = walker->getAngleInclination();
    
    initial_height = walker->getHeight();
    initial_height-= 0.65;
    
    
    for (int i = 0; i < DEFAULT_CHANGE_COUNTER; i++) {
        worldStep();
        double t = (i+1) * DEFAULT_EXPERIMENT_INTERVAL;
        double value = walker->getHeight();
        value-= 0.68;
        acum_height += fabs(value - initial_height);
        
        
        double final_position = walker->getPosition();
        
        
        // --- cambio de la formula del informe del cuadrupedo respecto de la velocidad: la ecuacion de movimiento uniforme seria x*t, y no x*t*dt
        acum_position += fabs(final_position-(initial_position+OBJETIVE_VELOCITY*(t+DEFAULT_EXPERIMENT_INTERVAL)));
        
        // --- asi es como esta escrita la formula en el informe del cuadrupedo
        
        //acum_position += fabs(final_position-(initial_position+OBJETIVE_VELOCITY*(t*DEFAULT_EXPERIMENT_INTERVAL)));
        
        
        double angle = walker->getAngleInclination();
        acum_direction += fabs( angle );
        
        
        int new_cycles = walker->getCycleQuantity();
        if(new_cycles == cycles+1){
            double *angles= walker->getAnglesLegs();
            for(int i=0;i<BODY_PART_QTY;i++){
                acum_cycles+=fabs(angles[i]-last_cycles[i]);
            }
            free(last_cycles);
            last_cycles=angles;
            cycles++;
        }

    }
    
    
    max_height = 1 - acum_height/ ((DEFAULT_CHANGE_COUNTER) * initial_height);
    
    average_velocity = 1 - acum_position/(pow(DEFAULT_CHANGE_COUNTER,2) * VELOCITY_CONSTANT * OBJETIVE_VELOCITY * DEFAULT_EXPERIMENT_INTERVAL);
    
    //ponemos bounds entre 0 y 1
    average_velocity = fmin(1.0, fmax(0,average_velocity));
    
    
    //direction = 1 - acum_direction/(DIRECTION_CONSTANT * DEFAULT_CHANGE_COUNTER);
    
    direction = acum_direction/(DIRECTION_CONSTANT * DEFAULT_CHANGE_COUNTER);
    
    periodicity = 1 - acum_cycles/(CYCLE_CONSTANT * BODY_PART_QTY * walker->getCycleQuantity());
    
   printf("velocity final: %f \n",average_velocity);
   printf("direction final: %f \n",direction);
//    printf("height final: %f \n",max_height);
    //printf("cycle final: %f \n",periodicity);
    

}

double getDirectionAngle(double previous_position_x, double previous_position_z, double actual_position_x, double actual_position_z){
    
    double x = actual_position_x - previous_position_x;
    double z = actual_position_z - previous_position_z;
    if (x==0){
        return 0;
    }
    return (asin(fmin(1.0, fmax(-1.0,x/z)))*180/M_PI);
}

