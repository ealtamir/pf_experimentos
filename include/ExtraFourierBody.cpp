//
//  ExtraFourierBody.cpp
//  TorqueResearch
//
//  Created by Enzo Altamiranda G on 20.11.15.
//  Copyright © 2015 Enzo Altamiranda G. All rights reserved.
//

#include "ExtraFourierBody.h"
#include "ExtraFourierActuator.h"

ExtraFourierBody::ExtraFourierBody(btDynamicsWorld* world, BodyParameters& params) : WalkerBody(world, params) {
    numberOfParams = 42;
}

void ExtraFourierBody::setActuatorValues(std::vector<double> vals) {
    
    ExtraFourierActuator* actuator;
    double values[42] = {
        vals[0], vals[1], vals[2], vals[3], vals[4], vals[5], vals[6],
        vals[7], vals[8], vals[9], vals[10], vals[11], vals[12], vals[13],
        vals[14], vals[15], vals[16], vals[17], vals[18], vals[19],
        vals[20], vals[21], vals[22], vals[23], vals[24], vals[25], vals[26],
        vals[27], vals[28], vals[29], vals[30], vals[31], vals[32], vals[33],
        vals[34], vals[35], vals[36], vals[37], vals[38], vals[39], vals[40],
        vals[41]
    };
    
    BodyPart* leftLowerLeg = getLowerLeftLeg();
    actuator = dynamic_cast<ExtraFourierActuator*>(leftLowerLeg->getActuator());
    actuator->setActuatorValues(values);
    
    BodyPart* leftUpperLeg = getUpperLeftLeg();
    actuator = dynamic_cast<ExtraFourierActuator*>(leftUpperLeg->getActuator());
    actuator->setActuatorValues(&values[21]);
    
    values[19] += SIMD_PI;
    values[40] += SIMD_PI;
    
    BodyPart* rightLowerLeg = getLowerRightLeg();
    actuator = dynamic_cast<ExtraFourierActuator*>(rightLowerLeg->getActuator());
    actuator->setActuatorValues(values);
    
    BodyPart* rightUpperLeg = getUpperRightLeg();
    actuator = dynamic_cast<ExtraFourierActuator*>(rightUpperLeg->getActuator());
    actuator->setActuatorValues(&values[21]);
    
}