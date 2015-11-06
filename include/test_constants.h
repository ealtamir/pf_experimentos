//
//  test_constants.h
//  pf2
//
//  Created by Enzo Altamiranda G on 22.04.15.
//  Copyright (c) 2015 Enzo Altamiranda G. All rights reserved.
//

#ifndef pf2_test_constants_h
#define pf2_test_constants_h

const btScalar BALL_RESTITUTION = btScalar(8);
const btScalar BALL_FRICTION = btScalar(1);

const btVector3 BALL_VELOCITY = btVector3(0, -.5, 0);
const btVector3 BALL_ORIGIN = btVector3(0, 4, 0);

const btVector3 GRAVITY = btVector3(0, 0, 0);

const btScalar GROUND_FRICTION = btScalar(1);
const btScalar GROUND_RESTITUTION = btScalar(1);

const btScalar WALL_RESTITUTION = btScalar(1);
const btScalar WALL_FRICTION = btScalar(1);

const btScalar BOX_FRICTION = btScalar(.75);
const btVector3 BOX_INITIAL_VEL = btVector3(1, 0, 0);

const btScalar SIM_STEP(1 / 100.);

#endif
