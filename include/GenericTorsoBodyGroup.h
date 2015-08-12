//
//  GenericTorsoBodyGroup.h
//  proyecto_pf
//
//  Created by Enzo Altamiranda G on 11.08.15.
//  Copyright (c) 2015 Enzo Altamiranda G. All rights reserved.
//

#ifndef __proyecto_pf__GenericTorsoBodyGroup__
#define __proyecto_pf__GenericTorsoBodyGroup__

#include <stdio.h>
#include "TorsoBodyGroup.h"

class GenericTorsoBodyGroup : public TorsoBodyGroup {
    
public:
    GenericTorsoBodyGroup(btDynamicsWorld* world,
                          BodyParameters &params,
                          const btVector3 positionAdjust);
    
    BodyPart* getLeftShoulderPart() { throw std::logic_error("Derived class doens't implement this method."); }
    BodyPart* getRightShoulderPart() { throw std::logic_error("Derived class doens't implement this method."); }
    BodyPart* getLeftHipPart() { return bodyParts[0]; }
    BodyPart* getRightHipPart() { return bodyParts[0]; }
};

#endif /* defined(__proyecto_pf__GenericTorsoBodyGroup__) */
