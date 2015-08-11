//
//  TorsoBodyGroup.h
//  test
//
//  Created by Enzo Altamiranda G on 23.06.15.
//  Copyright (c) 2015 Enzo Altamiranda G. All rights reserved.
//

#ifndef __test__TorsoBodyGroup__
#define __test__TorsoBodyGroup__

#include <stdio.h>
#include <exception>
#include "BodyGroup.h"
#include "BodyParameters.h"

class TorsoBodyGroup : public BodyGroup {

public:
    TorsoBodyGroup(btDynamicsWorld* world,
                   BodyParameters &params,
                   const btVector3 positionAdjust = btVector3(1, 1, 1));
    
    BodyPart* getJointPart() { exit(1); }
    
    virtual BodyPart* getLeftShoulderPart() { return bodyParts[1]; }
    virtual BodyPart* getRightShoulderPart() { return bodyParts[1]; }
    virtual BodyPart* getLeftHipPart() { return bodyParts[2]; }
    virtual BodyPart* getRightHipPart() { return bodyParts[2]; }

    
protected:
    btGeneric6DofConstraint*
    createHeadSpineConstraint(BodyPart* head,
                              BodyPart* spine,
                              BodyParameters &params);
    
    btGeneric6DofConstraint*
    createSpinePelvisConstraint(BodyPart* spine,
                                BodyPart* pelvis,
                                BodyParameters &params);
    
    BodyPart*
    createHead(BodyParameters &params, const btVector3 positionAdjust);
    
    BodyPart*
    createSpine(BodyParameters &params, const btVector3 positionAdjust);

    BodyPart*
    createPelvis(BodyParameters &params, const btVector3 positionAdjust);
    
};

#endif /* defined(__test__TorsoBodyGroup__) */
