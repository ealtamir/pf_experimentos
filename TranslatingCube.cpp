//
//  TranslatingCube.cpp
//  pf2
//
//  Created by Enzo Altamiranda G on 23.04.15.
//  Copyright (c) 2015 Enzo Altamiranda G. All rights reserved.
//

#include "TranslatingCube.h"
#include "test_constants.h"


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
    box->setLinearVelocity(btVector3(10, 0, 0));
}

void TranslatingCube::worldStep()
{
    float seconds = difftime(time(0), startTime);
    if (seconds > 0.0)
    {
        startTime = time(0);
        btTransform trans;
        box->getMotionState()->getWorldTransform(trans);
        printf("x = %f\n", trans.getOrigin().getX());
    }
}

bool TranslatingCube::stopExperiment()
{
    return condition.stopConditionMet();
}