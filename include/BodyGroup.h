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
    
    void actuate(double t, int stage);
    
    std::vector<BodyPart*> getBodyParts() { return bodyParts; };
    
    static std::vector<Actuator*> null_fill;
    
protected:
	std::vector<BodyPart*> bodyParts;
    std::vector<btTypedConstraint*> constraints;
    
    btDynamicsWorld* world;

	void addRigidBodiesToWorld();
    
    BodyPart*
    generateStandardPart(const double r,
                         const double h,
                         const double m,
                         const btVector3& position,
                         const btVector3& positionOffset,
                         btVector3 centerOfMass,
                         std::vector<Actuator*> actuator = null_fill );
    
    BodyPart*
    generateStandardPart(const double r,
                         const double h,
                         const double m,
                         const btTransform adjust,
                         const btVector3 &positionOffset,
                         btVector3 centerOfMass,
                         std::vector<Actuator*> actuator = null_fill);
    
    BodyPart*
    generateFoot(const double m,
                 const btTransform adjust,
                 const btVector3 &positionOffset);
};
#endif
