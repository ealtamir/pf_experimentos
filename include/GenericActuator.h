//
//  GenericActuator.h
//  test
//
//  Created by Enzo Altamiranda G on 04.08.15.
//  Copyright (c) 2015 Enzo Altamiranda G. All rights reserved.
//

#ifndef __test__GenericActuator__
#define __test__GenericActuator__

#include <stdio.h>
#include <vector>
#include "Actuator.h"

enum GenericActuatorParams {
    
};

class GenericActuator : public Actuator {
    
public:
    virtual void setActuatorValues(double vals[]);
    
    virtual Actuator* clone();
    
protected:
    btVector3 actuatorFunc(double t, int stage);
    
};

#endif /* defined(__test__GenericActuator__) */
