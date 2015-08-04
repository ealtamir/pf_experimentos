#ifndef GENERICBODY_H_INCLUDED
#define GENERICBODY_H_INCLUDED

#include "Body.h"
#include <BulletDynamics/btBulletDynamicsCommon.h>
#include <vector>



class GenericBody : public Body {


public:
	GenericBody(btDynamicsWorld* world);
    
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
