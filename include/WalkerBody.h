//
//  WalkerBody.h
//  test
//
//  Created by Enzo Altamiranda G on 05.08.15.
//  Copyright (c) 2015 Enzo Altamiranda G. All rights reserved.
//

#ifndef __test__WalkerBody__
#define __test__WalkerBody__

#include <stdio.h>
#include "GenericBody.h"

class WalkerBody : public GenericBody {
public:
    WalkerBody(btDynamicsWorld* world, BodyParameters &params);
    std::vector<BodyGroup*> getBodyGroups();
    double getHeight();
    double getPosition();
    
protected:
    virtual BodyGroup*
    createTorso(btDynamicsWorld* world, BodyParameters &params);
};


#endif /* defined(__test__WalkerBody__) */
