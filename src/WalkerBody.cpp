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
