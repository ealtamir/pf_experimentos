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

#define     BODY_SCALE      1

class BodyParameters {
    
public:
    
    /******************** PARTS ********************/
    
    btVector3 positionOffset = btVector3(0, -10, 0);
    
    // Leg body group
    // lower leg
    double L_LEG_RADIUS = 0.05 * BODY_SCALE;
    double L_LEG_HEIGHT = 0.37 * BODY_SCALE;
    double L_LEG_MASS = 1 * BODY_SCALE;
    btVector3 L_LEG_ORIENTATION = btVector3(0, 0, 0);
    btVector3 L_LEG_POSITION = btVector3(btScalar(0.18 * BODY_SCALE),
                                         btScalar(0.2 * BODY_SCALE),
                                         btScalar(0.0));
    
    //upper leg
    double U_LEG_RADIUS = 0.07 * BODY_SCALE;
    double U_LEG_HEIGHT = 0.45 * BODY_SCALE;
    double U_LEG_MASS = 1 * BODY_SCALE;
    btVector3 U_LEG_ORIENTATION = btVector3(0, 0, 0);
    btVector3 U_LEG_POSITION = btVector3(btScalar(0.18 * BODY_SCALE),
                                         btScalar(0.65 * BODY_SCALE),
                                         btScalar(0.));
    
    double FOOT_RADIUS = 0.05 * BODY_SCALE;
    double FOOT_HEIGHT = 0.15 * BODY_SCALE;
    double FOOT_MASS = 1 * BODY_SCALE;
    btVector3 FOOT_ORIENTATION = btVector3(SIMD_HALF_PI, 0, 0);
    btVector3 FOOT_POSITION = btVector3(btScalar(0.18 * BODY_SCALE),
                                        btScalar(0.2 * BODY_SCALE),
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
    double U_ARM_RADIUS = 0.05 * BODY_SCALE;
    double U_ARM_HEIGHT = 0.33 * BODY_SCALE;
    double U_ARM_MASS = 1 * BODY_SCALE;
    btVector3 U_ARM_ORIENTATION = btVector3(0, 0, -SIMD_HALF_PI);
    btVector3 U_ARM_POSITION = btVector3(btScalar(0.35 * BODY_SCALE),
                                         btScalar(1.45 * BODY_SCALE),
                                         btScalar(0));
    
    // Torso body group
    // Pelvis
    double PELVIS_RADIUS = 0.15 * BODY_SCALE;
    double PELVIS_HEIGHT = 0.20 * BODY_SCALE;
    double PELVIS_MASS = 1.0 * BODY_SCALE;
    btVector3 PELVIS_ORIENTATION = btVector3(0, 0, 0);
    btVector3 PELVIS_POSITION = btVector3(btScalar(0),
                                          btScalar(1 * BODY_SCALE),
                                          btScalar(0));
    
    // Spine
    double SPINE_RADIUS = 0.15 * BODY_SCALE;
    double SPINE_HEIGHT = 0.28 * BODY_SCALE;
    double SPINE_MASS = 1.0 * BODY_SCALE;
    btVector3 SPINE_ORIENTATION = btVector3(0, 0, 0);
    btVector3 SPINE_POSITION = btVector3(btScalar(0),
                                         btScalar(1.6 * BODY_SCALE),
                                         btScalar(0));
    
    // HEAD
    double HEAD_RADIUS = 0.10 * BODY_SCALE;
    double HEAD_HEIGHT = 0.05 * BODY_SCALE;
    double HEAD_MASS = 1.0 * BODY_SCALE;
    btVector3 HEAD_ORIENTATION = btVector3(0, 0, 0);
    btVector3 HEAD_POSITION = btVector3(btScalar(0),
                                        btScalar(1.6 * BODY_SCALE),
                                        btScalar(0));
    
    /******************** CONTRAINTS ********************/
    
    // LEFT ANKLE
    
    // RIGHT ANKLE
    
    // LEFT KNEE
    // RIGHT KNEE
    
    // LEFT HIP
    // RIGHT HIP
    
    // SPINE-PELVIS
    
    // NECK
    
    // LEFT SHOULDER
    // RIGHT SHOULDER
    
    // LEFT ARM
    // RIGHT ARM
    
};

#endif /* defined(__test__BodyParameters__) */
