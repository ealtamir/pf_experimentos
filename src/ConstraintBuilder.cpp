//
//  ConstraintBuilder.cpp
//  test
//
//  Created by Enzo Altamiranda G on 20.07.15.
//  Copyright (c) 2015 Enzo Altamiranda G. All rights reserved.
//

#include "ConstraintBuilder.h"



btGeneric6DofConstraint*
ConstraintBuilder::create6DoFConstraint(ConstraintParams& params) {
    btGeneric6DofConstraint* joint6DOF;
    btTransform p1Trans, p2Trans;
    btVector3 euler;
    
    bool useLinearReferenceFrameA = true;
    
    p1Trans.setIdentity();
    p2Trans.setIdentity();
    
    if (params.p1_eulerZYX != nullptr) {
        euler = *params.p1_eulerZYX;
        p1Trans.getBasis().setEulerZYX(euler.x(), euler.y(), euler.z());
    }
    if (params.p2_eulerZYX != nullptr) {
        euler = *params.p2_eulerZYX;
        p2Trans.getBasis().setEulerZYX(euler.x(), euler.y(), euler.z());
    }
    
    p1Trans.setOrigin(params.p1_Offset);
    p2Trans.setOrigin(params.p2_Offset);
    
    btRigidBody* p1 = params.p1->getRigidBody();
    btRigidBody* p2 = params.p2->getRigidBody();
    
    joint6DOF = new btGeneric6DofConstraint(*p1,
                                            *p2,
                                            p1Trans,
                                            p2Trans,
                                            useLinearReferenceFrameA
                                            );
    

    joint6DOF->setAngularLowerLimit(params.angularLowerLimit);
    joint6DOF->setAngularUpperLimit(params.angulerUpperLimit);

    return joint6DOF;
}