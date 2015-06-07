#include "ArmBodyGroup.h"
#include "CapsuleBodyPart.h"

ArmBodyGroup::ArmBodyGroup(float multiplier, const btVector3& positionOffset) {
	double lowerArmRadius = 0.04, lowerArmHeight = 0.25, lowerArmMass = 1;
	double upperArmRadius = 0.05, upperArmHeight = 0.33, upperArmMass = 1;

	CapsuleBodyPart lowerArm(
		btScalar(multiplier * lowerArmRadius),
		btScalar(multiplier * lowerArmHeight),
		btScalar(lowerArmMass),
		positionOffset
	);
	CapsuleBodyPart upperArm(
		btScalar(multiplier * upperArmRadius),
		btScalar(multiplier * upperArmHeight),
		btScalar(upperArmMass),
		positionOffset
	);

	bodyParts.push_back(&lowerArm);
	bodyParts.push_back(&upperArm);
}

void ArmBodyGroup::initBodyGroup(btDynamicsWorld* world) {
	for (BodyPart* part : bodyParts) {
		world->addRigidBody(part->getRigidBody());
	}
}
