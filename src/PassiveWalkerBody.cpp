#include "PassiveWalkerBody.h"
#include "BodyGroup.h"
#include "ArmBodyGroup.h"
#include "LegBodyGroup.h"
#include "TorsoBodyGroup.h"
#include "ConstraintBuilder.h"


PassiveWalkerBody::PassiveWalkerBody(btDynamicsWorld* world) : Body::Body(world) {
    
    btVector3 offset(0, 3, 0);
    btVector3 leftAdjust(-1, 1, 1);
    btVector3 rightAdjust(1, 1, 1);
    
    BodyGroup* left_arm = new ArmBodyGroup(world,
                                           PassiveWalkerBody::MULTIPLIER,
                                           leftAdjust,
                                           offset);
    BodyGroup* right_arm = new ArmBodyGroup(world,
                                            PassiveWalkerBody::MULTIPLIER,
                                            rightAdjust,
                                            offset);
    BodyGroup* left_leg = new LegBodyGroup(world,
                                           PassiveWalkerBody::MULTIPLIER,
                                           leftAdjust,
                                           offset);
    BodyGroup* right_leg = new LegBodyGroup(world,
                                            PassiveWalkerBody::MULTIPLIER,
                                            rightAdjust,
                                            offset);
    BodyGroup* torso = new TorsoBodyGroup(world,
                                          PassiveWalkerBody::MULTIPLIER,
                                          rightAdjust,
                                          offset);
	bodyGroups.push_back(left_arm);
    bodyGroups.push_back(left_leg);
    bodyGroups.push_back(right_arm);
    bodyGroups.push_back(right_leg);
    bodyGroups.push_back(torso);

	left_arm->initBodyGroup();
    left_leg->initBodyGroup();
    right_arm->initBodyGroup();
    right_leg->initBodyGroup();
    torso->initBodyGroup();
    
    TorsoBodyGroup* torso_bg = dynamic_cast<TorsoBodyGroup*>(torso);
    
    btTypedConstraint* leftShoulder =
        createLeftShoulder(left_arm->getJointPart(),
                           torso_bg->getLeftShoulderPart(),
                           PassiveWalkerBody::MULTIPLIER);
    
    btTypedConstraint* rightShoulder =
        createRightShoulder(right_arm->getJointPart(),
                           torso_bg->getRightShoulderPart(),
                           PassiveWalkerBody::MULTIPLIER);
    
    btTypedConstraint* leftHip =
        createLeftHip(left_leg->getJointPart(),
                      torso_bg->getLeftHipPart(),
                      PassiveWalkerBody::MULTIPLIER);

    btTypedConstraint* rightHip =
        createRightHip(right_leg->getJointPart(),
                       torso_bg->getRightHipPart(),
                       PassiveWalkerBody::MULTIPLIER);
    
    constraints.push_back(leftShoulder);
    constraints.push_back(rightShoulder);
    constraints.push_back(leftHip);
    constraints.push_back(rightHip);
    
    world->addConstraint(leftShoulder, true);
    world->addConstraint(rightShoulder, true);
    world->addConstraint(leftHip, true);
    world->addConstraint(rightHip, true);
    
}

btTypedConstraint*
PassiveWalkerBody::createLeftShoulder(BodyPart* leftArm, BodyPart* torso, const double multiplier) {
    btVector3 torsoOffset(btScalar(-0.2 * multiplier),
                            btScalar(0.15 * multiplier),
                            btScalar(0.));
    
    btVector3 leftArmOffset(btScalar(0.),
                            btScalar(-0.18 * multiplier),
                            btScalar(0.));
    
    btVector3 leftArmEulerZYX(SIMD_HALF_PI, 0, -SIMD_HALF_PI);
    
    btVector3 angularLowerLimit(-SIMD_PI * 0.8, -SIMD_EPSILON, -SIMD_PI * 0.5);
    btVector3 angularUpperLimit(SIMD_PI * 0.8, SIMD_EPSILON, SIMD_PI * 0.5);
    
    ConstraintParams params = {
        torso,
        leftArm,
        torsoOffset,
        leftArmOffset,
        nullptr,
        &leftArmEulerZYX,
        angularLowerLimit,
        angularUpperLimit
    };
    
    return ConstraintBuilder::create6DoFConstraint(params);
}

btTypedConstraint*
PassiveWalkerBody::createRightShoulder(BodyPart* rightArm, BodyPart* torso, const double multiplier) {
    btVector3 torsoOffset(btScalar(0.2 * multiplier),
                          btScalar(0.15 * multiplier),
                          btScalar(0.));
    
    btVector3 rightArmOffset(btScalar(0.),
                             btScalar(-0.18 * multiplier),
                             btScalar(0.));
    
    btVector3 rightArmEulerZYX(0, 0, SIMD_HALF_PI);
    
    btVector3 angularLowerLimit(-SIMD_PI * 0.8, -SIMD_EPSILON, -SIMD_PI * 0.5);
    btVector3 angularUpperLimit(SIMD_PI * 0.8, SIMD_EPSILON, SIMD_PI * 0.5);
    
    ConstraintParams params = {
        torso,
        rightArm,
        torsoOffset,
        rightArmOffset,
        nullptr,
        &rightArmEulerZYX,
        angularLowerLimit,
        angularUpperLimit
    };
    
    return ConstraintBuilder::create6DoFConstraint(params);
}

btTypedConstraint*
PassiveWalkerBody::createLeftHip(BodyPart* leftHip, BodyPart* torso, const double multiplier) {
    btVector3 torsoOffset(btScalar(-0.18 * multiplier),
                          btScalar(-0.10 * multiplier),
                          btScalar(0.));
    
    btVector3 leftHipOffset(btScalar(0.),
                            btScalar(0.225 * multiplier),
                            btScalar(0.));
    
    btVector3 angularUpperLimit(SIMD_HALF_PI * 0.8, SIMD_EPSILON, SIMD_HALF_PI * 0.6);
    btVector3 angularLowerLimit(-SIMD_HALF_PI * 0.5, -SIMD_EPSILON, -SIMD_HALF_PI);
    
    ConstraintParams params = {
        torso,
        leftHip,
        torsoOffset,
        leftHipOffset,
        nullptr,
        nullptr,
        angularLowerLimit,
        angularUpperLimit
    };
    
    return ConstraintBuilder::create6DoFConstraint(params);
}

btTypedConstraint*
PassiveWalkerBody::createRightHip(BodyPart* rightHip, BodyPart* torso, const double multiplier) {
    btVector3 torsoOffset(btScalar(0.18 * multiplier),
                          btScalar(-0.10 * multiplier),
                          btScalar(0.));
    
    btVector3 rightHipOffset(btScalar(0.),
                            btScalar(0.225 * multiplier),
                            btScalar(0.));
    
    btVector3 angularUpperLimit(SIMD_HALF_PI * 0.8, SIMD_EPSILON, SIMD_HALF_PI);
    btVector3 angularLowerLimit(-SIMD_HALF_PI * 0.5, -SIMD_EPSILON, -SIMD_HALF_PI * 0.6);
    
    ConstraintParams params = {
        torso,
        rightHip,
        torsoOffset,
        rightHipOffset,
        nullptr,
        nullptr,
        angularLowerLimit,
        angularUpperLimit
    };
    
    return ConstraintBuilder::create6DoFConstraint(params);
}
