//
//  WalkerBody.cpp
//  test
//
//  Created by Enzo Altamiranda G on 05.08.15.
//  Copyright (c) 2015 Enzo Altamiranda G. All rights reserved.
//

#include "WalkerBody.h"
#include "GenericTorsoBodyGroup.h"

WalkerBody::WalkerBody(btDynamicsWorld* world, BodyParameters &params) : GenericBody(world, params) {
    

    BodyGroup* leftLeg = createLeftLeg(world, params);
    BodyGroup* rightLeg = createRightLeg(world, params);
    BodyGroup* torso = createTorso(world, params);
    
    GenericTorsoBodyGroup* torsoGroup = dynamic_cast<GenericTorsoBodyGroup*>(torso);
    

    createLeftHip(leftLeg->getJointPart(),
                  torsoGroup->getLeftHipPart(),
                  params);
    createRightHip(rightLeg->getJointPart(),
                   torsoGroup->getRightHipPart(),
                   params);

}

BodyGroup*
WalkerBody::createTorso(btDynamicsWorld* world, BodyParameters &params) {
    
    BodyGroup* torso = new GenericTorsoBodyGroup(world,
                                          params,
                                          rightOffset);
    bodyGroups.push_back(torso);
    torso->initBodyGroup();
    return torso;
}

std::vector<BodyGroup*> WalkerBody::getBodyGroups(){
    return bodyGroups;
}

double
WalkerBody::getHeight(){
    GenericTorsoBodyGroup* torso = dynamic_cast<GenericTorsoBodyGroup*>(bodyGroups.back());
    BodyPart* bp = torso->getLeftHipPart();
    btRigidBody* rigidBody = bp->getRigidBody();
    btTransform v = rigidBody->getCenterOfMassTransform();
    return v.getOrigin().getY();
}

double
WalkerBody::getPosition(){
    GenericTorsoBodyGroup* torso = dynamic_cast<GenericTorsoBodyGroup*>(bodyGroups.back());
    BodyPart* bp = torso->getLeftHipPart();
    btRigidBody* rigidBody = bp->getRigidBody();
    btTransform v = rigidBody->getCenterOfMassTransform();
    return v.getOrigin().getX();
}