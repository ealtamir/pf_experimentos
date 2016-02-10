//
//  GenericActuatorHip.hpp
//  TorqueResearch
//
//  Created by Enzo Altamiranda G on 22.01.16.
//  Copyright © 2016 Enzo Altamiranda G. All rights reserved.
//

#ifndef GenericActuatorHip_hpp
#define GenericActuatorHip_hpp

#include <stdio.h>
#include "GenericActuator.h"

class GenericActuatorHip : public GenericActuator {
    
protected:
    btVector3 actuatorFunc(double t, int stage);
    
};

#endif /* defined(__test__GenericActuator__) */