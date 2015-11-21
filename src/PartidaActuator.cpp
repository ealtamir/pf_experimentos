//
//  PartidaActuator.cpp
//  MongoDoll
//
//  Created by Teresa Fontanella De Santis on 11/21/15.
//  Copyright (c) 2015 PF15. All rights reserved.
//

#include "PartidaActuator.h"


#define A 0
#define W 1
#define FASE 2
#define IND_TERM 3


PartidaActuator::PartidaActuator(bool isLeft) : Actuator(isLeft) {
    
}

btVector3 PartidaActuator::actuatorFunc(double t, int stage) {
    double senos = parameters[A] * sin(parameters[W]/2 * t + parameters[FASE]);
    
    return btVector3(senos + parameters[IND_TERM], 0, 0);
}

void PartidaActuator::setActuatorValues(double vals[]) {
    parameters[A] = vals[A];
    parameters[W] = vals[W];
    parameters[FASE] = vals[FASE];
    parameters[IND_TERM] = vals[IND_TERM];
}