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
    
//    rightLowerArmAct = new GenericActuator();
//    rightUpperArmAct = new GenericActuator();
//    
//    leftLowerArmAct = new GenericActuator();
//    leftUpperArmAct = new GenericActuator();
//    
//    hipAct = new GenericActuator();
//    
//    rightLowerLegAct = new GenericActuator();
//    rightUpperLegAct = new GenericActuator();
//    
//    leftLowerLegAct = new GenericActuator(true);
//    leftUpperLegAct = new GenericActuator(true);
//    rightLowerArmAct = new FourierActuator();
//    rightUpperArmAct = new FourierActuator();
//    
//    leftLowerArmAct = new FourierActuator();
//    leftUpperArmAct = new FourierActuator();
//    
//    hipAct = new FourierActuator();
//    
//    rightLowerLegAct = new FourierActuator();
//    rightUpperLegAct = new FourierActuator();
//    
//    leftLowerLegAct = new FourierActuator(true);
//    leftUpperLegAct = new FourierActuator(true);
    rightLowerArmAct = new CosineDoubleFrecActuator();
    rightUpperArmAct = new CosineDoubleFrecActuator();
    
    leftLowerArmAct = new CosineDoubleFrecActuator();
    leftUpperArmAct = new CosineDoubleFrecActuator();
    
    hipAct = new CosineDoubleFrecActuator();
    
    rightLowerLegAct = new CosineDoubleFrecActuator();
    rightUpperLegAct = new CosineDoubleFrecActuator();
    
    leftLowerLegAct = new CosineDoubleFrecActuator(true);
    leftUpperLegAct = new CosineDoubleFrecActuator(true);
}

GenericBodyParameters::~GenericBodyParameters() {
}