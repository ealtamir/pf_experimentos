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
    
    virtual BodyPart* getJointPart() = 0;

protected:
	std::vector<BodyPart*> bodyParts;
    std::vector<btTypedConstraint*> constraints;
    
    btDynamicsWorld* world;

	void addRigidBodiesToWorld();
    
    btGeneric6DofConstraint*
    genericPartJoin(BodyPart *upperPart,
                    BodyPart *lowerPart,
                    const btVector3 upperOffset,
                    const btVector3 lowerOffset,
                    double multiplier);
    
    btGeneric6DofConstraint*
    create6DoFConstraint(BodyPart* p1,
                         BodyPart* p2,
                         const btVector3 &offset1,
                         const btVector3 &offset2,
                         const btVector3 &angularUpperLimit,
                         double multiplier);
    
    BodyPart*
    generateStandardPart(const double r,
                         const double h,
                         const double m,
                         const btVector3& positionOffset);
    
};
#endif
