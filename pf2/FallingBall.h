//
//  FallingBall.h
//  pf2
//
//  Created by Enzo Altamiranda G on 22.04.15.
//  Copyright (c) 2015 Enzo Altamiranda G. All rights reserved.
//

#ifndef __pf2__FallingBall__
#define __pf2__FallingBall__

#include <stdio.h>
#include "Experiment.h"

class FallingBall : public Experiment
{
private:
    btRigidBody* ground;
    btRigidBody* ball;

protected:
    void initializeBodies();
    
    void initObjects();
    
    void worldStep();
    
    bool stopExperiment();

};


#endif /* defined(__pf2__FallingBall__) */
