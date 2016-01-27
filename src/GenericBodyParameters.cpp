//
//  GenericBodyParameters.cpp
//  test
//
//  Created by Enzo Altamiranda G on 03.08.15.
//  Copyright (c) 2015 Enzo Altamiranda G. All rights reserved.
//

#include "GenericBodyParameters.h"
#include "GenericActuator.h"
#include "GenericActuatorHip.hpp"
#include "FourierActuator.h"
#include "CosineDoubleFrecActuator.h"
#include "MetaActuator.h"

GenericBodyParameters::GenericBodyParameters(Actuator *firstStepActuator) {
    
    rightLowerArmAct = new MetaActuator(firstStepActuator->clone(), new GenericActuator());
    rightUpperArmAct = new MetaActuator(firstStepActuator->clone(), new GenericActuator());
    
    leftLowerArmAct = new MetaActuator(firstStepActuator->clone(), new GenericActuator());
    leftUpperArmAct = new MetaActuator(firstStepActuator->clone(), new GenericActuator());
    
    hipAct = new MetaActuator(firstStepActuator->clone(), new GenericActuatorHip());
    
    rightLowerLegAct = new MetaActuator(firstStepActuator->clone(), new GenericActuator());
    rightUpperLegAct = new MetaActuator(firstStepActuator->clone(), new GenericActuator());
    
    leftLowerLegAct = new MetaActuator(firstStepActuator->clone(), new GenericActuator());
    leftUpperLegAct = new MetaActuator(firstStepActuator->clone(), new GenericActuator());
}

GenericBodyParameters::~GenericBodyParameters() {
}