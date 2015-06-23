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
}
