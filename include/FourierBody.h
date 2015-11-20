//
//  FourierBody.hpp
//  TorqueResearch
//
//  Created by Enzo Altamiranda G on 15.11.15.
//  Copyright © 2015 Enzo Altamiranda G. All rights reserved.
//

#ifndef FourierBody_hpp
#define FourierBody_hpp

#include "WalkerBody.h"
#include "BodyParameters.h"

class FourierBody : public WalkerBody {
    
public:
    FourierBody(btDynamicsWorld* world, BodyParameters &params);
    
    virtual void setActuatorValues(std::vector<double> vals);
};

#endif /* FourierBody_hpp */
