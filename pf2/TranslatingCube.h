//
//  TranslatingCube.h
//  pf2
//
//  Created by Enzo Altamiranda G on 23.04.15.
//  Copyright (c) 2015 Enzo Altamiranda G. All rights reserved.
//

#ifndef __pf2__TranslatingCube__
#define __pf2__TranslatingCube__

#include <stdio.h>
#include "Experiment.h"
#include "ObjectStoppedCondition.h"

class TranslatingCube : public Experiment
{
public:
    TranslatingCube();
    
private:
    btRigidBody* ground;
    btRigidBody* box;
    btRigidBody* wall;
    
    
protected:
    void initializeBodies();
    
    void initObjects();
    
    void worldStep();
    
    virtual bool stopExperiment();
};

#endif /* defined(__pf2__TranslatingCube__) */
