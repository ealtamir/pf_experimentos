//
//  BallWallCollision.cpp
//  pf2
//
//  Created by Enzo Altamiranda G on 22.04.15.
//  Copyright (c) 2015 Enzo Altamiranda G. All rights reserved.
//

#include "BallWallCollision.h"
#include "test_constants.h"

void BallWallCollision::initializeBodies()
{
    ball = createBall();
    wall = createWall();
    createGround();
    
    ball->setFriction(BALL_FRICTION);
    ball->setRestitution(BALL_RESTITUTION);
    
    wall->setFriction(WALL_FRICTION);
    wall->setRestitution(WALL_RESTITUTION);
}

void BallWallCollision::initObjects()
{
    objectsInitialized = true;
    ball->activate(true);
    ball->setLinearVelocity(btVector3(7 / 10., 1 / 10., 10 / 10.));
}

void BallWallCollision::worldStep()
{
    float seconds = difftime(time(0), startTime);
    if (seconds > 0.1)
    {
        startTime = time(0);
        btVector3 v = ball->getLinearVelocity();
        printf("x = %f, y = %f, z = %f\n", v.getX(), v.getY(), v.getZ());
    }
}