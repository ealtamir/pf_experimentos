//
//  Ragdoll_experiment.h
//  pf2
//
//  Created by tom on 5/14/15.
//  Copyright (c) 2015 Enzo Altamiranda G. All rights reserved.
//

#ifndef __pf2__Ragdoll_experiment__
#define __pf2__Ragdoll_experiment__

#include <stdio.h>
#include "Experiment.h"
#include "Ragdoll.h"

class Ragdoll_experiment : public Experiment
{
private:
    btRigidBody* ground;
    RagDoll* ragDoll;
    
protected:
    void initializeBodies();
    
    void initObjects();
    
    void worldStep();
    
    bool stopExperiment();
    
};



#endif /* defined(__pf2__Ragdoll_experiment__) */
