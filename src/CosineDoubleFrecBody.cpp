//
//  CosineDoubleFrecBody.cpp
//  TorqueResearch
//
//  Created by Enzo Altamiranda G on 15.11.15.
//  Copyright © 2015 Enzo Altamiranda G. All rights reserved.
//

#include "CosineDoubleFrecBody.h"
#include "CosineDoubleFrecActuator.h"

CosineDoubleFrecBody::CosineDoubleFrecBody(btDynamicsWorld* world,
                                           BodyParameters& params) : WalkerBody(world, params) {
    numberOfParams = 10;
}

void
CosineDoubleFrecBody::setActuatorValues(std::vector<double> vals) {
    
    Actuator* actuator;
    double values[30] = {
        vals[0], vals[1], vals[2], vals[3], vals[4],
        vals[5], vals[6], vals[7], vals[8], vals[9],
        vals[10], vals[11], vals[12], vals[13], vals[14],
        vals[15], vals[16], vals[17], vals[18], vals[19]
    };
    
    BodyPart* leftLowerLeg = getLowerLeftLeg();
    actuator = dynamic_cast<Actuator*>(leftLowerLeg->getActuator());
    actuator->setActuatorValues(values, &values[10]);
    
    BodyPart* leftUpperLeg = getUpperLeftLeg();
    actuator = dynamic_cast<Actuator*>(leftUpperLeg->getActuator());
    actuator->setActuatorValues(&values[5], &values[15]);
    
    values[3] += SIMD_PI;
    values[8] += SIMD_PI;
    values[13] += SIMD_PI;
    values[18] += SIMD_PI;
    
    BodyPart* rightLowerLeg = getLowerRightLeg();
    actuator = dynamic_cast<Actuator*>(rightLowerLeg->getActuator());
    actuator->setActuatorValues(values, &values[10]);
    
    BodyPart* rightUpperLeg = getUpperRightLeg();
    actuator = dynamic_cast<Actuator*>(rightUpperLeg->getActuator());
    actuator->setActuatorValues(&values[5], &values[15]);
}