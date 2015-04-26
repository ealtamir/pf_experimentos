//
//  ObjectStoppedCondition.cpp
//  pf2
//
//  Created by Enzo Altamiranda G on 26.04.15.
//  Copyright (c) 2015 Enzo Altamiranda G. All rights reserved.
//

#include "ObjectStoppedCondition.h"

ObjectStoppedCondition::ObjectStoppedCondition(btRigidBody* body)
{
    counter.counter = 0;
    counter.position = btVector3(0, 0, 0);
}

bool ObjectStoppedCondition::stopConditionMet()
{
    btVector3 currentPos = body->getWorldTransform().getOrigin();
    if (counter.position == currentPos && counter.counter >= 10) {
        return true;
    } else if (counter.position == currentPos) {
        counter.counter += 1;
    } else {
        counter.position = currentPos;
        counter.counter = 0;
    }
    return false;
}