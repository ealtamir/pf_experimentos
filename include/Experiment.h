//
//  Experiment.h
//  pf2
//
//  Created by Enzo Altamiranda G on 22.04.15.
//  Copyright (c) 2015 Enzo Altamiranda G. All rights reserved.
//

#ifndef __pf2__Experiment__
#define __pf2__Experiment__

#include <stdio.h>
#include <time.h>
#include <string>
#include <vector>


#include <BulletDynamics/btBulletDynamicsCommon.h>
#include "GlutDemoApplication.h"
#include "WalkerBody.h"

#include "ObjectStoppedCondition.h"

const btScalar DEFAULT_EXPERIMENT_INTERVAL = 0.001;
const btScalar SIMULATION_STEPS = 60 * 3; // if it's 60 the simulation is 1 second
const btScalar DIRECTION_CONSTANT = 0.02;
const btScalar VELOCITY_CONSTANT = 4.6;
const btScalar OBJETIVE_VELOCITY = 1;
const btScalar CYCLE_CONSTANT = 30;
const double HALF_PI_IN_DEGREES = 90;



class Experiment : public GlutDemoApplication
{
public:
    Experiment();
    virtual ~Experiment();

    virtual void initPhysics();

    virtual void clientMoveAndDisplay();

    virtual void displayCallback();
    
    virtual void worldStep() = 0;
    
    virtual void simulate() = 0;
    
    virtual double getHeight() const;
    
    virtual double getVelocity() const;
    
    virtual double getDirection() const;
    
    virtual double getLeftFootHeight() const;
    
    virtual double getRightFootHeight() const;
    
    virtual double getCorrectFootHipPosition() const;
    
    std::string getName() {
        return "Experiment";
    }
    
    WalkerBody* getWalkerBody() {return selectedBody;}
    
    WalkerBody* selectedBody;
    
    
    bool objectsInitialized = false;
    
    double timeCount = 0;
    
    virtual void setBodyActuatorValues(std::vector<double> vals);

private:
    btRigidBody* createGround();
    
protected:
    
    bool simulated = false;
    
    double max_height = -1;
    
    double average_velocity = -1;
    
    double direction = -1;
    
    double left_foot_height = -1;
    
    double right_foot_height = -1;
    
    double correct_foot_hip_position = -1;
    
    virtual void initializeBodies() = 0;

    virtual void initObjects() = 0;

    virtual bool stopExperiment() = 0;

    virtual void keyboardCallback(unsigned char key, int x, int y);

};


#endif /* defined(__pf2__Experiment__) */
