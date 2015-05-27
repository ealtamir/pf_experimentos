//
//  FallingBall.cpp
//  pf2
//
//  Created by Enzo Altamiranda G on 22.04.15.
//  Copyright (c) 2015 Enzo Altamiranda G. All rights reserved.
//

#include "FallingBall.h"
#include "test_constants.h"


void FallingBall::initializeBodies() {
    ground = createGround();
    ball = createBall();
    
    ball->setFriction(BALL_FRICTION);
    ball->setRestitution(BALL_RESTITUTION);
        
    ground->setFriction(GROUND_FRICTION);
    ground->setRestitution(GROUND_RESTITUTION);
    
    condition = ObjectStoppedCondition(ball);
    ball->setDamping(0, 0);
}


void FallingBall::initObjects() {
    ball->activate(true);
    ball->setLinearVelocity(BALL_VELOCITY);
    objectsInitialized = true;
}

void FallingBall::worldStep() {
    float seconds = difftime(time(0), startTime);
    bool ignoreStopCondition = true;
    if (!stopExperiment() || ignoreStopCondition)
    {
        startTime = time(0);
        printf("V_y: %f\n", ball->getLinearVelocity().getY());
    }
    ball->activate(true);
}

bool FallingBall::stopExperiment()
{
    return condition.stopConditionMet();
}