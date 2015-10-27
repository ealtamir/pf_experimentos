#include "CapsuleBodyPart.h"
#include <BulletDynamics/btBulletDynamicsCommon.h>

btCompoundShape* shiftTransformCenterOfmass(btCompoundShape* boxCompound,btScalar mass,btTransform& shift)
;

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
        localTrans.setOrigin(centerofMass);
        compound->addChildShape(localTrans,capsule);
    
    
    
    btTransform shift;
    shift.setIdentity();
    btCompoundShape* newBoxCompound = shiftTransformCenterOfmass(compound,m,shift);
    newBoxCompound->calculateLocalInertia(m,inertia);
    //btDefaultMotionState* motionState = new btDefaultMotionState(trans*shift);
    //btRigidBody::btRigidBodyConstructionInfo rbInfo(m,motionState,newBoxCompound,inertia);
    
    btDefaultMotionState* motionState = new btDefaultMotionState(trans);
    
    //capsule->calculateLocalInertia(m, inertia);
    btRigidBody::btRigidBodyConstructionInfo capsuleCI(m, motionState, newBoxCompound, inertia);
    
    capsuleCI.m_additionalDamping = true;
    
    body = new btRigidBody(capsuleCI);
    
    body->setDamping(LINEAR_DAMPING, ANGULAR_DAMPING);
    body->setDeactivationTime(DEACTIVATION_TIME);
    body->setSleepingThresholds(LINEAR_SLEEPING_THRESHOLD, ANGULAR_SLEEPING_THRESHOLD);
    
}

btCompoundShape* shiftTransformCenterOfmass(btCompoundShape* boxCompound,btScalar mass,btTransform& shift)
{
    btTransform principal;
    btVector3 principalInertia;
    btScalar* masses = new btScalar[boxCompound->getNumChildShapes()];
    for (int j=0;j<boxCompound->getNumChildShapes();j++)
    {
        //evenly distribute mass
        masses[j]=mass/boxCompound->getNumChildShapes();
    }
    
    boxCompound->calculatePrincipalAxisTransform(masses,principal,principalInertia);
    
    ///creation is faster using a new compound to store the shifted children
    btCompoundShape* newBoxCompound = new btCompoundShape();
    for (int i=0;i<boxCompound->getNumChildShapes();i++)
    {
        btTransform newChildTransform = principal.inverse()*boxCompound->getChildTransform(i);
        ///updateChildTransform is really slow, because it re-calculates the AABB each time. todo: add option to disable this update
        newBoxCompound->addChildShape(newChildTransform,boxCompound->getChildShape(i));
    }
    
    
    shift = principal;
    return newBoxCompound;
}


