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
    ragDoll->m_bodies[RagDoll::BODYPART_PELVIS]->applyForce(btVector3(0, 53, 0), btVector3(0., 0., 0.));
    if(startTime < 35) {
        ragDoll->m_bodies[RagDoll::BODYPART_PELVIS]->applyTorque(btVector3(0, -2, 0));
    }
    if(sin(startTime*SIMD_PI/70) < -0.99) {
        ragDoll->m_bodies[RagDoll::BODYPART_PELVIS]->applyForce(btVector3(30, 0, 0), btVector3(0., 0., 0.));
        ragDoll->m_bodies[RagDoll::BODYPART_PELVIS]->applyTorque(btVector3(0, 10, 0));
    }
    if(sin(startTime*SIMD_PI/70) > 0.99) {
        ragDoll->m_bodies[RagDoll::BODYPART_PELVIS]->applyForce(btVector3(-30, 0, 0), btVector3(0., 0., 0.));
        ragDoll->m_bodies[RagDoll::BODYPART_PELVIS]->applyTorque(btVector3(0, -10, 0));
    }
    
    for (int i = 0; i < RagDoll::BODYPART_COUNT; ++i) {
        ragDoll->m_bodies[i]->applyForce(btVector3(0, 0, -1.5), btVector3(0., 0., 0.));
    }

    startTime++;
}

bool Ragdoll_experiment::stopExperiment()
{
    return condition.stopConditionMet();
}