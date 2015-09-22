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
    
    // run simulation
    experiment->simulate();
    double value = experiment->getHeight();// * experiment->getDirection() * experiment->getVelocity();
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
//    body->actuate(timeCount);
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
    const btVector3& velocity_obj = btVector3(0, 0, OBJETIVE_VELOCITY);
    
    double initial_position = 0;
    double acum_position = 0;
    double acum_direction = 0;
    double initial_angle = 0;
    double acum_cycles = 0;
    
    initial_position = walker->getPosition();
    initial_angle = walker->getAngleInclination();
    
    for (int i = 0; i < DEFAULT_CHANGE_COUNTER; i++) {
        worldStep();
        if(i == 0) { initial_height = walker->getHeight(); }
        acum_height += walker->getHeight();
        
        btVector3 final_position = walker->getVelocity();
        
        acum_position += fabs(final_position.norm() - velocity_obj.norm());
        
        // --- esto era lo que teníamos que mezclaba módulo de velocidad y dirección en un mismo valor
        //acum_position += fabs(final_position.distance(velocity_obj));
        
        // --- cambio de la formula del informe del cuadrupedo respecto de la velocidad: la ecuacion de movimiento uniforme seria x*t, y no x*t*dt
        //acum_position += fabs(final_position-(initial_position+OBJETIVE_VELOCITY*(t+DEFAULT_EXPERIMENT_INTERVAL)));
        
        // --- asi es como esta escrita la formula en el informe del cuadrupedo
        
        //acum_position += fabs(final_position-(initial_position+OBJETIVE_VELOCITY*(t*DEFAULT_EXPERIMENT_INTERVAL)));
        
        
        double angle = walker->getAngleInclination()-90;
        printf("angulo: %f\n",angle);
        acum_direction += fabs( angle );
        
        
     /* int new_cycles = walker->getCycleQuantity();
        if(new_cycles == cycles+1){
            double *angles= walker->getAnglesLegs();
            for(int i=0;i<BODY_PART_QTY;i++){
                acum_cycles+=fabs(angles[i]-last_cycles[i]);
            }
            free(last_cycles);
            last_cycles=angles;
            cycles++;
        }
         */
    }
    
    
    max_height = 1 - fabs (1 - acum_height/ ((DEFAULT_CHANGE_COUNTER) * initial_height));
    
    
    acum_position = acum_position/DEFAULT_CHANGE_COUNTER;
    
    average_velocity = 1 - fabs(tanh((1.2*acum_position)));
    
    //average_velocity = 1 - acum_position/(pow(DEFAULT_CHANGE_COUNTER,2) * VELOCITY_CONSTANT * DEFAULT_EXPERIMENT_INTERVAL);
    
    
    //average_velocity = 1 - acum_position/(pow(DEFAULT_CHANGE_COUNTER,2) * VELOCITY_CONSTANT * OBJETIVE_VELOCITY * DEFAULT_EXPERIMENT_INTERVAL);
    
    //ponemos bounds entre 0 y 1
    //average_velocity = fmin(1.0, fmax(0,average_velocity));
    
    //por ahora la velocity del fitness va a estar entre 1 y menos infinito, porque siempre está dando negativa (y dejarla en cero va a ser muy malo para el GA)
    
    //average_velocity = fmin(1.0, average_velocity);
    
    
    
    direction = 1 - fabs(tanh(DIRECTION_CONSTANT*(acum_direction/(DEFAULT_CHANGE_COUNTER))));
    //printf("diferencias de angulo acumulada: %f\n",acum_direction);
    
    periodicity = 1 - acum_cycles/(CYCLE_CONSTANT * BODY_PART_QTY * walker->getCycleQuantity());
    
   printf("velocity final: %f \n",average_velocity);
    printf("direction final: %f \n",direction);
    printf("height final: %f \n",max_height);
    //printf("cycle final: %f \n",periodicity);
    

}

double getDirectionAngle(double previous_position_x, double previous_position_z,
                         double actual_position_x, double actual_position_z) {
    
    double x = actual_position_x - previous_position_x;
    double z = actual_position_z - previous_position_z;
    if (x==0){
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
    bodyPart->setActuatorValues(vals[0], vals[1], vals[2], vals[3], vals[4]);
    
    // left upper leg
    bodyPart = experiment->body->getBodyGroups()[LEFT_LEG]->getBodyParts()[UPPER_LEG];
    bodyPart->setActuatorValues(vals[5], vals[6], vals[7], vals[8], vals[9]);
    
    // right lower leg
    bodyPart = experiment->body->getBodyGroups()[RIGHT_LEG]->getBodyParts()[LOWER_LEG];
    bodyPart->setActuatorValues(vals[0], vals[1], vals[2], vals[3] + SIMD_PI, vals[4]);
    
    // right upper leg
    bodyPart = experiment->body->getBodyGroups()[RIGHT_LEG]->getBodyParts()[UPPER_LEG];
    bodyPart->setActuatorValues(vals[5], vals[6], vals[7], vals[8] + SIMD_PI, vals[9]);
}





