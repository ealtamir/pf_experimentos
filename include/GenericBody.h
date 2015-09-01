#ifndef GENERICBODY_H_INCLUDED
#define GENERICBODY_H_INCLUDED

#include "Body.h"
#include "BodyParameters.h"
#include <BulletDynamics/btBulletDynamicsCommon.h>
#include <vector>



class GenericBody : public Body {


public:
	GenericBody(btDynamicsWorld* world, BodyParameters &params);
    
protected:
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
