#include "CapsuleBodyPart.h"
#include <BulletDynamics/btBulletDynamicsCommon.h>


CapsuleBodyPart::CapsuleBodyPart(btScalar radius,
                                 btScalar height,
                                 btScalar mass,
                                 const btTransform& transform, btVector3 centerofMass) {

    CapsuleBodyPart(radius, height, mass, transform, nullptr, centerofMass);
}

CapsuleBodyPart::CapsuleBodyPart(btScalar r,
                                 btScalar h,
                                 btScalar m,
                                 const btTransform &trans,
                                 Actuator* actuator, btVector3 centerofMass) {
    this->actuator = actuator;
    
    btVector3 inertia(0, 0, 0);
//    btQuaternion rotation(0, 0, 0, 1);
    
    btCollisionShape* capsule = new btCapsuleShape(r, h);
    
    btCompoundShape* compound = new btCompoundShape();
    btTransform localTrans;
    localTrans.setIdentity();
    //localTrans effectively shifts the center of mass with respect to the chassis
    localTrans.setOrigin(btVector3(0,0,1));
    compound->addChildShape(localTrans,capsule);
    
    
    btDefaultMotionState* motionState = new btDefaultMotionState(trans);
    
    capsule->calculateLocalInertia(m, inertia);
    btRigidBody::btRigidBodyConstructionInfo capsuleCI(m, motionState, capsule, inertia);
    
    capsuleCI.m_additionalDamping = true;
    
    body = new btRigidBody(capsuleCI);
    
    body->setDamping(LINEAR_DAMPING, ANGULAR_DAMPING);
    body->setDeactivationTime(DEACTIVATION_TIME);
    body->setSleepingThresholds(LINEAR_SLEEPING_THRESHOLD, ANGULAR_SLEEPING_THRESHOLD);
    
}


