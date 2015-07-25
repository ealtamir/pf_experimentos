//
//  ConstraintBuilder.h
//  test
//
//  Created by Enzo Altamiranda G on 20.07.15.
//  Copyright (c) 2015 Enzo Altamiranda G. All rights reserved.
//

#ifndef __test__ConstraintBuilder__
#define __test__ConstraintBuilder__

#include <stdio.h>
#include <BulletDynamics/btBulletDynamicsCommon.h>
#include "BodyPart.h"

typedef struct {
    BodyPart* p1;
    BodyPart* p2;
    
    btVector3 p1_Offset;
    btVector3 p2_Offset;
    
    btVector3 p1_eulerZYX;
    btVector3 p2_eulerZYX;
    
    btVector3& angulerUpperLimit;
    btVector3& angularLowerLimit;
    
    double multiplier;
} ConstraintParams;

class ConstraintBuilder {
    
public:
    btGeneric6DofConstraint*
    generatePartsJoint(BodyPart *p1,
                       BodyPart *p2,
                       const btVector3 p1Offset,
                       const btVector3 p2Offset,
                       double multiplier);
    
    btGeneric6DofConstraint*
    create6DoFConstraint(BodyPart* p1,
                         BodyPart* p2,
                         const btVector3 &offset1,
                         const btVector3 &offset2,
                         const btVector3 &angularUpperLimit,
                         double multiplier);
};

#endif /* defined(__test__ConstraintBuilder__) */
