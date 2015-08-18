//
//  FourierActuator.cpp
//  proyecto_pf
//
//  Created by Enzo Altamiranda G on 17.08.15.
//  Copyright (c) 2015 Enzo Altamiranda G. All rights reserved.
//

#include "FourierActuator.h"


FourierActuator::FourierActuator(bool isLeft) : Actuator(isLeft) {
    
}

btVector3
FourierActuator::actuatorFunc(double t) {
    double senos = A1 * sin(w * t + fase) + A2 * sin(2 * w * t + fase);
    double cosenos = A3 * cos(w * t + fase) + A4 * cos(2 * w * t + fase);
    return btVector3(senos + cosenos + C, 0, 0);
}