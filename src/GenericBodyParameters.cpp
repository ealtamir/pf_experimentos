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
    rightLowerArmAct = new FourierActuator();
    rightUpperArmAct = new FourierActuator();
    
    leftLowerArmAct = new FourierActuator();
    leftUpperArmAct = new FourierActuator();
    
    hipAct = new FourierActuator();
    
    rightLowerLegAct = new FourierActuator();
    rightUpperLegAct = new FourierActuator();
    
    leftLowerLegAct = new FourierActuator(true);
    leftUpperLegAct = new FourierActuator(true);
}

GenericBodyParameters::~GenericBodyParameters() {
    delete rightLowerArmAct;
    delete rightUpperArmAct;
    
    delete leftLowerArmAct;
    delete leftUpperLegAct;
    
    delete hipAct;
    
    delete rightLowerLegAct;
    delete rightUpperLegAct;
    
    delete leftLowerLegAct;
    delete leftUpperLegAct;
}