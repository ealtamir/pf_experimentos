//
//  ObjectStoppedCondition.cpp
//  pf2
//
//  Created by Enzo Altamiranda G on 26.04.15.
//  Copyright (c) 2015 Enzo Altamiranda G. All rights reserved.
//

#include "ObjectStoppedCondition.h"
#include "Experiment.h"

ObjectStoppedCondition::ObjectStoppedCondition(btRigidBody* body)
{
    this->body = body;
    counter.counter = 0;
    counter.position = btVector3(0, 0, 0);
}

bool ObjectStoppedCondition::stopConditionMet()
{
    btTransform trans;
    body->getMotionState()->getWorldTransform(trans);
    btVector3 currentPos = trans.getOrigin();
    
    btScalar diff = currentPos.distance2(counter.position);
    
    if (diff < DEFAULT_EXPERIMENT_INTERVAL
        && counter.counter >= SIMULATION_STEPS) {
        return true;
    } else if (diff < 0.001) {
        counter.counter += 1;
    } else {
        counter.position = currentPos;
        counter.counter = 0;
    }
    return false;
}