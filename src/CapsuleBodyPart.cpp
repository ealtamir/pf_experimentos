#include "CapsuleBodyPart.h"
#include <BulletDynamics/btBulletDynamicsCommon.h>


CapsuleBodyPart::CapsuleBodyPart(btScalar radius, btScalar height, btScalar mass,
		const btVector3 origin) {
	btVector3 inertia(0, 0, 0);
	btQuaternion rotation(0, 0, 0, 1);

	btTransform transform(rotation, origin);
	btCollisionShape* capsule = new btCapsuleShape(radius, height);
	btDefaultMotionState* motionState = new btDefaultMotionState(transform);

	capsule->calculateLocalInertia(mass, inertia);
	btRigidBody::btRigidBodyConstructionInfo capsuleCI(mass, motionState, capsule, inertia);

	body = new btRigidBody(capsuleCI);
}
