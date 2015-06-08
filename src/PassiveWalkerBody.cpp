#include "PassiveWalkerBody.h"
#include "BodyGroup.h"
#include "ArmBodyGroup.h"


PassiveWalkerBody::PassiveWalkerBody(btDynamicsWorld* world) : Body::Body(world) {
	BodyGroup* arm = new ArmBodyGroup();
	bodyGroups.push_back(arm);

	arm->initBodyGroup(world);
}
