//
//  WalkerBody.cpp
//  test
//
//  Created by Enzo Altamiranda G on 05.08.15.
//  Copyright (c) 2015 Enzo Altamiranda G. All rights reserved.
//

#include "WalkerBody.h"
#include "TorsoBodyGroup.h"

WalkerBody::WalkerBody(btDynamicsWorld* world, BodyParameters &params) : GenericBody(world, params) {
    
    BodyGroup* leftArm = createLeftArm(world, params);
    BodyGroup* rightArm = createRightArm(world, params);
    BodyGroup* leftLeg = createLeftLeg(world, params);
    BodyGroup* rightLeg = createRightLeg(world, params);
    BodyGroup* torso = createTorso(world, params);
    
    TorsoBodyGroup* torsoGroup = dynamic_cast<TorsoBodyGroup*>(torso);
    
    createLeftShoulder(leftArm->getJointPart(),
                       torsoGroup->getLeftShoulderPart(),
                       params);
    createRightShoulder(rightArm->getJointPart(),
                        torsoGroup->getRightShoulderPart(),
                        params);
    createLeftHip(leftLeg->getJointPart(),
                  torsoGroup->getLeftHipPart(),
                  params);
    createRightHip(rightLeg->getJointPart(),
                   torsoGroup->getRightHipPart(),
                   params);
}