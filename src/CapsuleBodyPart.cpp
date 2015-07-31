#include "CapsuleBodyPart.h"
#include <BulletDynamics/btBulletDynamicsCommon.h>


CapsuleBodyPart::CapsuleBodyPart(btScalar radius, btScalar height, btScalar mass,
		const btTransform transform) {
	btVector3 inertia(0, 0, 0);
	btQuaternion rotation(0, 0, 0, 1);

	btCollisionShape* capsule = new btCapsuleShape(radius, height);
	btDefaultMotionState* motionState = new btDefaultMotionState(transform);

	capsule->calculateLocalInertia(mass, inertia);
	btRigidBody::btRigidBodyConstructionInfo capsuleCI(mass, motionState, capsule, inertia);

    capsuleCI.m_additionalDamping = true;
    
	body = new btRigidBody(capsuleCI);
    
    body->setDamping(LINEAR_DAMPING, ANGULAR_DAMPING);
    body->setDeactivationTime(DEACTIVATION_TIME);
    body->setSleepingThresholds(LINEAR_SLEEPING_THRESHOLD, ANGULAR_SLEEPING_THRESHOLD);
}
