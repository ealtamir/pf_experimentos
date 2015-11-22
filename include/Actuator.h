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
#include <vector>
#include <BulletDynamics/btBulletDynamicsCommon.h>

#define PARAMS_SIZE 30

class Actuator {
    
public:
    
    
    Actuator(bool isLeft);
    
    btVector3 eval(double t, int stage);
    
    
    void setParameters(double *parameters);
    
    virtual bool isFirstStep(double t) = 0;
    
    virtual void setActuatorValues(double vals[]) = 0;
    
protected:
    double parameters[PARAMS_SIZE];
    
    virtual btVector3 actuatorFunc(double t, int stage) = 0;

};

#endif /* defined(__test__Actuator__) */
