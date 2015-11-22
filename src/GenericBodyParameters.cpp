//
//  GenericBodyParameters.cpp
//  test
//
//  Created by Enzo Altamiranda G on 03.08.15.
//  Copyright (c) 2015 Enzo Altamiranda G. All rights reserved.
//

#include "GenericBodyParameters.h"
#include "GenericActuator.h"
#include "FourierActuator.h"
#include "CosineDoubleFrecActuator.h"

GenericBodyParameters::GenericBodyParameters() {
    
    rightLowerArmAct.push_back( new GenericActuator());
    rightUpperArmAct.push_back( new GenericActuator());
    
    leftLowerArmAct.push_back( new GenericActuator());
    leftUpperArmAct.push_back( new GenericActuator());
    
    hipAct.push_back( new GenericActuator());
    
    rightLowerLegAct.push_back( new GenericActuator());
    rightUpperLegAct.push_back( new GenericActuator());
    
    leftLowerLegAct.push_back( new GenericActuator(true));
    leftUpperLegAct.push_back( new GenericActuator(true));
}

GenericBodyParameters::~GenericBodyParameters() {
}