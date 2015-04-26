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
}


void FallingBall::initObjects() {
    ball->activate(true);
    ball->setLinearVelocity(btVector3(0, -5, 0));
    objectsInitialized = true;
}

void FallingBall::worldStep() {
    float seconds = difftime(time(0), startTime);
    if (seconds > 0.1)
    {
        startTime = time(0);
        printf("speedY: %f\n", ball->getLinearVelocity().getY());
    }
}