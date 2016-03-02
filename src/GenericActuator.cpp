//
//  GenericActuator.cpp
//  test
//
//  Created by Enzo Altamiranda G on 04.08.15.
//  Copyright (c) 2015 Enzo Altamiranda G. All rights reserved.
//

#include "GenericActuator.h"
#include <vector>

#define SIN_AMPLITUD_X 0
#define COS_AMPLITUD_X 1
#define SIN_FREC_X 2
#define COS_FREC_X 3
#define FASE_X 4
#define IND_TERM_X 5

#define SIN_AMPLITUD_Y 6
#define COS_AMPLITUD_Y 7
#define SIN_FREC_Y 8
#define COS_FREC_Y 9
#define FASE_Y 10
#define IND_TERM_Y 11

#define SIN_AMPLITUD_Z 12
#define COS_AMPLITUD_Z 13
#define SIN_FREC_Z 14
#define COS_FREC_Z 15
#define FASE_Z 16
#define IND_TERM_Z 17

btVector3 GenericActuator::actuatorFunc(double t, int stage) {
    double fx = parameters[SIN_AMPLITUD_X] * sin(parameters[SIN_FREC_X] * t + parameters[FASE_X])
        + parameters[COS_AMPLITUD_X] * cos(parameters[COS_FREC_X] * t
        + parameters[FASE_X]) + parameters[IND_TERM_X];
    
    double fy = parameters[SIN_AMPLITUD_Y] * sin(parameters[SIN_FREC_Y] * t + parameters[FASE_Y])
        + parameters[COS_AMPLITUD_Y] * cos(parameters[COS_FREC_Y] * t
        + parameters[FASE_Y]) + parameters[IND_TERM_Y];
    
    double fz = parameters[SIN_AMPLITUD_Z] * sin(parameters[SIN_FREC_Z] * t + parameters[FASE_Z])
        + parameters[COS_AMPLITUD_Z] * cos(parameters[COS_FREC_Z] * t
        + parameters[FASE_Z]) + parameters[IND_TERM_Z];
    return btVector3(fx, fy, 0);
}

void GenericActuator::setActuatorValues(double vals[]) {
    parameters[SIN_AMPLITUD_X] = vals[SIN_AMPLITUD_X];
    parameters[COS_AMPLITUD_X] = vals[COS_AMPLITUD_X];
    parameters[SIN_FREC_X] = vals[SIN_FREC_X];
    parameters[COS_FREC_X] = vals[COS_FREC_X];
    parameters[FASE_X] = vals[FASE_X];
    parameters[IND_TERM_X] = vals[IND_TERM_X];
    
    parameters[SIN_AMPLITUD_Y] = vals[SIN_AMPLITUD_Y];
    parameters[COS_AMPLITUD_Y] = vals[COS_AMPLITUD_Y];
    parameters[SIN_FREC_Y] = vals[SIN_FREC_Y];
    parameters[COS_FREC_Y] = vals[COS_FREC_Y];
    parameters[FASE_Y] = vals[FASE_Y];
    parameters[IND_TERM_Y] = vals[IND_TERM_Y];
    
    parameters[SIN_AMPLITUD_Z] = vals[SIN_AMPLITUD_Z];
    parameters[COS_AMPLITUD_Z] = vals[COS_AMPLITUD_Z];
    parameters[SIN_FREC_Z] = vals[SIN_FREC_Z];
    parameters[COS_FREC_Z] = vals[COS_FREC_Z];
    parameters[FASE_Z] = vals[FASE_Z];
    parameters[IND_TERM_Z] = vals[IND_TERM_Z];
}

void GenericActuator::setActuatorValues(double vals1[], double vals2[]) {
    parameters[SIN_AMPLITUD_X] = vals1[SIN_AMPLITUD_X];
    parameters[COS_AMPLITUD_X] = vals1[COS_AMPLITUD_X];
    parameters[SIN_FREC_X] = vals1[SIN_FREC_X];
    parameters[COS_FREC_X] = vals1[COS_FREC_X];
    parameters[FASE_X] = vals1[FASE_X];
    parameters[IND_TERM_X] = vals1[IND_TERM_X];
    
    parameters[SIN_AMPLITUD_Y] = vals1[SIN_AMPLITUD_Y];
    parameters[COS_AMPLITUD_Y] = vals1[COS_AMPLITUD_Y];
    parameters[SIN_FREC_Y] = vals1[SIN_FREC_Y];
    parameters[COS_FREC_Y] = vals1[COS_FREC_Y];
    parameters[FASE_Y] = vals1[FASE_Y];
    parameters[IND_TERM_Y] = vals1[IND_TERM_Y];
    
    parameters[SIN_AMPLITUD_Z] = vals1[SIN_AMPLITUD_Z];
    parameters[COS_AMPLITUD_Z] = vals1[COS_AMPLITUD_Z];
    parameters[SIN_FREC_Z] = vals1[SIN_FREC_Z];
    parameters[COS_FREC_Z] = vals1[COS_FREC_Z];
    parameters[FASE_Z] = vals1[FASE_Z];
    parameters[IND_TERM_Z] = vals1[IND_TERM_Z];
}

Actuator* GenericActuator::clone() {
    return new GenericActuator();
}