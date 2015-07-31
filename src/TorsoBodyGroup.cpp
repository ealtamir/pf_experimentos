//
//  TorsoBodyGroup.cpp
//  test
//
//  Created by Enzo Altamiranda G on 23.06.15.
//  Copyright (c) 2015 Enzo Altamiranda G. All rights reserved.
//

#include "TorsoBodyGroup.h"
#include "ConstraintBuilder.h"

TorsoBodyGroup::TorsoBodyGroup(btDynamicsWorld* world,
                               double multiplier,
                               const btVector3 positionAdjust,
                               const btVector3 positionOffset) : BodyGroup(world) {
    
    btVector3 headPos(btScalar(0.) * positionAdjust.x(),
                      btScalar(multiplier * 1.6) * positionAdjust.y(),
                      btScalar(0.) * positionAdjust.z());
    BodyPart* head = generateStandardPart(multiplier * HEAD_R,
                                          multiplier * HEAD_H,
                                          HEAD_M,
                                          headPos,
                                          positionOffset);
    
    btVector3 spinePos(btScalar(0.) * positionAdjust.x(),
                       btScalar(multiplier * 1.6) * positionAdjust.y(),
                       btScalar(0.) * positionAdjust.z());
    BodyPart* spine = generateStandardPart(multiplier * SPINE_R,
                                           multiplier * SPINE_H,
                                           SPINE_M,
                                           spinePos,
                                           positionOffset);
    
    btVector3 pelvisPos(btScalar(0.) * positionAdjust.x(),
                        btScalar(multiplier * 1.) * positionAdjust.y(),
                        btScalar(0.) * positionAdjust.z());
    BodyPart* pelvis = generateStandardPart(multiplier * PELVIS_R,
                                            multiplier * SPINE_H,
                                            SPINE_M,
                                            pelvisPos,
                                            positionOffset);
    
    bodyParts.push_back(head);
    bodyParts.push_back(spine);
    bodyParts.push_back(pelvis);
    

    btTypedConstraint* headSpineConstaint = createHeadSpineConstraint(head, spine,
                                                                      multiplier);
    

    btTypedConstraint* spinePelvisConstraint = createSpinePelvisConstraint(spine, pelvis,
                                                                           multiplier);
    constraints.push_back(headSpineConstaint);
    constraints.push_back(spinePelvisConstraint);
}

btGeneric6DofConstraint*
TorsoBodyGroup::createHeadSpineConstraint(BodyPart* head, BodyPart* spine, double multiplier) {
    
    btVector3 upperSpineOffset(btScalar(0.), btScalar(0.30 * multiplier), btScalar(0.));
    btVector3 headOffset(btScalar(0.), btScalar(-0.14 * multiplier), btScalar(0.));
    
    btVector3 lowerAngularLimit(-SIMD_PI*0.3f,-SIMD_EPSILON,-SIMD_PI*0.3f);
    btVector3 upperAngularLimit(SIMD_PI*0.5f,SIMD_EPSILON,SIMD_PI*0.3f);
    
    ConstraintParams params = {
        spine,
        head,
        upperSpineOffset,
        headOffset,
        nullptr,
        nullptr,
        lowerAngularLimit,
        upperAngularLimit
    };
    
    return ConstraintBuilder::create6DoFConstraint(params);

    
}

btGeneric6DofConstraint*
TorsoBodyGroup::createSpinePelvisConstraint(BodyPart* spine, BodyPart* pelvis, double multiplier) {

    btVector3 pelvisOffset(btScalar(0.), btScalar(0.15 * multiplier), btScalar(0.));
    btVector3 lowerSpineOffset(btScalar(0.), btScalar(-0.15 * multiplier), btScalar(0.));
    
    btVector3 lowerAngularLimit(-SIMD_PI*0.2,-SIMD_EPSILON,-SIMD_PI*0.3);
    btVector3 upperAngularLimit(SIMD_PI*0.2,SIMD_EPSILON,SIMD_PI*0.6);
    
    btVector3 p1_eulerZYX(0, SIMD_HALF_PI, 0);
    btVector3 p2_eulerZYX(0, SIMD_HALF_PI, 0);
    
    ConstraintParams params = {
        spine,
        pelvis,
        lowerSpineOffset,
        pelvisOffset,
        &p1_eulerZYX,
        &p2_eulerZYX,
        lowerSpineOffset,
        upperAngularLimit,
        multiplier
    };
    
    return ConstraintBuilder::create6DoFConstraint(params);
}