#ifndef BODYGROUP_H_INCLUDED
#define BODYGROUP_H_INCLUDED

#include <vector>
#include <BulletDynamics/btBulletDynamicsCommon.h>
#include "BodyPart.h"

class BodyGroup {

public:
	BodyGroup();
	~BodyGroup();

	virtual void initBodyGroup(btDynamicsWorld* world);

protected:
	std::vector<BodyPart*> bodyParts;

	void addRigidBodiesToWorld(btDynamicsWorld* world);

};

#endif
