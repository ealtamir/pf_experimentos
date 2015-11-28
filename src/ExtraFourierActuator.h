//
//  ExtraFourierActuator.hpp
//  TorqueResearch
//
//  Created by Enzo Altamiranda G on 20.11.15.
//  Copyright © 2015 Enzo Altamiranda G. All rights reserved.
//

#ifndef ExtraFourierActuator_hpp
#define ExtraFourierActuator_hpp

#include <stdio.h>
#include "Actuator.h"

class ExtraFourierActuator : public Actuator {
    
public:
    ExtraFourierActuator();
    
    virtual void setActuatorValues(double vals[]);
    
    virtual void setActuatorValues(double vals1[], double vals2[]);
    
    virtual Actuator* clone();
    
protected:
    virtual btVector3 actuatorFunc(double t, int stage);
    
};

#endif /* ExtraFourierActuator_hpp */
