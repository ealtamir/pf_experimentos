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
    
    leftLowerLegAct = new GenericActuator();
    leftUpperArmAct = new GenericActuator();
    
    hipAct = new GenericActuator();
    
    rightLowerArmAct = new GenericActuator();
    rightUpperArmAct = new GenericActuator();
    
    leftLowerLegAct = new GenericActuator();
    leftUpperArmAct = new GenericActuator();
}