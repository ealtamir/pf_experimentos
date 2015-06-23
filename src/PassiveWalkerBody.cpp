#include "PassiveWalkerBody.h"
#include "BodyGroup.h"
#include "ArmBodyGroup.h"


PassiveWalkerBody::PassiveWalkerBody(btDynamicsWorld* world) : Body::Body(world) {
	BodyGroup* arm = new ArmBodyGroup(world, 1.0, btVector3(0, 10, 0));
	bodyGroups.push_back(arm);

	arm->initBodyGroup();
}
