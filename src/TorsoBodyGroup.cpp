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
                               BodyParameters &params,
                               const btVector3 positionAdjust) : BodyGroup(world) {
    
    
    btVector3 headPos(params.HEAD_POSITION.x() * positionAdjust.x(),
                      params.HEAD_POSITION.y() * positionAdjust.y(),
                      params.HEAD_POSITION.z() * positionAdjust.z());
    BodyPart* head = generateStandardPart(params.HEAD_RADIUS,
                                          params.HEAD_HEIGHT,
                                          params.HEAD_MASS,
                                          headPos,
                                          params.bodyInitialPosition);
    
    btVector3 spinePos(params.SPINE_POSITION.x() * positionAdjust.x(),
                       params.SPINE_POSITION.y() * positionAdjust.y(),
                       params.SPINE_POSITION.z() * positionAdjust.z());
    BodyPart* spine = generateStandardPart(params.SPINE_RADIUS,
                                           params.SPINE_HEIGHT,
                                           params.SPINE_HEIGHT,
                                           spinePos,
                                           params.bodyInitialPosition);
    
    btVector3 pelvisPos(params.PELVIS_POSITION.x() * positionAdjust.x(),
                        params.PELVIS_POSITION.y() * positionAdjust.y(),
                        params.PELVIS_POSITION.z() * positionAdjust.z());
    BodyPart* pelvis = generateStandardPart(params.PELVIS_RADIUS,
                                            params.PELVIS_HEIGHT,
                                            params.PELVIS_MASS,
                                            pelvisPos,
                                            params.bodyInitialPosition);
    
    bodyParts.push_back(head);
    bodyParts.push_back(spine);
    bodyParts.push_back(pelvis);
    

    btTypedConstraint* headSpineConstaint = createHeadSpineConstraint(head, spine, params);
    

    btTypedConstraint* spinePelvisConstraint = createSpinePelvisConstraint(spine, pelvis, params);
    constraints.push_back(headSpineConstaint);
    constraints.push_back(spinePelvisConstraint);
}

btGeneric6DofConstraint*
TorsoBodyGroup::createHeadSpineConstraint(BodyPart* head, BodyPart* spine, BodyParameters &params) {
    
    ConstraintParams constraintParams = {
        spine,
        head,
        params.neckUpperSpineOffset,
        params.headOffset,
        nullptr,
        nullptr,
        params.neckLowerAngularLimit,
        params.neckUpperAngularLimit
    };
    
    return ConstraintBuilder::create6DoFConstraint(constraintParams);

    
}

btGeneric6DofConstraint*
TorsoBodyGroup::createSpinePelvisConstraint(BodyPart* spine, BodyPart* pelvis, BodyParameters &params) {
    
    ConstraintParams constraintParams = {
        spine,
        pelvis,
        params.lowerSpineOffset,
        params.pelvisOffset,
        &params.hipSpine_eulerZYX,
        &params.hipPelvis_eulerZYX,
        params.hipLowerAngularLimit,
        params.hipUpperAngularLimit
    };
    
    return ConstraintBuilder::create6DoFConstraint(constraintParams);
}