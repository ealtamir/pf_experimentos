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

#define PARAMS_SIZE 30 

class Actuator {
    
public:
    
    btVector3 eval(double t, int stage);
    
    void setParameters(double *parameters);
    
    virtual void setActuatorValues(double vals[]) = 0;
    
    virtual void setActuatorValues(double vals1[], double vals2[]) = 0;
    
    virtual Actuator* clone() = 0;
    
    virtual btVector3 actuatorFunc(double t, int stage) = 0;
    
protected:
    double parameters[PARAMS_SIZE];
};

#endif /* defined(__test__Actuator__) */
