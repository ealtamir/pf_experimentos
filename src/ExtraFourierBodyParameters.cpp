//
//  ExtraFourierBodParameters.cpp
//  TorqueResearch
//
//  Created by Enzo Altamiranda G on 20.11.15.
//  Copyright © 2015 Enzo Altamiranda G. All rights reserved.
//

#include "ExtraFourierBodyParameters.h"
#include "ExtraFourierActuator.h"

ExtraFourierBodyParameters::ExtraFourierBodyParameters() {
    rightLowerArmAct = new ExtraFourierActuator();
    rightUpperArmAct = new ExtraFourierActuator();
    
    leftLowerArmAct = new ExtraFourierActuator();
    leftUpperArmAct = new ExtraFourierActuator();
    
    hipAct = new ExtraFourierActuator();
    
    rightLowerLegAct = new ExtraFourierActuator();
    rightUpperLegAct = new ExtraFourierActuator();
    
    leftLowerLegAct = new ExtraFourierActuator();
    leftUpperLegAct = new ExtraFourierActuator();
}

ExtraFourierBodyParameters::~ExtraFourierBodyParameters() {
    
}