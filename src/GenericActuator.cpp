//
//  GenericActuator.cpp
//  test
//
//  Created by Enzo Altamiranda G on 04.08.15.
//  Copyright (c) 2015 Enzo Altamiranda G. All rights reserved.
//

#include "GenericActuator.h"
#include <vector>

#define SIN_AMPLITUD 0
#define COS_AMPLITUD 1
#define SIN_FREC 2
#define COS_FREC 3
#define FASE 4
#define IND_TERM 5

btVector3 GenericActuator::actuatorFunc(double t, int stage) {
    
    double f = parameters[SIN_AMPLITUD] * sin(parameters[SIN_FREC] * t + parameters[FASE])
        + parameters[COS_AMPLITUD] * cos(parameters[COS_FREC] * t
        + parameters[FASE]) + parameters[IND_TERM];
    return btVector3(f, 0, 0);
}

void GenericActuator::setActuatorValues(double vals[]) {
    parameters[SIN_AMPLITUD] = vals[SIN_AMPLITUD];
    parameters[COS_AMPLITUD] = vals[COS_AMPLITUD];
    parameters[SIN_FREC] = vals[SIN_FREC];
    parameters[COS_FREC] = vals[COS_FREC];
    parameters[FASE] = vals[FASE];
    parameters[IND_TERM] = vals[IND_TERM];
}

void GenericActuator::setActuatorValues(double vals1[], double vals2[]) {
    parameters[SIN_AMPLITUD] = vals1[SIN_AMPLITUD];
    parameters[COS_AMPLITUD] = vals1[COS_AMPLITUD];
    parameters[SIN_FREC] = vals1[SIN_FREC];
    parameters[COS_FREC] = vals1[COS_FREC];
    parameters[FASE] = vals1[FASE];
    parameters[IND_TERM] = vals1[IND_TERM];
}

Actuator* GenericActuator::clone() {
    return new GenericActuator();
}