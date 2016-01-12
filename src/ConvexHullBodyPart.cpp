//
//  ConvexHullBodyPart.cpp
//  Prueba2
//
//  Created by Tomas Mehdi on 8/5/15.
//  Copyright (c) 2015 Tomas Mehdi. All rights reserved.
//

#include "ConvexHullBodyPart.h"
#include <BulletDynamics/btBulletDynamicsCommon.h>


ConvexHullBodyPart::ConvexHullBodyPart(btVector3 points[], btScalar mass, const btTransform& transform) {
    btVector3 inertia(0, 0, 0);
    btQuaternion rotation(0, 0, 0, 1);
    
    this->radius = 0.075;
    this->height = 0.075;
    
    btConvexHullShape* convexHullShape = new btConvexHullShape(0,0,sizeof(btVector3));
    convexHullShape->addPoint(btVector3(-0.075 ,0.015     ,-0.075*0.1));
    convexHullShape->addPoint(btVector3(0.075  ,0.015     ,-0.075*0.1));
    
    convexHullShape->addPoint(btVector3(-0.075 ,0.015     ,0.075*0.1));
    convexHullShape->addPoint(btVector3(0.075  ,0.015     ,0.075*0.1));
    
    btDefaultMotionState* motionState = new btDefaultMotionState(transform);
    convexHullShape->calculateLocalInertia(mass, inertia);
    btRigidBody::btRigidBodyConstructionInfo capsuleCI(mass, motionState, convexHullShape, inertia);
    
    capsuleCI.m_additionalDamping = true;
    
    body = new btRigidBody(capsuleCI);
    body->setFriction(1);
    
    body->setDamping(LINEAR_DAMPING, ANGULAR_DAMPING);
    body->setDeactivationTime(DEACTIVATION_TIME);
    body->setSleepingThresholds(LINEAR_SLEEPING_THRESHOLD, ANGULAR_SLEEPING_THRESHOLD);
}
