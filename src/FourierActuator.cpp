//
//  FourierActuator.cpp
//  proyecto_pf
//
//  Created by Enzo Altamiranda G on 17.08.15.
//  Copyright (c) 2015 Enzo Altamiranda G. All rights reserved.
//

#include "FourierActuator.h"

#define A1 0
#define A2 1
#define A3 2
#define A4 3
#define W 4
#define FASE 5
#define IND_TERM 6


FourierActuator::FourierActuator(bool isLeft) : Actuator(isLeft) {
    
}

btVector3 FourierActuator::actuatorFunc(double t, int stage) {
    double senos = parameters[A1] * sin(parameters[W] * t + parameters[FASE])
                 + parameters[A2] * sin(2 * parameters[W] * t + parameters[FASE]);
    double cosenos = parameters[A3] * cos(parameters[W] * t + parameters[FASE])
                   + parameters[A4] * cos(2 * parameters[W] * t + parameters[FASE]);
    return btVector3(senos + cosenos + parameters[IND_TERM], 0, 0);
}

void FourierActuator::setActuatorValues(double vals[]) {
    parameters[A1] = vals[A1];
    parameters[A2] = vals[A2];
    parameters[A3] = vals[A3];
    parameters[A4] = vals[A4];
    parameters[W] = vals[W];
    parameters[FASE] = vals[FASE];
    parameters[IND_TERM] = vals[IND_TERM];
}