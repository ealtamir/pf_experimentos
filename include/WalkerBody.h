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
#include "GenericBody.h"
#include "Experiment.h"

const btScalar BODY_PART_QTY = 6;




class WalkerBody : public GenericBody {
public:
    WalkerBody(btDynamicsWorld* world, BodyParameters &params);
    std::vector<BodyGroup*> getBodyGroups();
    double getHeight();
    double getPosition();
    btVector3 getVelocity();
    double getAngleInclination();
    void cicleQuantity();
    int getCycleQuantity();
    double* getAnglesLegs();
    
protected:
    
    virtual BodyGroup*
    createTorso(btDynamicsWorld* world, BodyParameters &params);
    int cicleQty = -1;
    double last_angle = 0;
    
    /* Se usan para calcular la direccion del doll, para el fitness*/
    //const btVector3 objetive = btVector3(0,0,-OBJETIVE_VELOCITY);
    const btVector3 objetive = btVector3(OBJETIVE_VELOCITY,0,0);
    
    btVector3 previous = btVector3(0,0,1);
};


#endif /* defined(__test__WalkerBody__) */
