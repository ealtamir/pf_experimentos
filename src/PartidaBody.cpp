//
//  PartidaBody.cpp
//  MongoDoll
//
//  Created by Teresa Fontanella De Santis on 11/21/15.
//  Copyright (c) 2015 PF15. All rights reserved.
//

#include "PartidaBody.h"

#include "FourierBody.h"
#include "BodyGroup.h"
#include "ArmBodyGroup.h"
#include "LegBodyGroup.h"
#include "TorsoBodyGroup.h"
#include "ConstraintBuilder.h"
#include "PartidaActuator.h"


PartidaBody::PartidaBody(btDynamicsWorld* world, BodyParameters& params) : WalkerBody(world, params) {
    numberOfParams = 8;
}

void PartidaBody::setActuatorValues(std::vector<double> vals) {
    
    PartidaActuator* actuator;
    double values[30] = {
        vals[0], vals[1], vals[2], vals[3], vals[4], vals[5], vals[6],
        vals[7], vals[8]    };
    
    BodyPart* leftLowerLeg = getLowerLeftLeg();
    actuator = dynamic_cast<PartidaActuator*>(leftLowerLeg->getActuator(0));
    actuator->setActuatorValues(values);
    
    BodyPart* leftUpperLeg = getUpperLeftLeg();
    actuator = dynamic_cast<PartidaActuator*>(leftUpperLeg->getActuator(0));
    actuator->setActuatorValues(&values[4]);
    
    /*values[3] += SIMD_PI;
    values[7] += SIMD_PI;
    */
    
    BodyPart* rightLowerLeg = getLowerRightLeg();
    actuator = dynamic_cast<PartidaActuator*>(rightLowerLeg->getActuator(0));
    actuator->setActuatorValues(values);
    
    BodyPart* rightUpperLeg = getUpperRightLeg();
    actuator = dynamic_cast<PartidaActuator*>(rightUpperLeg->getActuator(0));
    actuator->setActuatorValues(&values[4]);
    
}