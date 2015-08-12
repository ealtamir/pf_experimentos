//
//  GenericBodyParameters.cpp
//  test
//
//  Created by Enzo Altamiranda G on 03.08.15.
//  Copyright (c) 2015 Enzo Altamiranda G. All rights reserved.
//

#include "GenericBodyParameters.h"
#include "GenericActuator.h"


GenericBodyParameters::GenericBodyParameters() {
    
    rightLowerArmAct = new GenericActuator();
    rightUpperArmAct = new GenericActuator();
    
    leftLowerArmAct = new GenericActuator();
    leftUpperArmAct = new GenericActuator();
    
    hipAct = new GenericActuator();
    
    rightLowerLegAct = new GenericActuator();
    rightUpperLegAct = new GenericActuator();
    
    leftLowerLegAct = new GenericActuator();
    leftUpperLegAct = new GenericActuator();
}