//
//  WalkerBody.cpp
//  test
//
//  Created by Enzo Altamiranda G on 05.08.15.
//  Copyright (c) 2015 Enzo Altamiranda G. All rights reserved.
//

#include "WalkerBody.h"
#include "GenericTorsoBodyGroup.h"
#include "LegBodyGroup.h"
#include "Initialization.h"
#include <iostream>
#include "IOTools.h"

void printBodyParty(BodyPart* bodyPart);

WalkerBody::WalkerBody(btDynamicsWorld* world, BodyParameters &params) : Body(world) {
    
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

BodyPart* WalkerBody::getLeftFoot() {
    return bodyGroups[0]->getBodyParts()[2];
}

BodyPart* WalkerBody::getRightFoot() {
    return bodyGroups[1]->getBodyParts()[2];
}

BodyPart* WalkerBody::getHip() {
    return bodyGroups[2]->getBodyParts()[0];
}

BodyPart* WalkerBody::getLowerLeftLeg() {
    return bodyGroups[0]->getBodyParts()[0];
}

BodyPart* WalkerBody::getUpperLeftLeg() {
    return bodyGroups[0]->getBodyParts()[1];
}

BodyPart* WalkerBody::getLowerRightLeg() {
    return bodyGroups[1]->getBodyParts()[0];
}

BodyPart* WalkerBody::getUpperRightLeg() {
    return bodyGroups[1]->getBodyParts()[1];
}

void WalkerBody::printPositions(int i) {
    storeOvitoLine(7, i);
//    std::cout << 6 << std::endl;
//    std::cout << i << std::endl;
    printBodyParty(getHip());
    printBodyParty(getUpperLeftLeg());
    printBodyParty(getLowerLeftLeg());
    printBodyParty(getLeftFoot());
    
    printBodyParty(getUpperRightLeg());
    printBodyParty(getLowerRightLeg());
    printBodyParty(getRightFoot());

}

void printBodyParty(BodyPart* bodyPart) {
    btRigidBody* rigidBody = bodyPart->getRigidBody();
    double radius = bodyPart->getRadius();
    double height = bodyPart->getHeight();
    btVector3 ull = rigidBody->getCenterOfMassPosition();
    btTransform transform, rectAngleTransformXAxis, resultTransform;
    rectAngleTransformXAxis.setRotation(btQuaternion(1,0,0,1));
    
    rigidBody->getMotionState()->getWorldTransform(transform);
    
    resultTransform = transform*rectAngleTransformXAxis;
    btQuaternion ullr = resultTransform.getRotation();

    storeOvitoLineValues(ull, ullr, radius, height);
//    std::cout << ull.x() << "\t" << ull.y() << "\t" << ull.z() << "\t";
//    std::cout << ullr.x() << "\t" << ullr.y() << "\t" << ullr.z() << "\t" << ullr.w() << std::endl;
}

