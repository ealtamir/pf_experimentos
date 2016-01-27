//
//  GenericActuatorHip.cpp
//  TorqueResearch
//
//  Created by Enzo Altamiranda G on 22.01.16.
//  Copyright © 2016 Enzo Altamiranda G. All rights reserved.
//

#include "GenericActuatorHip.hpp"

#define SIN_AMPLITUD 0
#define COS_AMPLITUD 1
#define SIN_FREC 2
#define COS_FREC 3
#define FASE 4
#define IND_TERM 5

btVector3 GenericActuatorHip::actuatorFunc(double t, int stage) {
    double f = parameters[SIN_AMPLITUD] * sin(parameters[SIN_FREC] * t + parameters[FASE])
    + parameters[COS_AMPLITUD] * cos(parameters[COS_FREC] * t
                                     + parameters[FASE]) + parameters[IND_TERM];
    return btVector3(0, f, 0);
}
