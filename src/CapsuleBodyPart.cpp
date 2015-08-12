#include "CapsuleBodyPart.h"
#include <BulletDynamics/btBulletDynamicsCommon.h>


CapsuleBodyPart::CapsuleBodyPart(btScalar radius,
                                 btScalar height,
                                 btScalar mass,
                                 const btTransform& transform) {

    CapsuleBodyPart(radius, height, mass, transform, nullptr);
}

CapsuleBodyPart::CapsuleBodyPart(btScalar r,
                                 btScalar h,
                                 btScalar m,
                                 const btTransform &trans,
                                 Actuator* actuator) {
    this->actuator = actuator;
    
    btVector3 inertia(0, 0, 0);
    btQuaternion rotation(0, 0, 0, 1);
    
    btCollisionShape* capsule = new btCapsuleShape(r, h);
    btDefaultMotionState* motionState = new btDefaultMotionState(trans);
    
    capsule->calculateLocalInertia(m, inertia);
    btRigidBody::btRigidBodyConstructionInfo capsuleCI(m, motionState, capsule, inertia);
    
    capsuleCI.m_additionalDamping = true;
    
    body = new btRigidBody(capsuleCI);
    
    body->setDamping(LINEAR_DAMPING, ANGULAR_DAMPING);
    //body->setDeactivationTime(DEACTIVATION_TIME);
    //body->setSleepingThresholds(LINEAR_SLEEPING_THRESHOLD, ANGULAR_SLEEPING_THRESHOLD);

}
