#ifndef LEFTARMBODYGROUP_H_INCLUDED
#define LEFTARMBODYGROUP_H_INCLUDED

#include "BodyGroup.h"

class ArmBodyGroup : public BodyGroup {

public:
	ArmBodyGroup(float multiplier = 1.0,
			const btVector3& positionOffset = btVector3(0, 20, 0));
	~ArmBodyGroup();

	virtual void initBodyGroup(btDynamicsWorld* world);


};

#endif
