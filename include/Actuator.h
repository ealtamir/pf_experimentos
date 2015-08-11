//
//  Actuator.h
//  test
//
//  Created by Enzo Altamiranda G on 02.08.15.
//  Copyright (c) 2015 Enzo Altamiranda G. All rights reserved.
//

#ifndef __test__Actuator__
#define __test__Actuator__

#include <stdio.h>
#include <BulletDynamics/btBulletDynamicsCommon.h>

class Actuator {
    
    
public:
    btVector3 eval(double t);
    
protected:
    virtual
    btVector3 actuatorFunc(double t) = 0;
    
    double A = 5 * ((double) rand() / RAND_MAX);
    double B = 5 * ((double) rand() / RAND_MAX);
    double w1 = 5 * ((double) rand() / RAND_MAX);
    double w2 = 5 * ((double) rand() / RAND_MAX);
};

#endif /* defined(__test__Actuator__) */
