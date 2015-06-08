#include "Body.h"

Body::Body(btDynamicsWorld* world) {
	this->world = world;
}

Body::~Body() {
	for (BodyGroup* group : bodyGroups) {
		delete group;
	}
}
