//
//  FourierBody.cpp
//  TorqueResearch
//
//  Created by Enzo Altamiranda G on 15.11.15.
//  Copyright © 2015 Enzo Altamiranda G. All rights reserved.
//

#include "FourierBody.h"
#include "BodyGroup.h"
#include "ArmBodyGroup.h"
#include "LegBodyGroup.h"
#include "TorsoBodyGroup.h"
#include "ConstraintBuilder.h"
#include "FourierActuator.h"


FourierBody::FourierBody(btDynamicsWorld* world, BodyParameters& params) : WalkerBody(world, params) {
    numberOfParams = 14;
}

void FourierBody::setActuatorValues(int index, std::vector<double> vals) {
    if(index != 0){
        return;
    }
    
    FourierActuator* actuator;
    double values[30] = {
        vals[0], vals[1], vals[2], vals[3], vals[4], vals[5], vals[6],
        vals[7], vals[8], vals[9], vals[10], vals[11], vals[12], vals[13]
    };
    
    BodyPart* leftLowerLeg = getLowerLeftLeg();
    actuator = dynamic_cast<FourierActuator*>(leftLowerLeg->getActuator(0));
    actuator->setActuatorValues(values);
    
    BodyPart* leftUpperLeg = getUpperLeftLeg();
    actuator = dynamic_cast<FourierActuator*>(leftUpperLeg->getActuator(0));
    actuator->setActuatorValues(&values[6]);
    
    values[6] += SIMD_PI;
    values[13] += SIMD_PI;
    
    BodyPart* rightLowerLeg = getLowerRightLeg();
    actuator = dynamic_cast<FourierActuator*>(rightLowerLeg->getActuator(0));
    actuator->setActuatorValues(values);
    
    BodyPart* rightUpperLeg = getUpperRightLeg();
    actuator = dynamic_cast<FourierActuator*>(rightUpperLeg->getActuator(0));
    actuator->setActuatorValues(&values[6]);
    
}