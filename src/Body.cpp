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

void
Body::actuate(double t, int stage) {
    for (BodyGroup* group : bodyGroups) {
        group->actuate(t, stage);
    }
    
}


std::vector<BodyGroup*> Body::getBodyGroups(){
    return bodyGroups;
}