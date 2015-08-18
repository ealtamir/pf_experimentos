//
//  Actuator.cpp
//  test
//
//  Created by Enzo Altamiranda G on 02.08.15.
//  Copyright (c) 2015 Enzo Altamiranda G. All rights reserved.
//

#include "Actuator.h"


Actuator::Actuator(bool isLeft) {
    if (isLeft) {
        fase = SIMD_PI;
    }
}

btVector3
Actuator::eval(double t) {
    return actuatorFunc(t);
}