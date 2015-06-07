//
//  Experiment.h
//  pf2
//
//  Created by Enzo Altamiranda G on 22.04.15.
//  Copyright (c) 2015 Enzo Altamiranda G. All rights reserved.
//

#ifndef __pf2__Experiment__
#define __pf2__Experiment__

#ifdef _WINDOWS
#include "Win32DemoApplication.h"
#define PlatformDemoApplication Win32DemoApplication
#else
#include "GlutDemoApplication.h"
#define PlatformDemoApplication GlutDemoApplication
#endif

#include <stdio.h>
#include <BulletDynamics/btBulletDynamicsCommon.h>
#include <time.h>
#include <string>
#include "ObjectStoppedCondition.h"

#include "Ragdoll.h"

const btScalar DEFAULT_EXPERIMENT_INTERVAL = 0.001;
const btScalar DEFAULT_CHANGE_COUNTER = 10;

class Experiment : public PlatformDemoApplication
{
protected:
    bool objectsInitialized = false;
    
public:
    RagDoll* ragDoll;
    
    int startTime;
    
    Experiment();
    
    virtual void initPhysics();
    
    virtual void clientMoveAndDisplay();
    
    virtual void displayCallback();
    
    void enableStoppingCondition(bool status) {
        stoppingConditionEnabled = status;
    }
    
    virtual std::string getName() {
        return "Experiment";
    }

    virtual void keyboardCallback(unsigned char key, int x, int y);
    
protected:
    ObjectStoppedCondition condition = NULL;
    
    btRigidBody* createGround();
    
    btRigidBody* createWall();
    
    btRigidBody* createBall();
    
    btRigidBody* createCube();
    
    RagDoll* createRagdoll();
    
    virtual void initializeBodies() = 0;
    
    virtual void initObjects() = 0;
    
    virtual void worldStep() = 0;
    
    virtual bool stopExperiment() = 0;
    
    bool stoppingConditionEnabled = true;

};


#endif /* defined(__pf2__Experiment__) */
