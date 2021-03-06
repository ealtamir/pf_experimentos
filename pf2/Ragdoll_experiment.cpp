//
//  Ragdoll_experiment.cpp
//  pf2
//
//  Created by tom on 5/14/15.
//  Copyright (c) 2015 Enzo Altamiranda G. All rights reserved.
//

#include "Ragdoll_experiment.h"
#include "test_constants.h"


void Ragdoll_experiment::initializeBodies() {
    ground = createGround();
    ragDoll = createRagdoll();
    
    ground->setFriction(GROUND_FRICTION);
    ground->setRestitution(GROUND_RESTITUTION);
}


void Ragdoll_experiment::initObjects() {
    objectsInitialized = true;
}

void Ragdoll_experiment::worldStep() {
    //float seconds = difftime(time(0), startTime);
    startTime = time(0);
//    ragDoll->m_bodies[RagDoll::BODYPART_PELVIS]->applyForce(btVector3(0, 50, 0), btVector3(0., 0., 0.));
}

bool Ragdoll_experiment::stopExperiment()
{
    return condition.stopConditionMet();
}