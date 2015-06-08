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
    ragDoll->m_bodies[RagDoll::BODYPART_PELVIS]->applyForce(btVector3(5*sin(startTime*SIMD_PI/100), 60, 0), btVector3(0., 0., 0.));
    ragDoll->m_bodies[RagDoll::BODYPART_RIGHT_UPPER_LEG]-> applyCentralForce(btVector3(0,5*sin(startTime*SIMD_PI/100), 0));
    ragDoll->m_bodies[RagDoll::BODYPART_LEFT_UPPER_LEG]-> applyCentralForce(btVector3(0,5*cos(startTime*SIMD_PI/100), 0));
    for (int i = 0; i < RagDoll::BODYPART_COUNT; ++i) {
        ragDoll->m_bodies[i]->applyForce(btVector3(0, 0, -1), btVector3(0., 0., 0.));
    }
    printf("%f\n", 5*sin(startTime*SIMD_PI/100));
    printf("%d\n", startTime);
    startTime++;
}

bool Ragdoll_experiment::stopExperiment()
{
    return condition.stopConditionMet();
}