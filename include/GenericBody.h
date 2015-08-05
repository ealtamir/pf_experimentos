#ifndef GENERICBODY_H_INCLUDED
#define GENERICBODY_H_INCLUDED

#include "Body.h"
#include "GenericBodyParameters.h"
#include <BulletDynamics/btBulletDynamicsCommon.h>
#include <vector>



class GenericBody : public Body {


public:
	GenericBody(btDynamicsWorld* world, GenericBodyParameters &params);
    
private:
    const btVector3 leftOffset = btVector3(-1, 1, 1);
    const btVector3 rightOffset = btVector3(1, 1, 1);
    
protected:
    
    BodyGroup*
    createLeftArm(btDynamicsWorld* world, GenericBodyParameters &params);
    
    BodyGroup*
    createRightArm(btDynamicsWorld* world, GenericBodyParameters &params);
    
    BodyGroup*
    createLeftLeg(btDynamicsWorld* world, GenericBodyParameters &params);
    
    BodyGroup*
    createRightLeg(btDynamicsWorld* world, GenericBodyParameters &params);
    
    BodyGroup*
    createTorso(btDynamicsWorld* world, GenericBodyParameters &params);
    
    btTypedConstraint*
    createLeftShoulder(BodyPart* leftArm, BodyPart* torso,
                       GenericBodyParameters &params);
    
    btTypedConstraint*
    createRightShoulder(BodyPart* rightArm, BodyPart* torso,
                        GenericBodyParameters &params);
    
    btTypedConstraint*
    createLeftHip(BodyPart* leftHip, BodyPart* torso,
                  GenericBodyParameters &params);

    btTypedConstraint*
    createRightHip(BodyPart* rightHip, BodyPart* torso,
                   GenericBodyParameters &params);

};
#endif
