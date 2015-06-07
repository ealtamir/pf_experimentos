#ifndef LEFTARMBODYGROUP_H_INCLUDED
#define LEFTARMBODYGROUP_H_INCLUDED

#include "BodyGroup.h"

class ArmBodyGroup : public BodyGroup {

public:
	ArmBodyGroup(float scale=1.0, const btVector3& positionOffset = btVector3(0, 0, 0));
	~ArmBodyGroup();

	void initBodyGroup(btDynamicsWorld* world);

};

#endif
