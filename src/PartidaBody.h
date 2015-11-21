//
//  PartidaBody.h
//  MongoDoll
//
//  Created by Teresa Fontanella De Santis on 11/21/15.
//  Copyright (c) 2015 PF15. All rights reserved.
//

#ifndef __MongoDoll__PartidaBody__
#define __MongoDoll__PartidaBody__

#include <stdio.h>

#include "WalkerBody.h"
#include "BodyParameters.h"

class PartidaBody : public WalkerBody {
    
public:
    PartidaBody(btDynamicsWorld* world, BodyParameters &params);
    
    virtual void setActuatorValues(std::vector<double> vals);
};

#endif /* defined(__MongoDoll__PartidaBody__) */
