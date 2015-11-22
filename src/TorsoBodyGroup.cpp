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
}

BodyPart*
TorsoBodyGroup::createHead(BodyParameters &params, const btVector3 positionAdjust) {
    
    btVector3 headPos(params.HEAD_POSITION.x() * positionAdjust.x(),
                      params.HEAD_POSITION.y() * positionAdjust.y(),
                      params.HEAD_POSITION.z() * positionAdjust.z());
    
    btVector3 centerOfMass(0,0,0);
    
    BodyPart* head = generateStandardPart(params.HEAD_RADIUS,
                                          params.HEAD_HEIGHT,
                                          params.HEAD_MASS,
                                          headPos,
                                          params.bodyInitialPosition,
                                          centerOfMass,BodyGroup::null_fill);
    
    bodyParts.push_back(head);
    return head;
}

BodyPart*
TorsoBodyGroup::createSpine(BodyParameters &params, const btVector3 positionAdjust) {
 
    
    btVector3 spinePos(params.SPINE_POSITION.x() * positionAdjust.x(),
                       params.SPINE_POSITION.y() * positionAdjust.y(),
                       params.SPINE_POSITION.z() * positionAdjust.z());
    
    btVector3 centerOfMass(0,0,0);
    
    BodyPart* spine = generateStandardPart(params.SPINE_RADIUS,
                                           params.SPINE_HEIGHT,
                                           params.SPINE_HEIGHT,
                                           spinePos,
                                           params.bodyInitialPosition,
                                           centerOfMass);
    
    bodyParts.push_back(spine);
    return spine;
}

BodyPart*
TorsoBodyGroup::createPelvis(BodyParameters &params, const btVector3 positionAdjust) {

    btVector3 pelvisPos(params.PELVIS_POSITION.x() * positionAdjust.x(),
                        params.PELVIS_POSITION.y() * positionAdjust.y(),
                        params.PELVIS_POSITION.z() * positionAdjust.z());
    
    //btVector3 centerOfMass(0, params.PELVIS_HEIGHT/2+params.PELVIS_RADIUS, 0);
    btVector3 centerOfMass(0, 0, 0);
    
    BodyPart* pelvis = generateStandardPart(params.PELVIS_RADIUS,
                                            params.PELVIS_HEIGHT,
                                            params.PELVIS_MASS,
                                            pelvisPos,
                                            params.bodyInitialPosition,                                            centerOfMass);
    
    bodyParts.push_back(pelvis);
    return pelvis;
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
    
    btGeneric6DofConstraint* constraint = ConstraintBuilder::create6DoFConstraint(constraintParams);
    constraints.push_back(constraint);

    return constraint;
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
    
    btGeneric6DofConstraint* constraint = ConstraintBuilder::create6DoFConstraint(constraintParams);
    constraints.push_back(constraint);
    
    return constraint;
}
