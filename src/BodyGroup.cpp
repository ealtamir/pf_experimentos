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


btGeneric6DofConstraint*
BodyGroup::create6DoFConstraint(BodyPart* p1,
                     BodyPart* p2,
                     const btVector3 &offset1,
                     const btVector3 &offset2,
                     const btVector3 &angularUpperLimit,
                     double multiplier) {
    btGeneric6DofConstraint* joint6DOF;
    btTransform p1Trans, p2Trans;
    bool useLinearReferenceFrameA = true;
    
    p1Trans.setIdentity();
    p2Trans.setIdentity();

    p1Trans.setOrigin(offset1);
    p2Trans.setOrigin(offset2);
    
    joint6DOF = new btGeneric6DofConstraint(*p1->getRigidBody(),
                                            *p2->getRigidBody(),
                                            p1Trans,
                                            p2Trans,
                                            useLinearReferenceFrameA
                                            );
    
#ifdef RIGID
    joint6DOF->setAngularLowerLimit(btVector3(-SIMD_EPSILON,-SIMD_EPSILON,-SIMD_EPSILON));
    joint6DOF->setAngularUpperLimit(btVector3(SIMD_EPSILON,SIMD_EPSILON,SIMD_EPSILON));
#else
    joint6DOF->setAngularLowerLimit(btVector3(-SIMD_EPSILON,-SIMD_EPSILON,-SIMD_EPSILON));
    joint6DOF->setAngularUpperLimit(angularUpperLimit);
#endif
    
    return joint6DOF;
}


btGeneric6DofConstraint*
BodyGroup::genericPartJoin(BodyPart *upperPart,
                           BodyPart *lowerPart,
                           const btVector3 upperOffset,
                           const btVector3 lowerOffset,
                           double multiplier) {
    
    btVector3 angularUpperLimit(SIMD_PI * 0.7f, SIMD_EPSILON, SIMD_EPSILON);
    return create6DoFConstraint(upperPart, lowerPart, upperOffset, lowerOffset, angularUpperLimit, multiplier);
}

BodyPart*
BodyGroup::generateStandardPart(const double r,
                                const double h,
                                const double m,
                                const btVector3 &positionOffset) {
    return new CapsuleBodyPart(btScalar(r), btScalar(h),
                               btScalar(m), positionOffset);
}



