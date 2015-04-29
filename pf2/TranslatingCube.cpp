//
//  TranslatingCube.cpp
//  pf2
//
//  Created by Enzo Altamiranda G on 23.04.15.
//  Copyright (c) 2015 Enzo Altamiranda G. All rights reserved.
//

#include "TranslatingCube.h"
#include "test_constants.h"


TranslatingCube::TranslatingCube()
{
    
}

void TranslatingCube::initializeBodies()
{
    box = createCube();
    ground = createGround();
    
    box->setFriction(BOX_FRICTION);
    ground->setFriction(GROUND_FRICTION);
    
    condition = ObjectStoppedCondition(box);
}

void TranslatingCube::initObjects()
{
    objectsInitialized = true;
    box->activate(true);
    box->setLinearVelocity(BOX_INITIAL_VEL);
}

void TranslatingCube::worldStep()
{
    if (!stopExperiment()) {
        startTime = time(0);
        btTransform trans;
        box->getMotionState()->getWorldTransform(trans);
        printf("%f\n", trans.getOrigin().getX());
    } else if (stoppingConditionEnabled) {
        exit(0);
    }
}

bool TranslatingCube::stopExperiment()
{
    return condition.stopConditionMet();
}