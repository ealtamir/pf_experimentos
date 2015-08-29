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

#include <BulletDynamics/btBulletDynamicsCommon.h>
#include "GlutDemoApplication.h"

#include "ObjectStoppedCondition.h"

const btScalar DEFAULT_EXPERIMENT_INTERVAL = 0.001;
const btScalar DEFAULT_CHANGE_COUNTER = 60*1000;

class Experiment : public GlutDemoApplication
{
public:
    Experiment();
    virtual ~Experiment();

    virtual void initPhysics();

    virtual void clientMoveAndDisplay();

    virtual void displayCallback();

    void enableStoppingCondition(bool status) {
        stoppingConditionEnabled = status;
    }
    
    virtual void worldStep() = 0;
    
    virtual void simulate();
    
    virtual double getHeight() const;
    
    virtual double getVelocity() const;
    
    virtual double getDirection() const;
    
    
    std::string getName() {
        return "Experiment";
    }

private:
    btRigidBody* createGround();
    

protected:
    bool objectsInitialized = false;
    bool stoppingConditionEnabled = true;
    
    double timeCount = 0;

    bool simulated = false;
    
    double max_height = -1; // Es uno de los parametros de la posible funcion de fitness, es la altura

    double initial_height = -1; // altura inicial de la pelvis (se usa en altura)
    
    double average_velocity = -1; // Es el parametro principal de la posible funcion de fitness, es la velocidad
    
    double direction = -1; // Es uno de los parametros de la posible funcion de fitness, es la dirección
    
    virtual void initializeBodies() = 0;

    virtual void initObjects() = 0;

    virtual bool stopExperiment() = 0;

    virtual void keyboardCallback(unsigned char key, int x, int y);

};


#endif /* defined(__pf2__Experiment__) */
