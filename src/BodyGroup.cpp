#include "BodyGroup.h"
#include "CapsuleBodyPart.h"
#include "ConvexHullBodyPart.h"


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
        world->addConstraint(constraint, true);
    }
}

void
BodyGroup::actuate(double t, int stage) {
    for (BodyPart* part : bodyParts) {
        part->actuate(t, stage);
    }
}

BodyPart*
BodyGroup::generateStandardPart(const double r,
                                const double h,
                                const double m,
                                const btVector3 &position,
                                const btVector3 &positionOffset,
                                btVector3 centerOfMass,
                                Actuator* actuator) {
    btTransform offset;
    offset.setIdentity();
    offset.setOrigin(positionOffset);
    
    btTransform transPos;
    transPos.setIdentity();
    transPos.setOrigin(position);
    
    return new CapsuleBodyPart(btScalar(r), btScalar(h),
                               btScalar(m), offset * transPos, actuator, centerOfMass);
    
}

BodyPart*
BodyGroup::generateStandardPart(const double r,
                                const double h,
                                const double m,
                                const btTransform adjust,
                                const btVector3 &positionOffset,
                                btVector3 centerOfMass,
                                Actuator* actuator) {
    
    btTransform offset;
    offset.setIdentity();
    offset.setOrigin(positionOffset);
    
    return new CapsuleBodyPart(btScalar(r), btScalar(h),
                               btScalar(m), offset * adjust, actuator, centerOfMass);
    
}


BodyPart*
BodyGroup::generateFoot(const double m,
                        const btTransform adjust,
                        const btVector3 &positionOffset) {
    
    btTransform offset;
    offset.setIdentity();
    offset.setOrigin(positionOffset);    
    
    return new ConvexHullBodyPart(nullptr, btScalar(m), offset * adjust);
    
}
