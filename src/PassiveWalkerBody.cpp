#include "PassiveWalkerBody.h"
#include "ArmBodyGroup.h"


PassiveWalkerBody::PassiveWalkerBody(btDynamicsWorld* world) : Body(world) {
	BodyGroup* arm = new ArmBodyGroup();
	bodyGroups.push_back(arm);

	arm->initBodyGroup(world);
}

PassiveWalkerBody::~PassiveWalkerBody() {
	for (BodyGroup* group : bodyGroups) {
		delete group;
	}
}
