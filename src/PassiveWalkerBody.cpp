#include "PassiveWalkerBody.h"
#include "BodyGroup.h"
#include "ArmBodyGroup.h"
#include "LegBodyGroup.h"
#include "TorsoBodyGroup.h"


PassiveWalkerBody::PassiveWalkerBody(btDynamicsWorld* world) : Body::Body(world) {
    BodyGroup* left_arm = new ArmBodyGroup(world,
                                           PassiveWalkerBody::MULTIPLIER,
                                           btVector3(0, 10, 0));
    BodyGroup* right_arm = new ArmBodyGroup(world,
                                           PassiveWalkerBody::MULTIPLIER,
                                           btVector3(0, 10, 0));
    BodyGroup* left_leg = new LegBodyGroup(world,
                                           PassiveWalkerBody::MULTIPLIER,
                                           btVector3(0, 11, 0));
    BodyGroup* right_leg = new LegBodyGroup(world,
                                            PassiveWalkerBody::MULTIPLIER,
                                            btVector3(0, 11, 0));
    BodyGroup* torso = new TorsoBodyGroup(world,
                                          PassiveWalkerBody::MULTIPLIER,
                                          btVector3(0, 12, 0));
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
        generatePartsJoint(left_arm->getJointPart(),
                           torso_bg->getLeftShoulderPart(),
                           btVector3(0, 0, 0),
                           btVector3(0, 0, 0),
                           PassiveWalkerBody::MULTIPLIER);
    
    btTypedConstraint* rightShoulder =
        generatePartsJoint(right_arm->getJointPart(),
                           torso_bg->getRightShoulderPart(),
                           btVector3(0, 0, 0),
                           btVector3(0, 0, 0),
                           PassiveWalkerBody::MULTIPLIER);
    
    btTypedConstraint* leftHip =
        generatePartsJoint(left_leg->getJointPart(),
                           torso_bg->getLeftHipPart(),
                           btVector3(0, 0, 0),
                           btVector3(0, 0, 0),
                           PassiveWalkerBody::MULTIPLIER);

    btTypedConstraint* rightHip =
        generatePartsJoint(right_leg->getJointPart(),
                           torso_bg->getRightHipPart(),
                           btVector3(0, 0, 0),
                           btVector3(0, 0, 0),
                           PassiveWalkerBody::MULTIPLIER);
    
    constraints.push_back(leftShoulder);
    constraints.push_back(rightShoulder);
    constraints.push_back(leftHip);
    constraints.push_back(rightHip);
    
    world->addConstraint(leftShoulder);
    world->addConstraint(rightShoulder);
    world->addConstraint(leftHip);
    world->addConstraint(rightHip);
    
}
