#include "Body.h"
#include <BulletDynamics/btBulletDynamicsCommon.h>


Body::Body(btDynamicsWorld* world) {
	this->world = world;
}

Body::~Body() {
    
    for (btTypedConstraint* constraint : constraints) {
        world->removeConstraint(constraint);
        delete constraint;
    }
    for (BodyGroup* group : bodyGroups) {
		delete group;
	}
}