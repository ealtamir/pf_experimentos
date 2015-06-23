#include "ArmBodyGroup.h"
#include "CapsuleBodyPart.h"



ArmBodyGroup::ArmBodyGroup(btDynamicsWorld* world,
                           const double multiplier,
                           const btVector3& positionOffset) : BodyGroup(world) {
    
	BodyPart* lowerArm = generateStandardPart(
        multiplier * LOWER_ARM_R,
		multiplier * LOWER_ARM_H,
		LOWER_ARM_M,
		positionOffset
	);
	BodyPart* upperArm = generateStandardPart(
		multiplier * UPPER_ARM_R,
		multiplier * UPPER_ARM_H,
		UPPER_ARM_M,
		positionOffset
	);

	bodyParts.push_back(lowerArm);
	bodyParts.push_back(upperArm);
    
    btTypedConstraint* elbow = joinArmParts(upperArm, lowerArm, multiplier);
    
    constraints.push_back(elbow);
}


btGeneric6DofConstraint*
ArmBodyGroup::joinArmParts(BodyPart* upperArm, BodyPart* lowerArm,
                           double multiplier) {
    btVector3 upperOrigin(0, 0.18 * multiplier, 0);
    btVector3 lowerOrigin(0, -0.14 * multiplier, 0);

    // Algo que usa Bullet
    btVector3 angularUpperLimit(SIMD_PI * 0.7f, SIMD_EPSILON, SIMD_EPSILON);
    
    return create6DoFConstraint(upperArm, lowerArm, upperOrigin, lowerOrigin, angularUpperLimit, multiplier);
}
