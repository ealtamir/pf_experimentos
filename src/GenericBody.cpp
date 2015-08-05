#include "GenericBody.h"
#include "BodyGroup.h"
#include "ArmBodyGroup.h"
#include "LegBodyGroup.h"
#include "TorsoBodyGroup.h"
#include "ConstraintBuilder.h"


GenericBody::GenericBody(btDynamicsWorld* world, GenericBodyParameters &params) : Body::Body(world) {

}

btTypedConstraint*
GenericBody::createLeftShoulder(BodyPart* leftArm, BodyPart* torso,
                                GenericBodyParameters &params) {
    ConstraintParams constraintParams = {
        torso,
        leftArm,
        params.leftShoulderTorsoOffset,
        params.leftShoulderLeftArmOffset,
        nullptr,
        &params.leftShoulderLeftArmEulerZYX,
        params.leftShoulderAngularLowerLimit,
        params.leftShoulderAngularUpperLimit
    };
    
    btTypedConstraint* constraint = ConstraintBuilder::create6DoFConstraint(constraintParams);
    constraints.push_back(constraint);
    world->addConstraint(constraint, true);
    return constraint;
}

btTypedConstraint*
GenericBody::createRightShoulder(BodyPart* rightArm, BodyPart* torso,
                                 GenericBodyParameters &params) {
    
    ConstraintParams constraintParams = {
        torso,
        rightArm,
        params.rightShoulderTorsoOffset,
        params.rightShoulderRightArmOffset,
        nullptr,
        &params.rightShoulderRightArmEulerZYX,
        params.rightShoulderAngularLowerLimit,
        params.rightShoulderAngularUpperLimit
    };
    
    btTypedConstraint* constraint = ConstraintBuilder::create6DoFConstraint(constraintParams);
    constraints.push_back(constraint);
    world->addConstraint(constraint, true);
    return constraint;
}

btTypedConstraint*
GenericBody::createLeftHip(BodyPart* leftHip, BodyPart* torso,
                           GenericBodyParameters &params) {

    ConstraintParams constraintParams = {
        torso,
        leftHip,
        params.leftHipTorsoOffset,
        params.leftHipOffset,
        nullptr,
        nullptr,
        params.leftHipAngularLowerLimit,
        params.leftHipAngularUpperLimit
    };
    
    btTypedConstraint* constraint = ConstraintBuilder::create6DoFConstraint(constraintParams);
    constraints.push_back(constraint);
    world->addConstraint(constraint, true);
    return constraint;
}

btTypedConstraint*
GenericBody::createRightHip(BodyPart* rightHip, BodyPart* torso,
                            GenericBodyParameters &params) {

    ConstraintParams constraintParams = {
        torso,
        rightHip,
        params.rightHipTorsoOffset,
        params.rightHipOffset,
        nullptr,
        nullptr,
        params.rightHipAngularLowerLimit,
        params.rightHipAngularUpperLimit
    };
    
    btTypedConstraint* constraint = ConstraintBuilder::create6DoFConstraint(constraintParams);
    constraints.push_back(constraint);
    world->addConstraint(constraint, true);
    return constraint;
}

BodyGroup*
GenericBody::createLeftArm(btDynamicsWorld* world,
                           GenericBodyParameters &params) {
    BodyGroup* left_arm = new ArmBodyGroup(world,
                                           params.bodyScale,
                                           leftOffset,
                                           params.bodyInitialPosition);
    bodyGroups.push_back(left_arm);
    left_arm->initBodyGroup();
    return left_arm;
}

BodyGroup*
GenericBody::createRightArm(btDynamicsWorld* world,
                            GenericBodyParameters &params) {
    BodyGroup* right_arm = new ArmBodyGroup(world,
                                            params.bodyScale,
                                            rightOffset,
                                            params.bodyInitialPosition);
    bodyGroups.push_back(right_arm);
    right_arm->initBodyGroup();
    return right_arm;
}

BodyGroup*
GenericBody::createLeftLeg(btDynamicsWorld* world,
                           GenericBodyParameters &params) {
    BodyGroup* left_leg = new LegBodyGroup(world,
                                           params.bodyScale,
                                           leftOffset,
                                           params.bodyInitialPosition);
    bodyGroups.push_back(left_leg);
    left_leg->initBodyGroup();
    return left_leg;
}

BodyGroup*
GenericBody::createRightLeg(btDynamicsWorld* world,
                            GenericBodyParameters &params) {
    BodyGroup* right_leg = new LegBodyGroup(world,
                                            params.bodyScale,
                                            rightOffset,
                                            params.bodyInitialPosition);
    bodyGroups.push_back(right_leg);
    right_leg->initBodyGroup();
    return right_leg;
}

BodyGroup*
GenericBody::createTorso(btDynamicsWorld* world,
                         GenericBodyParameters &params) {
    
    BodyGroup* torso = new TorsoBodyGroup(world,
                                          params.bodyScale,
                                          rightOffset,
                                          params.bodyInitialPosition);
    bodyGroups.push_back(torso);
    torso->initBodyGroup();
    return torso;
}
