//
//  GenericActuator.h
//  test
//
//  Created by Enzo Altamiranda G on 04.08.15.
//  Copyright (c) 2015 Enzo Altamiranda G. All rights reserved.
//

#ifndef __test__GenericActuator__
#define __test__GenericActuator__

#include <stdio.h>
#include "Actuator.h"

class GenericActuator : public Actuator {
    
public:
    GenericActuator(bool isLeft = false);
    
protected:
    btVector3 actuatorFunc(double t);
    
    double A = 12;
    double B = 12;
    double w1 = 3;
    double w2 = 3;
    
};

#endif /* defined(__test__GenericActuator__) */
