//
//  ObjectStoppedCondition.h
//  pf2
//
//  Created by Enzo Altamiranda G on 26.04.15.
//  Copyright (c) 2015 Enzo Altamiranda G. All rights reserved.
//

#ifndef __pf2__ObjectStoppedCondition__
#define __pf2__ObjectStoppedCondition__

#include <stdio.h>
#include "StoppingCondition.h"

struct posCounter {
    int counter;
    btVector3 position;
};

class ObjectStoppedCondition : public StoppingCondition
{
public:
    ObjectStoppedCondition(btRigidBody* body);
    
    virtual bool stopConditionMet();
    
private:
    btRigidBody* body;
    
    posCounter counter;
};

#endif /* defined(__pf2__ObjectStoppedCondition__) */
