#include "GenericBody.h"
#include "BodyGroup.h"
#include "ArmBodyGroup.h"
#include "LegBodyGroup.h"
#include "TorsoBodyGroup.h"
#include "ConstraintBuilder.h"


GenericBody::GenericBody(btDynamicsWorld* world, BodyParameters &params) : Body::Body(world) {
    // Contains nothing
}

btTypedConstraint*
GenericBody::createLeftShoulder(BodyPart* leftArm, BodyPart* torso,
                                BodyParameters &params) {
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
                                 BodyParameters &params) {
    
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
                           BodyParameters &params) {

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
                            BodyParameters &params) {

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
    
//    btTransform torsoTrans, hipTrans;
//    torsoTrans.setIdentity(); torsoTrans.setOrigin(params.rightHipTorsoOffset);
//    hipTrans.setIdentity(); torsoTrans.setOrigin(params.rightHipOffset);
//    
//
//    btTypedConstraint* constraint = new btConeTwistConstraint(*torso->getRigidBody(),
//                                                              *rightHip->getRigidBody(),
//                                                              torsoTrans,
//                                                              hipTrans);
//    dynamic_cast<btConeTwistConstraint*>(constraint)->setLimit(M_PI_4, M_PI_4, 0, 0.1);

//    constraint->setDbgDrawSize(btScalar(5.f));
//    
//    btTransform localA, localB;
//    localA.setIdentity(); localB.setIdentity();
////    localA.getBasis().setEulerZYX(0,0,M_PI_4); localA.setOrigin(btVector3(btScalar(0.18), btScalar(-0.10), btScalar(0.)));
////    localB.getBasis().setEulerZYX(0,0,M_PI_4); localB.setOrigin(btVector3(btScalar(0.), btScalar(0.225), btScalar(0.)));
//
//    localA.setIdentity(); localB.setIdentity();
////    localA.getBasis().setEulerZYX(0,0,M_PI_4); localA.setOrigin(btVector3(btScalar(0.18), btScalar(-0.10), btScalar(0.)));
////    localB.getBasis().setEulerZYX(0,0,M_PI_4); localB.setOrigin(btVector3(btScalar(0.0), btScalar(0.10), btScalar(0.)));
//    btTypedConstraint* constraint = new btConeTwistConstraint(*torso->getRigidBody(), *rightHip->getRigidBody(), localA, localB);
//    dynamic_cast<btConeTwistConstraint*>(constraint)->setLimit(M_PI_4, M_PI_4, 0);
//    constraint->setOverrideNumSolverIterations(30);

    
    constraints.push_back(constraint);
    world->addConstraint(constraint, true);
    return constraint;
}

BodyGroup*
GenericBody::createLeftArm(btDynamicsWorld* world,
                           BodyParameters &params) {
    BodyGroup* left_arm = new ArmBodyGroup(world,
                                           params,
                                           leftOffset);
    bodyGroups.push_back(left_arm);
    left_arm->initBodyGroup();
    return left_arm;
}

BodyGroup*
GenericBody::createRightArm(btDynamicsWorld* world,
                            BodyParameters &params) {
    BodyGroup* right_arm = new ArmBodyGroup(world,
                                            params,
                                            rightOffset);
    bodyGroups.push_back(right_arm);
    right_arm->initBodyGroup();
    return right_arm;
}

BodyGroup*
GenericBody::createLeftLeg(btDynamicsWorld* world,
                           BodyParameters &params) {
    BodyGroup* left_leg = new LegBodyGroup(world,
                                           params,
                                           leftOffset, true);
    bodyGroups.push_back(left_leg);
    left_leg->initBodyGroup();
    return left_leg;
}

BodyGroup*
GenericBody::createRightLeg(btDynamicsWorld* world,
                            BodyParameters &params) {
    BodyGroup* right_leg = new LegBodyGroup(world,
                                            params,
                                            rightOffset);
    bodyGroups.push_back(right_leg);
    right_leg->initBodyGroup();
    return right_leg;
}

BodyGroup*
GenericBody::createTorso(btDynamicsWorld* world,
                         BodyParameters &params) {
    
    BodyGroup* torso = new TorsoBodyGroup(world,
                                          params,
                                          rightOffset);
    bodyGroups.push_back(torso);
    torso->initBodyGroup();
    return torso;
}
