#include "BodyGroup.h"


void BodyGroup::initBodyGroup(btDynamicsWorld* world) {
	this->addRigidBodiesToWorld(world);
}

void BodyGroup::addRigidBodiesToWorld(btDynamicsWorld* world) {
	for (BodyPart* part : bodyParts) {
		world->addRigidBody(part->getRigidBody());
	}
    for (btTypedConstraint* constraint : constraints) {
        world->addConstraint(constraint);
    }
}

