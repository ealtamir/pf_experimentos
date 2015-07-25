#include "BodyGroup.h"
#include "CapsuleBodyPart.h"


BodyGroup::~BodyGroup() {
    for (btTypedConstraint* constraint : constraints) {
        world->removeConstraint(constraint);
        delete constraint;
    }
    constraints.clear();
    
    for (BodyPart* part : bodyParts) {
        world->removeRigidBody(part->getRigidBody());
        delete part;
    }
    bodyParts.clear();
}

void BodyGroup::initBodyGroup() {
	addRigidBodiesToWorld();
}

void BodyGroup::addRigidBodiesToWorld() {
	for (BodyPart* part : bodyParts) {
		world->addRigidBody(part->getRigidBody());
	}
    for (btTypedConstraint* constraint : constraints) {
        world->addConstraint(constraint);
    }
}

BodyPart*
BodyGroup::generateStandardPart(const double r,
                                const double h,
                                const double m,
                                const btVector3 &positionOffset) {
    return new CapsuleBodyPart(btScalar(r), btScalar(h),
                               btScalar(m), positionOffset);
}




