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
    virtual void setActuatorValues(double vals[]);
    
    virtual Actuator* clone();
    
protected:
    virtual btVector3 actuatorFunc(double t, int stage);
};

#endif /* defined(__proyecto_pf__FourierActuator__) */
