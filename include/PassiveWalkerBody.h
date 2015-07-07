#ifndef PASSIVEWALKERBODY_H_INCLUDED
#define PASSIVEWALKERBODY_H_INCLUDED

#include "Body.h"
#include <BulletDynamics/btBulletDynamicsCommon.h>
#include <vector>



class PassiveWalkerBody : public Body {


public:
	PassiveWalkerBody(btDynamicsWorld* world);
    
    const double MULTIPLIER = 1.0;

};
#endif