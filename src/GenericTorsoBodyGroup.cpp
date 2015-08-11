//
//  GenericTorsoBodyGroup.cpp
//  proyecto_pf
//
//  Created by Enzo Altamiranda G on 11.08.15.
//  Copyright (c) 2015 Enzo Altamiranda G. All rights reserved.
//

#include "GenericTorsoBodyGroup.h"




GenericTorsoBodyGroup::GenericTorsoBodyGroup(btDynamicsWorld* world,
                                              BodyParameters &params,
                                              const btVector3 positionAdjust) : TorsoBodyGroup(world, params, positionAdjust) {
    createPelvis(params, positionAdjust);
}