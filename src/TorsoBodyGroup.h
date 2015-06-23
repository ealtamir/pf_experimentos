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
#include "BodyGroup.h"

class TorsoBodyGroup : public BodyGroup {

public:
    TorsoBodyGroup(btDynamicsWorld* world,
                   double multiplier = 1.0,
                   const btVector3 positionOffset = btVector3(0, 20, 0));
protected:
    btGeneric6DofConstraint*
    joinTorsoParts(BodyPart* upperPart,
                   BodyPart* lowerPart,
                   const btVector3 upperOffset,
                   const btVector3 lowerOffset,
                   double multiplier);
    
  
    const double PELVIS_R = 0.15, PELVIS_H = 0.20, PELVIS_M = 1.0;
    const double SPINE_R = 0.15, SPINE_H = 0.28, SPINE_M = 1.0;
    const double HEAD_R = 0.10, HEAD_H = 0.05, HEAD_M = 1.0;
};

#endif /* defined(__test__TorsoBodyGroup__) */
