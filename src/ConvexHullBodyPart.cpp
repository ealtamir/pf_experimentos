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
    
    
    btConvexHullShape* convexHullShape = new btConvexHullShape(0,0,sizeof(btVector3));
    convexHullShape->addPoint(btVector3(0        ,0.03     ,0));
    convexHullShape->addPoint(btVector3(0.075*2  ,0.03     ,0));
    
    convexHullShape->addPoint(btVector3(0        ,0.03/10  ,2*0.15/8));
    convexHullShape->addPoint(btVector3(0.075*2  ,0.03/10  ,2*0.15/8));
    
    convexHullShape->addPoint(btVector3(0        ,0        ,2*0.15/4));
    convexHullShape->addPoint(btVector3(0.075*2  ,0        ,2*0.15/4));
    
    convexHullShape->addPoint(btVector3(0        ,0.03/10  ,2*0.15*3/8));
    convexHullShape->addPoint(btVector3(0.075*2  ,0.03/10  ,2*0.15*3/8));
    
    convexHullShape->addPoint(btVector3(0        ,0.03     ,2*0.15/2));
    convexHullShape->addPoint(btVector3(0.075*2  ,0.03     ,2*0.15/2));
    
    btDefaultMotionState* motionState = new btDefaultMotionState(transform);
    convexHullShape->calculateLocalInertia(mass, inertia);
    btRigidBody::btRigidBodyConstructionInfo capsuleCI(mass, motionState, convexHullShape, inertia);
    
    capsuleCI.m_additionalDamping = true;
    
    body = new btRigidBody(capsuleCI);
    
    body->setDamping(LINEAR_DAMPING, ANGULAR_DAMPING);
    body->setDeactivationTime(DEACTIVATION_TIME);
    body->setSleepingThresholds(LINEAR_SLEEPING_THRESHOLD, ANGULAR_SLEEPING_THRESHOLD);
}
