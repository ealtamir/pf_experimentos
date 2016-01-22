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

#include "ExtraFourierBody.h"
#include "ExtraFourierBodyParameters.h"

#include "IOTools.h"

#define FIFO_PATHNAME   "/tmp/passive_walker_exp.fifo"

#define FITNESS_EXPONENT_CONSTANT 5


#define FIRST_STEP_TIME 0.7

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
    PassiveWalkerExperiment* experiment = PassiveWalkerExperiment::getInstance();
    WalkerBody* body = experiment->selectedBody;
    body->setActuatorValues(vals);
    if(RIEL){
        experiment->setConstantRiel(vals.at(vals.size()-1));
    }
    experiment->simulate();
    fitness = experiment->getHeight() * experiment->getVelocity() *
    experiment->getDirection() * experiment->feet_symmetry *
              experiment->feet_hip_treshold;
//    cout << "Fitnes: " << fitness << endl;
    return fitness;
}

void PassiveWalkerExperiment::initializeBodies() {
    if (BODY_TYPE == BodyType::generic) {
        params = new GenericBodyParameters(firstStepActuator);
        selectedBody = new GenericBody(m_dynamicsWorld, *params);
        
    } else if (BODY_TYPE == BodyType::fourier) {
        params = new FourierBodyParameters(firstStepActuator);
        selectedBody = new FourierBody(m_dynamicsWorld, *params);
        
    } else if (BODY_TYPE == BodyType::double_cosine) {
        params = new CosineDoubleFrecBodyParameters(firstStepActuator);
        selectedBody = new CosineDoubleFrecBody(m_dynamicsWorld, *params);
        
    } else {
        params = new ExtraFourierBodyParameters();
        selectedBody = new ExtraFourierBody(m_dynamicsWorld, *params);
    }
}

void PassiveWalkerExperiment::setConstantRiel(double constant){
    this->constantRiel = constant;
}

void PassiveWalkerExperiment::initObjects() {
	objectsInitialized = true;
}

void PassiveWalkerExperiment::worldStep() {
    //int k=100;
//    cout << selectedBody->getHeight() << endl;
    if (timeCount > 5)
        return;
    btDynamicsWorld* w = getDynamicsWorld();
    w->stepSimulation(1 / 60.f, 10, 1 / 480.);
    int stageValue = 0;
    if(timeCount <= FIRST_STEP_TIME) {
        stageValue = 0;
        
        //empujon en la pelvis
        if(PELVIS_EMPUJON){
            btRigidBody* rb = selectedBody->getHip()->getRigidBody();
            rb->applyForce(btVector3(0, 0, -100), btVector3(0, 0, 0));
        }
    } else {
        stageValue = 1;
    }

    selectedBody->actuate(timeCount, stageValue);
    
    if(initialHeight<0){
        initialHeight= selectedBody->getHeight();
    }
    else{
        
        btRigidBody* rb = selectedBody->getHip()->getRigidBody();
        double delta_l = (selectedBody->getHeight()-initialHeight);
        rb->applyForce(btVector3(0, -constantRiel*delta_l, 0), btVector3(0, 0, 0));
        
    }
    
    
//    cout << selectedBody->getHeight() << endl;;
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
    return 1 / exp(diff * diff * FITNESS_EXPONENT_CONSTANT*2);
}

double PassiveWalkerExperiment::getVelocityCoefficient(btVector3& current_velocity, double desiredZspeed) {
    double diff = current_velocity.norm() - desiredZspeed;
    return 1 / exp(diff * diff * FITNESS_EXPONENT_CONSTANT*4);    
}

double PassiveWalkerExperiment::getAngleCoefficient(btVector3& normalizedVel) {
    btVector3 desiredDir(0, 0, -1);
    double cosineVal = normalizedVel.dot(desiredDir);
    double diff = cosineVal - 1;
    return 1 / exp(diff * diff * FITNESS_EXPONENT_CONSTANT*4);
}

