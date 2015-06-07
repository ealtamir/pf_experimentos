#ifndef PASSIVEWALKERBODY_H_INCLUDED
#define PASSIVEWALKERBODY_H_INCLUDED

#include "Body.h"
#include "BodyGroup.h"
#include <BulletDynamics/btBulletDynamicsCommon.h>
#include <vector>

class PassiveWalkerBody : public Body {

public:
	PassiveWalkerBody(btDynamicsWorld* world);
	~PassiveWalkerBody();

};
#endif
