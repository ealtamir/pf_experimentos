#ifndef BODYGROUP_H_INCLUDED
#define BODYGROUP_H_INCLUDED

#include <vector>
#include <BulletDynamics/btBulletDynamicsCommon.h>
#include "BodyPart.h"

class BodyGroup {

public:
    BodyGroup(btDynamicsWorld* world) : world(world) {};
    virtual ~BodyGroup();
	virtual void initBodyGroup();

protected:
	std::vector<BodyPart*> bodyParts;
    std::vector<btTypedConstraint*> constraints;
    
    btDynamicsWorld* world;

	void addRigidBodiesToWorld();
    
    btGeneric6DofConstraint*
    create6DoFConstraint(BodyPart* p1,
                         BodyPart* p2,
                         const btVector3 &offset1,
                         const btVector3 &offset2,
                         const btVector3 &angularUpperLimit,
                         double multiplier);
    
};
#endif