double PassiveWalkerExperiment::getFeetSimmetry() {
    double leftFootZ, leftFootX;
    double rightFootZ, rightFootX;
    double hipZ, hipX;
    double diffZ, diffX;
    double valZ, valX;
    btRigidBody* leftFoot = selectedBody->getLeftFoot()->getRigidBody();
    btRigidBody* rightFoot = selectedBody->getRightFoot()->getRigidBody();
    btRigidBody* hip = selectedBody->getHip()->getRigidBody();
    
    btVector3 position;
    position = leftFoot->getCenterOfMassPosition();
    leftFootZ = position.z();
    leftFootX = position.x();
    
    position = rightFoot->getCenterOfMassPosition();
    rightFootZ = position.z();
    rightFootX = position.x();
    
    position = hip->getCenterOfMassPosition();
    hipZ = position.z();
    hipX = position.x();
    
    diffZ = abs(leftFootZ - hipZ + rightFootZ - hipZ);
    diffX = abs(leftFootX - hipX + rightFootX - hipX);
    valX = 1 / exp(diffX * diffX * FITNESS_EXPONENT_CONSTANT);
    valZ = 1 / exp(diffZ * diffZ * FITNESS_EXPONENT_CONSTANT);
    return (valX + valZ) / 2;
}

double PassiveWalkerExperiment::getFeetBelowHipCoefficient(double initial_foot_pos, double initial_hip_pos) {
    btRigidBody* leftFoot = selectedBody->getLeftFoot()->getRigidBody();
    btRigidBody* rightFoot = selectedBody->getRightFoot()->getRigidBody();
    btRigidBody* hip = selectedBody->getHip()->getRigidBody();
    double hip_h, leftFoot_h, rightFoot_h;
    hip_h = hip->getCenterOfMassPosition().y();
    leftFoot_h = leftFoot->getCenterOfMassPosition().y();
    rightFoot_h = rightFoot->getCenterOfMassPosition().y();
    
    if (hip_h <= leftFoot_h || hip_h <= rightFoot_h) {
        return 0;
    }
    
    double diff_left_foot = leftFoot_h - initial_foot_pos;
    double diff_right_foot = rightFoot_h - initial_foot_pos;
    double left_foot_score = 1 / exp(diff_left_foot * diff_left_foot * FITNESS_EXPONENT_CONSTANT);
    double right_foot_score = 1 / exp(diff_right_foot * diff_right_foot * FITNESS_EXPONENT_CONSTANT);
    
    return (left_foot_score + right_foot_score) / 2;
}


void PassiveWalkerExperiment::simulate() {
    initialHeight = -1; //para worldstep
    
    max_height = 0;
    left_foot_height = 0;
    right_foot_height = 0;
    average_velocity = 0;
    correct_foot_hip_position = 1;
    PassiveWalkerExperiment* exp = this;
    WalkerBody* walker = dynamic_cast<WalkerBody*>(exp->getWalkerBody());
    
    double temp = 0;
    
    double initial_height = 0;
    double acum_height = 0;
    double current_height = 0;
    double min_height = 0.649991;
    double acum_velocity = 0;
    
    double initial_angle = 0;
    double acum_direction = 0;
    double acum_feet_symmetry = 0;
    
    double initial_foot_position;
    double feet_val = 0;
    
    
    worldStep();
    initial_height = walker->getHeight();
    initial_angle = walker->getAngleInclination();
    initial_foot_position = selectedBody->getLeftFoot()->getRigidBody()->getCenterOfMassPosition().y();
    
//    cout << "initial height: " << initial_height << endl;
    
    exp->clientResetScene();
    exp->objectsInitialized = false;
//    cout << "Altura de la cadera" << endl;
//    cout << "Velocidad" << endl;
//    cout << "Direccion" << endl;


    for (int i = 0; i < SIMULATION_STEPS; i++) {
        worldStep();

        // Height Fitness
        current_height = walker->getHeight();
//        cout << current_height << endl;
        acum_height += getHeightCoefficient(current_height, min_height, initial_height);
        
        // Velocity Fitness
        btVector3 current_velocity = walker->getVelocity();
//        cout << current_velocity.x()<<"," << current_velocity.y()<<","<< current_velocity.z() << endl;
        acum_velocity += getVelocityCoefficient(current_velocity, TARGET_SPEED);
        // Angle Fitness
        if (current_velocity != btVector3(0, 0, 0)) {
            current_velocity.normalize();
            acum_direction += getAngleCoefficient(current_velocity);
        }

        acum_feet_symmetry += getFeetSimmetry();
        temp = getFeetBelowHipCoefficient(initial_foot_position, initial_height);
        
        feet_val += temp;
        
//        cout << temp << endl;
    }
    
    
    max_height = acum_height / SIMULATION_STEPS;
    average_velocity = acum_velocity / SIMULATION_STEPS;
    direction = acum_direction / SIMULATION_STEPS;
    feet_symmetry = acum_feet_symmetry / SIMULATION_STEPS;
    
    feet_hip_treshold = feet_val / SIMULATION_STEPS;
        
    timeCount = 0;
    exp->clientResetScene();
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

