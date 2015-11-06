#include "CapsuleBodyPart.h"
#include <BulletDynamics/btBulletDynamicsCommon.h>

#define SHIFT_TRANSFORM 1
#define CHANGE_COMPOUND_INPLACE 1
#define USE_RECURSIVE_COMPOUND 0

btCompoundShape* shiftTransform2(btCompoundShape* boxCompound,btScalar mass,btTransform& shift);

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
    
    
    btCollisionShape* capsule = new btCapsuleShape(r, h);
    btCompoundShape* compound = new btCompoundShape();
    
    btTransform localTrans;
//    btVector3 inertia(0, 0, 0);
    
    localTrans.setIdentity();
    localTrans.setOrigin(centerofMass);
    compound->addChildShape(localTrans, capsule);
    
    btTransform shift;
    shift.setIdentity();
    compound->calculateLocalInertia(m, centerofMass);
    btDefaultMotionState* motionState = new btDefaultMotionState(trans*shift);
    btRigidBody::btRigidBodyConstructionInfo capsuleCI(m, motionState, compound, centerofMass);
    
    body = new btRigidBody(capsuleCI);
//    btTransform shift;
//    shift.setIdentity();
//    btCompoundShape* newBoxCompound = shiftTransform2(compound, m, shift);
    
//    newBoxCompound->calculateLocalInertia(m,inertia);
//    btDefaultMotionState* motionState = new btDefaultMotionState(trans*shift);
//    btRigidBody::btRigidBodyConstructionInfo capsuleCI(m, motionState, newBoxCompound, inertia);
    
//    capsuleCI.m_additionalDamping = true;
    
//    body = new btRigidBody(capsuleCI);
}

btCompoundShape* shiftTransform2(btCompoundShape* boxCompound,btScalar mass,btTransform& shift)
{
    btCompoundShape* newBoxCompound = 0;
    btTransform principal;
    btVector3 principalInertia;
    btScalar* masses = new btScalar[boxCompound->getNumChildShapes()];
    for (int j=0;j<boxCompound->getNumChildShapes();j++)
    {
        //evenly distribute mass
        masses[j]=mass/boxCompound->getNumChildShapes();
    }
    
    
    boxCompound->calculatePrincipalAxisTransform(masses,principal,principalInertia);
    
    
    ///create a new compound with world transform/center of mass properly aligned with the principal axis
    
    ///non-recursive compound shapes perform better
    
#ifdef USE_RECURSIVE_COMPOUND
    
    btCompoundShape* newCompound = new btCompoundShape();
    newCompound->addChildShape(principal.inverse(),boxCompound);
    newBoxCompound = newCompound;
    //m_collisionShapes.push_back(newCompound);
    
    //btDefaultMotionState* myMotionState = new btDefaultMotionState(startTransform);
    //btRigidBody::btRigidBodyConstructionInfo rbInfo(mass,myMotionState,newCompound,principalInertia);
    
#else
#ifdef CHANGE_COMPOUND_INPLACE
    newBoxCompound = boxCompound;
    for (int i=0;i<boxCompound->getNumChildShapes();i++)
    {
        btTransform newChildTransform = principal.inverse()*boxCompound->getChildTransform(i);
        ///updateChildTransform is really slow, because it re-calculates the AABB each time. todo: add option to disable this update
        boxCompound->updateChildTransform(i,newChildTransform);
    }
    bool isDynamic = (mass != 0.f);
    btVector3 localInertia(0,0,0);
    if (isDynamic)
        boxCompound->calculateLocalInertia(mass,localInertia);
    
#else
    ///creation is faster using a new compound to store the shifted children
    newBoxCompound = new btCompoundShape();
    for (int i=0;i<boxCompound->getNumChildShapes();i++)
    {
        btTransform newChildTransform = principal.inverse()*boxCompound->getChildTransform(i);
        ///updateChildTransform is really slow, because it re-calculates the AABB each time. todo: add option to disable this update
        newBoxCompound->addChildShape(newChildTransform,boxCompound->getChildShape(i));
    }
    
    
    
#endif
    
#endif//USE_RECURSIVE_COMPOUND
    
    shift = principal;
    return newBoxCompound;
    
}


