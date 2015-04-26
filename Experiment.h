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

const btScalar DEFAULT_EXPERIMENT_INTERVAL = 0.001;
const btScalar DEFAULT_CHANGE_COUNTER = 10;

class Experiment : public PlatformDemoApplication
{
protected:
    bool objectsInitialized = false;
    
    time_t startTime;
    
public:
    Experiment();
    
    virtual void initPhysics();
    
    virtual void clientMoveAndDisplay();
    
    virtual void displayCallback();
    
private:
    virtual void keyboardCallback(unsigned char key, int x, int y);
    
protected:
    btRigidBody* createGround();
    
    btRigidBody* createWall();
    
    btRigidBody* createBall();
    
    btRigidBody* createCube();
    
    virtual void initializeBodies() = 0;
    
    virtual void initObjects() = 0;
    
    virtual void worldStep() = 0;
    
    virtual bool stopExperiment() = 0;
};


#endif /* defined(__pf2__Experiment__) */
