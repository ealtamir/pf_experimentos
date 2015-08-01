#ifndef PASSIVEWALKERBODY_H_INCLUDED
#define PASSIVEWALKERBODY_H_INCLUDED

#include "Body.h"
#include <BulletDynamics/btBulletDynamicsCommon.h>
#include <vector>



class PassiveWalkerBody : public Body {


public:
	PassiveWalkerBody(btDynamicsWorld* world);
    
    const double MULTIPLIER = 1;
    
protected:
    
    btTypedConstraint*
    createLeftShoulder(BodyPart* leftArm, BodyPart* torso, const double multiplier);
    
    btTypedConstraint*
    createRightShoulder(BodyPart* rightArm, BodyPart* torso, const double multiplier);
    
    btTypedConstraint*
    createLeftHip(BodyPart* leftHip, BodyPart* torso, const double multiplier);

    btTypedConstraint*
    createRightHip(BodyPart* rightHip, BodyPart* torso, const double multiplier);

};
#endif
