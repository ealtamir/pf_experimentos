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
#include <math.h>
#include "Body.h"
#include "Experiment.h"

const btScalar BODY_PART_QTY = 6;




class WalkerBody : public Body {
public:
    WalkerBody(btDynamicsWorld* world, BodyParameters &params);

};


#endif /* defined(__test__WalkerBody__) */
