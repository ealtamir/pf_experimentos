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
#include "PartidaActuator.h"

PartidaBody::PartidaBody(btDynamicsWorld* world, BodyParameters& params) : WalkerBody(world, params) {
    numberOfParams = 8;
}

void
PartidaBody::actuate(double t, int stage) {
    
    for (BodyGroup* group : bodyGroups) {
        group->actuate(t, 1);
    }
}

void PartidaBody::setActuatorValues(int index, std::vector<double> vals) {
    
    Actuator* actuator;
    double values[30] = {};
    int cant_params = (index==0)?OTHER_FUNCTION_VALUES_SIZE:numberOfParams;
    for (int i=0; i<cant_params; i++) {
        values[i]=vals[i];
    }
    /*double values[30] = {
        vals[0], vals[1], vals[2], vals[3], vals[4], vals[5], vals[6],
        vals[7], vals[8]    };
    */
    BodyPart* leftLowerLeg = getLowerLeftLeg();
    actuator = leftLowerLeg->getActuator(index);
    actuator->setActuatorValues(values);
    
    BodyPart* leftUpperLeg = getUpperLeftLeg();
    actuator = leftUpperLeg->getActuator(index);
    actuator->setActuatorValues(&values[cant_params/2]);
    
    /*values[3] += SIMD_PI;
    values[7] += SIMD_PI;
    */
    
    BodyPart* rightLowerLeg = getLowerRightLeg();
    actuator = rightLowerLeg->getActuator(index);
    actuator->setActuatorValues(values);
    
    BodyPart* rightUpperLeg = getUpperRightLeg();
    actuator = rightUpperLeg->getActuator(index);
    actuator->setActuatorValues(&values[cant_params/2]);
    
}