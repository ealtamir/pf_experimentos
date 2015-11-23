//
//  CosineDoubleFrecBody.hpp
//  TorqueResearch
//
//  Created by Enzo Altamiranda G on 15.11.15.
//  Copyright © 2015 Enzo Altamiranda G. All rights reserved.
//

#ifndef CosineDoubleFrecBody_hpp
#define CosineDoubleFrecBody_hpp

#include <stdio.h>
#include "WalkerBody.h"

class CosineDoubleFrecBody : public WalkerBody {
    
public:
    CosineDoubleFrecBody(btDynamicsWorld* world, BodyParameters &params);
    
    virtual void setActuatorValues(int index, std::vector<double> vals);

};

#endif /* CosineDoubleFrecBody_hpp */
