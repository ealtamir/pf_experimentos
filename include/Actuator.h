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
    
    double fase = 0;
    
    double A = 12;
    double B = 12;
    double w1 = 3;
    double w2 = 3;
};

#endif /* defined(__test__Actuator__) */
