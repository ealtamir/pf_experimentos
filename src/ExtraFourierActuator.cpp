//
//  ExtraFourierActuator.cpp
//  TorqueResearch
//
//  Created by Enzo Altamiranda G on 20.11.15.
//  Copyright © 2015 Enzo Altamiranda G. All rights reserved.
//

#include "ExtraFourierActuator.h"

#define A0 0
#define A1 1
#define A2 2
#define A3 3
#define A4 4
#define A5 5
#define A6 6
#define A7 7
#define A8 8
#define A9 9
#define B1 10
#define B2 11
#define B3 12
#define B4 13
#define B5 14
#define B6 15
#define B7 16
#define B8 17
#define B9 18
#define FREQ 19
#define FASE 20


ExtraFourierActuator::ExtraFourierActuator() {
    
}

void ExtraFourierActuator::setActuatorValues(double vals[]) {
    parameters[A0] = vals[A0];
    parameters[A1] = vals[A1];
    parameters[A2] = vals[A2];
    parameters[A3] = vals[A3];
    parameters[A4] = vals[A4];
    parameters[A5] = vals[A5];
    parameters[A6] = vals[A6];
    parameters[A7] = vals[A7];
    parameters[A8] = vals[A8];
    parameters[A9] = vals[A9];
    parameters[B1] = vals[B1];
    parameters[B2] = vals[B2];
    parameters[B3] = vals[B3];
    parameters[B4] = vals[B4];
    parameters[B5] = vals[B5];
    parameters[B6] = vals[B6];
    parameters[B7] = vals[B7];
    parameters[B8] = vals[B8];
    parameters[B9] = vals[B9];
    parameters[FREQ] = vals[FREQ];
    parameters[FASE] = vals[FASE];
}


btVector3 ExtraFourierActuator::actuatorFunc(double t, int stage) {
    double* p = parameters;
    double freq = p[FREQ];
    double fase = p[FASE];
    double termInd = p[A0];
    double result =  termInd
    + p[A1] * cos(freq * t + fase) + p[B1] * sin(freq * t + fase)
    + p[A2] * cos(2 * freq * t + fase) + p[B2] * sin(2 * freq * t + fase)
    + p[A3] * cos(3 * freq * t + fase) + p[B3] * sin(3 * freq * t + fase)
    + p[A4] * cos(4 * freq * t + fase) + p[B4] * sin(4 * freq * t + fase)
    + p[A5] * cos(5 * freq * t + fase) + p[B5] * sin(5 * freq * t + fase)
    + p[A6] * cos(6 * freq * t + fase) + p[B6] * sin(6 * freq * t + fase)
    + p[A7] * cos(7 * freq * t + fase) + p[B7] * sin(7 * freq * t + fase)
    + p[A8] * cos(8 * freq * t + fase) + p[B8] * sin(8 * freq * t + fase)
    + p[A9] * cos(9 * freq * t + fase) + p[B9] * sin(9 * freq * t + fase);
    return btVector3(result, 0, 0);
}

void ExtraFourierActuator::setActuatorValues(double vals1[], double vals2[]) {
    
}

Actuator* ExtraFourierActuator::clone() {
    return nullptr;
}