//
//  GenericActuator.cpp
//  test
//
//  Created by Enzo Altamiranda G on 04.08.15.
//  Copyright (c) 2015 Enzo Altamiranda G. All rights reserved.
//

#include "GenericActuator.h"


GenericActuator::GenericActuator(bool isLeft) {
    if (isLeft) {
        fase = SIMD_PI;
    }
}

btVector3
GenericActuator::actuatorFunc(double t) {
    
    double f = A * sin(w1 * t + fase) + B * cos(w2 * t + fase);
    return btVector3(f, 0, 0);
}