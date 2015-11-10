#ifndef BODY_H_INCLUDED
#define BODY_H_INCLUDED

#include <vector>
#include <BulletDynamics/btBulletDynamicsCommon.h>
#include "BodyGroup.h"
#include "ConstraintBuilder.h"
#include "BodyParameters.h"


class Body : public ConstraintBuilder {

public:
	Body(btDynamicsWorld* world);
	virtual ~Body();
    
    void actuate(double t, int stage);

    std::vector<BodyGroup*> getBodyGroups();

    
    double getHeight();
    double getLeftFootHeight();
    double getRightFootHeight();
    btVector3 getPosition();
    btVector3 getVelocity();
    double getAngleInclination();
    void cicleQuantity();
    int getCycleQuantity();
    double* getAnglesLegs();

protected:
    int cicleQty = -1;
    double last_angle = 0;
    
    btVector3 previous = btVector3(0,0,1);
    
    std::vector<btTypedConstraint*> constraints;
    
    std::vector<BodyGroup*> bodyGroups;
    
	btDynamicsWorld* world;
    
    const btVector3 leftOffset = btVector3(-1, 1, 1);
    const btVector3 rightOffset = btVector3(1, 1, 1);
    
    BodyGroup*
    createLeftArm(btDynamicsWorld* world, BodyParameters &params);
    
    BodyGroup*
    createRightArm(btDynamicsWorld* world, BodyParameters &params);
    
    BodyGroup*
    createLeftLeg(btDynamicsWorld* world, BodyParameters &params);
    
    BodyGroup*
    createRightLeg(btDynamicsWorld* world, BodyParameters &params);
    
    BodyGroup*
    createTorso(btDynamicsWorld* world, BodyParameters &params);
    
    btTypedConstraint*
    createLeftShoulder(BodyPart* leftArm, BodyPart* torso,
                       BodyParameters &params);
    
    btTypedConstraint*
    createRightShoulder(BodyPart* rightArm, BodyPart* torso,
                        BodyParameters &params);
    
    btTypedConstraint*
    createLeftHip(BodyPart* leftHip, BodyPart* torso,
                  BodyParameters &params);
    
    btTypedConstraint*
    createRightHip(BodyPart* rightHip, BodyPart* torso,
                   BodyParameters &params);
};

#endif
