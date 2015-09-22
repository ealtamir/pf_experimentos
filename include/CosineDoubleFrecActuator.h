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

class CosineDoubleFrecActuator : public Actuator {
    
public:
    CosineDoubleFrecActuator(bool isLeft = false);
    
protected:
    virtual btVector3
    actuatorFunc(double t);
};

#endif /* defined(__proyecto_pf__FourierActuator__) */
