#ifndef BODY_H_INCLUDED
#define BODY_H_INCLUDED

#include <vector>
#include <BulletDynamics/btBulletDynamicsCommon.h>
#include "BodyGroup.h"

class Body {

public:
	Body(btDynamicsWorld* world);
	virtual ~Body();

protected:
	std::vector<BodyGroup*> bodyGroups;
    std::vector<btTypedConstraint*> constraints;
    
	btDynamicsWorld* world;

};

#endif
