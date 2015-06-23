//
//  TorsoBodyGroup.cpp
//  test
//
//  Created by Enzo Altamiranda G on 23.06.15.
//  Copyright (c) 2015 Enzo Altamiranda G. All rights reserved.
//

#include "TorsoBodyGroup.h"

TorsoBodyGroup::TorsoBodyGroup(btDynamicsWorld* world,
                               double multiplier,
                               const btVector3 positionOffset) : BodyGroup(world) {
    
    BodyPart* head = generateStandardPart(multiplier * HEAD_R,
                                          multiplier * HEAD_H,
                                          HEAD_M,
                                          positionOffset);
    
    BodyPart* spine = generateStandardPart(multiplier * SPINE_R,
                                           multiplier * SPINE_H,
                                           SPINE_M,
                                           positionOffset);
    
    BodyPart* pelvis = generateStandardPart(multiplier * PELVIS_R,
                                            multiplier * SPINE_H,
                                            SPINE_M,
                                            positionOffset);
    
    bodyParts.push_back(head);
    bodyParts.push_back(spine);
    bodyParts.push_back(pelvis);
    
    btVector3 headOffset(btScalar(0.), btScalar(0.30 * multiplier), btScalar(0.));
    btVector3 upperSpineOffset(btScalar(0.), btScalar(-0.14 * multiplier), btScalar(0.));
    btTypedConstraint* headSpineConstaint = genericPartJoin(head, spine, headOffset, upperSpineOffset, multiplier);
    
    btVector3 pelvisOffset(btScalar(0.), btScalar(0.15 * multiplier), btScalar(0.));
    btVector3 lowerSpineOffset(btScalar(0.), btScalar(-0.15 * multiplier), btScalar(0.));
    btTypedConstraint* spinePelvisConstraint = genericPartJoin(spine, pelvis, pelvisOffset, lowerSpineOffset, multiplier);
    
    constraints.push_back(headSpineConstaint);
    constraints.push_back(spinePelvisConstraint);
}