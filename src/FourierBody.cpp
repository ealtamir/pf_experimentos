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

void FourierBody::setActuatorValues(std::vector<double> vals) {
    Actuator* actuator;
    double values[50] = {
        vals[0], vals[1], vals[2], vals[3], vals[4], vals[5],
        vals[6], vals[7], vals[8], vals[9], vals[10], vals[11],
        vals[12], vals[13], vals[14], vals[15], vals[16], vals[17],
        vals[18], vals[19], vals[20], vals[21], vals[22], vals[23],
        
        
        vals[24], vals[25], vals[26], vals[27], vals[28], vals[29],vals[30],
        vals[31], vals[32], vals[33], vals[34], vals[35], vals[36], vals[37]
    };
    
    //
    // Se le pasan al meta actuator
    //
    BodyPart* leftLowerLeg = getLowerLeftLeg();
    actuator = dynamic_cast<Actuator*>(leftLowerLeg->getActuator());
    actuator->setActuatorValues(values, &values[24]);
    
    BodyPart* leftUpperLeg = getUpperLeftLeg();
    actuator = dynamic_cast<Actuator*>(leftUpperLeg->getActuator());
    actuator->setActuatorValues(&values[6], &values[31]);
    
    values[30] += SIMD_PI;
    values[37] += SIMD_PI;
    
    BodyPart* rightLowerLeg = getLowerRightLeg();
    actuator = dynamic_cast<Actuator*>(rightLowerLeg->getActuator());
    actuator->setActuatorValues(&values[12], &values[24]);
    
    BodyPart* rightUpperLeg = getUpperRightLeg();
    actuator = dynamic_cast<Actuator*>(rightUpperLeg->getActuator());
    actuator->setActuatorValues(&values[18], &values[31]);
    
    
    
    /*
    
    Actuator* actuator;
    double values[30] = {
        vals[0], vals[1], vals[2], vals[3], vals[4], vals[5], vals[6],
        vals[7], vals[8], vals[9], vals[10], vals[11], vals[12], vals[13]
    };
    
    BodyPart* leftLowerLeg = getLowerLeftLeg();
    actuator = dynamic_cast<Actuator*>(leftLowerLeg->getActuator());
    actuator->setActuatorValues(values);
    
    BodyPart* leftUpperLeg = getUpperLeftLeg();
    actuator = dynamic_cast<Actuator*>(leftUpperLeg->getActuator());
    actuator->setActuatorValues(&values[6]);
    
    values[6] += SIMD_PI;
    values[13] += SIMD_PI;
    
    BodyPart* rightLowerLeg = getLowerRightLeg();
    actuator = dynamic_cast<Actuator*>(rightLowerLeg->getActuator());
    actuator->setActuatorValues(values);
    
    BodyPart* rightUpperLeg = getUpperRightLeg();
    actuator = dynamic_cast<Actuator*>(rightUpperLeg->getActuator());
    actuator->setActuatorValues(&values[6]);
    */
}