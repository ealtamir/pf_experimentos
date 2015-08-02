//
//  BodyParameters.h
//  test
//
//  Created by Enzo Altamiranda G on 02.08.15.
//  Copyright (c) 2015 Enzo Altamiranda G. All rights reserved.
//

#ifndef __test__BodyParameters__
#define __test__BodyParameters__

#include <stdio.h>
#include <BulletDynamics/btBulletDynamicsCommon.h>


class BodyParameters {

public:
    double bodyMultiplier = 1;
    
    btVector3 positionOffset = btVector3(0, -10, 0);
    
    // Leg body group
    // lower leg
    double L_LEG_RADIUS = 0.05;
    double L_LEG_HEIGHT = 0.37;
    double L_LEG_MASS = 1;
    btVector3 L_LEG_ORIENTATION = btVector3(0, 0, 0);
    btVector3 L_LEG_POSITION = btVector3(btScalar(0.18),
                                         btScalar(0.2),
                                         btScalar(0.0));
    
    //upper leg
    double U_LEG_RADIUS = 0.07;
    double U_LEG_HEIGHT = 0.45;
    double U_LEG_MASS = 1;
    btVector3 U_LEG_ORIENTATION = btVector3(0, 0, 0);
    btVector3 U_LEG_POSITION = btVector3(btScalar(0.18),
                                         btScalar(0.65),
                                         btScalar(0.));
    
    double FOOT_RADIUS = 0.05;
    double FOOT_HEIGHT = 0.15;
    double FOOT_MASS = 1;
    btVector3 FOOT_ORIENTATION = btVector3(SIMD_HALF_PI, 0, 0);
    btVector3 FOOT_POSITION = btVector3(btScalar(0.18),
                                        btScalar(0.2),
                                        btScalar(0.));
    
    // Arm body group
    //lower arm
    double L_ARM_RADIUS = 0.04;
    double L_ARM_HEIGHT = 0.25;
    double L_ARM_MASS = 1;
    btVector3 L_ARM_ORIENTATION = btVector3(0, 0, -SIMD_HALF_PI);
    btVector3 L_ARM_POSITION = btVector3(btScalar(0.7),
                                         btScalar(1.45),
                                         btScalar(0));
    
    //upper arm
    double U_ARM_RADIUS = 0.05;
    double U_ARM_HEIGHT = 0.33;
    double U_ARM_MASS = 1;
    btVector3 U_ARM_ORIENTATION = btVector3(0, 0, -SIMD_HALF_PI);
    btVector3 U_ARM_POSITION = btVector3(btScalar(0.35),
                                         btScalar(1.45),
                                         btScalar(0));
    
    // Torso body group
    // Pelvis
    double PELVIS_RADIUS = 0.15;
    double PELVIS_HEIGHT = 0.20;
    double PELVIS_MASS = 1.0;
    btVector3 PELVIS_ORIENTATION = btVector3(0, 0, 0);
    btVector3 PELVIS_POSITION = btVector3(btScalar(0),
                                          btScalar(1),
                                          btScalar(0));
    
    // Spine
    double SPINE_RADIUS = 0.15;
    double SPINE_HEIGHT = 0.28;
    double SPINE_MASS = 1.0;
    btVector3 SPINE_ORIENTATION = btVector3(0, 0, 0);
    btVector3 SPINE_POSITION = btVector3(btScalar(0),
                                         btScalar(1.6),
                                         btScalar(0));
    
    // HEAD
    double HEAD_RADIUS = 0.10;
    double HEAD_HEIGHT = 0.05;
    double HEAD_MASS = 1.0;
    btVector3 HEAD_ORIENTATION = btVector3(0, 0, 0);
    btVector3 HEAD_POSITION = btVector3(btScalar(0),
                                        btScalar(1.6),
                                        btScalar(0));
    
    
    
};

#endif /* defined(__test__BodyParameters__) */
