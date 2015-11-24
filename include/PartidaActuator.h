//
//  PartidaActuator.h
//  MongoDoll
//
//  Created by Teresa Fontanella De Santis on 11/21/15.
//  Copyright (c) 2015 PF15. All rights reserved.
//

#ifndef __MongoDoll__PartidaActuator__
#define __MongoDoll__PartidaActuator__

#include <stdio.h>

#include "Actuator.h"

class PartidaActuator : public Actuator {
    
public:
    PartidaActuator(bool isLeft = false);
    
    virtual bool isFirstStep(double t);
    
    virtual void setActuatorValues(double vals[]);
    
protected:
    virtual btVector3 actuatorFunc(double t, int stage);
};

#endif /* defined(__MongoDoll__PartidaActuator__) */
