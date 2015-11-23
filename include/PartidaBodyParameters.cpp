
//
//  PartidaBodyParameters.cpp
//  MongoDoll
//
//  Created by Teresa Fontanella De Santis on 11/21/15.
//  Copyright (c) 2015 PF15. All rights reserved.
//

#include "PartidaBodyParameters.h"
#include "PartidaActuator.h"
#include "CosineDoubleFrecActuator.h"

PartidaBodyParameters::PartidaBodyParameters() {
    
    rightLowerArmAct.push_back( new CosineDoubleFrecActuator());
    rightLowerArmAct.push_back( new PartidaActuator());
    rightUpperArmAct.push_back( new CosineDoubleFrecActuator());
    rightUpperArmAct.push_back( new PartidaActuator());
    
    leftLowerArmAct.push_back( new CosineDoubleFrecActuator());
    leftLowerArmAct.push_back( new PartidaActuator());
    leftUpperArmAct.push_back( new CosineDoubleFrecActuator());
    leftUpperArmAct.push_back( new PartidaActuator());
    
    hipAct.push_back( new CosineDoubleFrecActuator());
    hipAct.push_back( new PartidaActuator());
    
    rightLowerLegAct.push_back( new CosineDoubleFrecActuator());
    rightLowerLegAct.push_back( new PartidaActuator());
    rightUpperLegAct.push_back( new CosineDoubleFrecActuator());
    rightUpperLegAct.push_back( new PartidaActuator());

    leftLowerLegAct.push_back( new CosineDoubleFrecActuator(true));
    leftLowerLegAct.push_back( new PartidaActuator(true));
    leftUpperLegAct.push_back( new CosineDoubleFrecActuator(true));
    leftUpperLegAct.push_back( new PartidaActuator(true));
}

PartidaBodyParameters::~PartidaBodyParameters() {
}