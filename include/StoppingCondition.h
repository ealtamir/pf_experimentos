//
//  StopingCondition.h
//  pf2
//
//  Created by Enzo Altamiranda G on 25.04.15.
//  Copyright (c) 2015 Enzo Altamiranda G. All rights reserved.
//

#ifndef __pf2__StopingCondition__
#define __pf2__StopingCondition__

#include <stdio.h>
#include <BulletDynamics/btBulletDynamicsCommon.h>

class StoppingCondition
{    
public:    
    virtual bool stopConditionMet() = 0;
};

#endif /* defined(__pf2__StopingCondition__) */
