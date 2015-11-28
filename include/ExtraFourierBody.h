//
//  ExtraFourierBody.hpp
//  TorqueResearch
//
//  Created by Enzo Altamiranda G on 20.11.15.
//  Copyright © 2015 Enzo Altamiranda G. All rights reserved.
//

#ifndef ExtraFourierBody_hpp
#define ExtraFourierBody_hpp

#include <stdio.h>
#include "WalkerBody.h"

class ExtraFourierBody : public WalkerBody {
    
public:
    ExtraFourierBody(btDynamicsWorld* world, BodyParameters &params);
    
    virtual void setActuatorValues(std::vector<double> vals);
};

#endif /* ExtraFourierBody_hpp */
