#include <CapsuleBodyPart>


CapsuleBodyPart::CapsuleBodyPart(btScalar radius, btScalar height, btScalar mass) {
	btVector3 origin(0, 50, 0);
	btVector3 inertia(0, 0, 0);
	btQuaternion rotation(0, 0, 0, 1);

	btTransform transform(rotation, origin);
	btCollisionShape* capsule = new btCapsuleShape(radius, height);
	btDefaultMotionState* motionState = new btDefaultMotionState(rotation, origin);

	capsule->calculateLocalInertia(mass, inertia);
	btRigidBody::btRigidBodyConstructionInfo capsuleCI(mass, motionState, capsule, inertia);

	body = new btRigidBody(capsuleCI);
}

CapsuleBodyPart::~CapsuleBodyPart() {
	delete body->getMotionState();
	delete body;
}
