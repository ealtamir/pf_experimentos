//
//  FourierActuator.h
//  proyecto_pf
//
//  Created by Enzo Altamiranda G on 17.08.15.
//  Copyright (c) 2015 Enzo Altamiranda G. All rights reserved.
//

#ifndef __proyecto_pf__FourierActuator__
#define __proyecto_pf__FourierActuator__

#include <stdio.h>
#include "Actuator.h"

class FourierActuator : public Actuator {
    
public:
    FourierActuator(bool isLeft);
    
    double A1 = 0;
    double A2 = 0;
    double A3 = 0;
    double A4 = 0;
    double w = 0;
    double C = 0;
    
protected:
    virtual btVector3
    actuatorFunc(double t);
};

#endif /* defined(__proyecto_pf__FourierActuator__) */
