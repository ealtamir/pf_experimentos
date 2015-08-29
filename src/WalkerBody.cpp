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
    return v.getOrigin().getZ();
}

double
WalkerBody::getAngleInclination(){
    GenericTorsoBodyGroup* torso = dynamic_cast<GenericTorsoBodyGroup*>(bodyGroups.back());
    BodyPart* bp = torso->getLeftHipPart();
    btRigidBody* rigidBody = bp->getRigidBody();
    btTransform v = rigidBody->getCenterOfMassTransform();
    double x = v.getOrigin().getX();
    double y = v.getOrigin().getY();
    if (x==0){
        return 0;
    }
    double lala = x/y;
    double lala3 = (asin(fmin(1.0, fmax(-1.0,x/y)))*180/M_PI);
    return (asin(fmin(1.0, fmax(-1.0,x/y)))*180/M_PI);
    //return (acos(fmin(1.0, fmax(-1.0,y/x)))*180/M_PI); // lo del fmin y fmax es para limitar el input de acos entre 1 y -1 (y a veces puede haber error de cómputo)
}