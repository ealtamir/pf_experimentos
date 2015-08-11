#include "ArmBodyGroup.h"
#include "CapsuleBodyPart.h"
#include "ConstraintBuilder.h"



ArmBodyGroup::ArmBodyGroup(btDynamicsWorld* world,
                           BodyParameters &params,
                           const btVector3& posAdjust) : BodyGroup(world) {
    
    btVector3 lowerArmPos(params.L_ARM_POSITION.x() * posAdjust.x(),
                          params.L_ARM_POSITION.y() * posAdjust.y(),
                          params.L_ARM_POSITION.z() * posAdjust.z());
    btTransform lowerTrans;
    lowerTrans.setIdentity();
    lowerTrans.setOrigin(lowerArmPos);
    lowerTrans.getBasis().setEulerZYX(params.L_ARM_ORIENTATION.x(),
                                      params.L_ARM_ORIENTATION.y(),
                                      params.L_ARM_ORIENTATION.z() * posAdjust.x());
	BodyPart* lowerArm = generateStandardPart(
        params.L_ARM_RADIUS,
		params.L_ARM_HEIGHT,
		params.L_ARM_MASS,
        lowerTrans,
		params.bodyInitialPosition,
        params.rightLowerArmAct
	);

    btTransform upperTrans;
    btVector3 upperArmPos(params.U_ARM_POSITION.x() * posAdjust.x(),
                          params.U_ARM_POSITION.y() * posAdjust.y(),
                          params.U_ARM_POSITION.z() * posAdjust.z());
    upperTrans.setIdentity();
    upperTrans.setOrigin(upperArmPos);
    upperTrans.getBasis().setEulerZYX(params.U_ARM_ORIENTATION.x(),
                                      params.U_ARM_ORIENTATION.y(),
                                      params.U_ARM_ORIENTATION.z() * posAdjust.x());
    BodyPart* upperArm = generateStandardPart(
		params.U_ARM_RADIUS,
		params.U_ARM_HEIGHT,
		params.U_ARM_MASS,
        upperTrans,
		params.bodyInitialPosition,
        params.rightUpperArmAct
	);

	bodyParts.push_back(lowerArm);
	bodyParts.push_back(upperArm);
    
    btTypedConstraint* elbow = joinArmParts(upperArm, lowerArm, params);
    
    constraints.push_back(elbow);
}

btGeneric6DofConstraint*
ArmBodyGroup::joinArmParts(BodyPart* upperArm, BodyPart* lowerArm,
                           BodyParameters &params) {
    
    ConstraintParams constraintParams = {
        upperArm,
        lowerArm,
        params.elbowUpperOffset,
        params.elbowLowerOffset,
        nullptr,
        nullptr,
        params.elbowAngularLowerLimit,
        params.elbowAngularUpperLimit
    };
    
    return ConstraintBuilder::create6DoFConstraint(constraintParams);
}

BodyPart*
ArmBodyGroup::getJointPart() {
    return bodyParts[1];
}
