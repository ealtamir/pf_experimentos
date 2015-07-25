//
//  ConstraintBuilder.cpp
//  test
//
//  Created by Enzo Altamiranda G on 20.07.15.
//  Copyright (c) 2015 Enzo Altamiranda G. All rights reserved.
//

#include "ConstraintBuilder.h"


btGeneric6DofConstraint*
ConstraintBuilder::create6DoFConstraint(BodyPart* p1,
                                BodyPart* p2,
                                const btVector3 &offset1,
                                const btVector3 &offset2,
                                const btVector3 &angularUpperLimit,
                                double multiplier) {
    btGeneric6DofConstraint* joint6DOF;
    btTransform p1Trans, p2Trans;
    bool useLinearReferenceFrameA = true;
    
    p1Trans.setIdentity();
    p2Trans.setIdentity();
    
    p1Trans.setOrigin(offset1);
    p2Trans.setOrigin(offset2);
    
    joint6DOF = new btGeneric6DofConstraint(*p1->getRigidBody(),
                                            *p2->getRigidBody(),
                                            p1Trans,
                                            p2Trans,
                                            useLinearReferenceFrameA
                                            );
    
#ifdef RIGID
    joint6DOF->setAngularLowerLimit(btVector3(-SIMD_EPSILON,-SIMD_EPSILON,-SIMD_EPSILON));
    joint6DOF->setAngularUpperLimit(btVector3(SIMD_EPSILON,SIMD_EPSILON,SIMD_EPSILON));
#else
    joint6DOF->setAngularLowerLimit(btVector3(-SIMD_EPSILON,-SIMD_EPSILON,-SIMD_EPSILON));
    joint6DOF->setAngularUpperLimit(angularUpperLimit);
#endif
    
    return joint6DOF;
}

btGeneric6DofConstraint*
ConstraintBuilder::generatePartsJoint(BodyPart *upperPart,
                           BodyPart *lowerPart,
                           const btVector3 upperOffset,
                           const btVector3 lowerOffset,
                           double multiplier) {
    
    btVector3 angularUpperLimit(SIMD_PI * 0.7f, SIMD_EPSILON, SIMD_EPSILON);
    return create6DoFConstraint(upperPart, lowerPart, upperOffset, lowerOffset, angularUpperLimit, multiplier);
}