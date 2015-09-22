//
//  Actuator.cpp
//  test
//
//  Created by Enzo Altamiranda G on 02.08.15.
//  Copyright (c) 2015 Enzo Altamiranda G. All rights reserved.
//

#include "Actuator.h"


Actuator::Actuator(bool isLeft) {
}

btVector3 Actuator::eval(double t) {
    return actuatorFunc(t);
}

void Actuator::setParameters(double *params) {
    for (int i = 0; i < PARAMS_SIZE; i++) {
        parameters[i] = params[i];
    }
}