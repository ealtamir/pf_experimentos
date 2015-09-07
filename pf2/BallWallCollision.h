//
//  BallWallCollision.h
//  pf2
//
//  Created by Enzo Altamiranda G on 22.04.15.
//  Copyright (c) 2015 Enzo Altamiranda G. All rights reserved.
//

#ifndef __pf2__BallWallCollision__
#define __pf2__BallWallCollision__

#include <stdio.h>

#include "Experiment.h"

class BallWallCollision : public Experiment
{
private:
    btRigidBody* ground;
    btRigidBody* ball;
    btRigidBody* wall;
    
protected:
    void initializeBodies();
    
    void initObjects();
    
    void worldStep();
};

#endif /* defined(__pf2__BallWallCollision__) */
