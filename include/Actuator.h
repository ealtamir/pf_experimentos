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
    Actuator(bool isLeft);
    btVector3 eval(double t);
    
    virtual void setA(double valueA) = 0;
    virtual void setB(double valueB) = 0;
    virtual void setw1(double valuew1) = 0;
    virtual void setw2(double valuew2) = 0;
    virtual void setFase(double valuew2) = 0;
    
protected:
    virtual btVector3
    actuatorFunc(double t) = 0;   

};

#endif /* defined(__test__Actuator__) */
