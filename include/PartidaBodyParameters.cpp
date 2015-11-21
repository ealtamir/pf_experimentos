
//
//  PartidaBodyParameters.cpp
//  MongoDoll
//
//  Created by Teresa Fontanella De Santis on 11/21/15.
//  Copyright (c) 2015 PF15. All rights reserved.
//

#include "PartidaBodyParameters.h"
#include "PartidaActuator.h"

PartidaBodyParameters::PartidaBodyParameters() {
    rightLowerArmAct = new PartidaActuator();
    rightUpperArmAct = new PartidaActuator();
    
    leftLowerArmAct = new PartidaActuator();
    leftUpperArmAct = new PartidaActuator();
    
    hipAct = new PartidaActuator();
    
    rightLowerLegAct = new PartidaActuator();
    rightUpperLegAct = new PartidaActuator();
    
    leftLowerLegAct = new PartidaActuator(true);
    leftUpperLegAct = new PartidaActuator(true);
}

PartidaBodyParameters::~PartidaBodyParameters() {
}