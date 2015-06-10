#include "ArmBodyGroup.h"
#include "CapsuleBodyPart.h"



ArmBodyGroup::ArmBodyGroup(const double multiplier,
                           const btVector3& positionOffset) {
    
	BodyPart* lowerArm = generateArmPart(
		multiplier * LOWER_ARM_R,
		multiplier * LOWER_ARM_H,
		LOWER_ARM_M,
		positionOffset
	);
	BodyPart* upperArm = generateArmPart(
		multiplier * UPPER_ARM_R,
		multiplier * UPPER_ARM_H,
		UPPER_ARM_M,
		positionOffset
	);

	bodyParts.push_back(lowerArm);
	bodyParts.push_back(upperArm);
    
    btTypedConstraint* elbow = joinArmParts(lowerArm, upperArm, multiplier);
    
    constraints.push_back(elbow);
    
}



ArmBodyGroup::~ArmBodyGroup() {
	for (BodyPart* part : bodyParts) {
		delete part->getRigidBody()->getMotionState();
		delete part->getRigidBody();
	}
}



btGeneric6DofConstraint*
ArmBodyGroup::joinArmParts(BodyPart* lowerArm, BodyPart* upperArm,
                           double multiplier) {
    btGeneric6DofConstraint* joint6DOF;
    btTransform lowerTrans, upperTrans;
    bool useLinearReferenceFrameA = true;
    
    upperTrans.setIdentity();
    lowerTrans.setIdentity();
    
    btVector3 upperOrigin(0, 0.18 * multiplier, 0);
    btVector3 lowerOrigin(0, -0.14 * multiplier, 0);
    
    upperTrans.setOrigin(upperOrigin);
    lowerTrans.setOrigin(lowerOrigin);

    joint6DOF = new btGeneric6DofConstraint(*upperArm->getRigidBody(),
                                            *lowerArm->getRigidBody(),
                                            upperTrans,
                                            lowerTrans,
                                            useLinearReferenceFrameA
    );
    
    #ifdef RIGID
    joint6DOF->setAngularLowerLimit(btVector3(-SIMD_EPSILON,-SIMD_EPSILON,-SIMD_EPSILON));
    joint6DOF->setAngularUpperLimit(btVector3(SIMD_EPSILON,SIMD_EPSILON,SIMD_EPSILON));
    #else
    joint6DOF->setAngularLowerLimit(btVector3(-SIMD_EPSILON,-SIMD_EPSILON,-SIMD_EPSILON));
    joint6DOF->setAngularUpperLimit(btVector3(SIMD_PI*0.7f,SIMD_EPSILON,SIMD_EPSILON));
    #endif
    
    return joint6DOF;
}



BodyPart*
ArmBodyGroup::generateArmPart(const double r, const double h, const double m,
                const btVector3& positionOffset) {
    return new CapsuleBodyPart(btScalar(r), btScalar(h),
                               btScalar(m), positionOffset);
}
