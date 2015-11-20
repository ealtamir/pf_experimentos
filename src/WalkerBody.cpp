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

