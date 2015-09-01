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
#include "Actuator.h"

#define     BODY_SCALE      1

class BodyParameters {
    
public:

    const double bodyScale = BODY_SCALE;
//    const btVector3 bodyInitialPosition = btVector3(0, 2 * BODY_SCALE, 0);
    const btVector3 bodyInitialPosition = btVector3(0, 0.6 * BODY_SCALE, 0);
    
    const double FEMALE_BODY_MASS = 61.99;
    const double MALE_BODY_MASS = 73;
    
    const double MALE_BODY_HEIGHT = 1.731;
    const double FEMALE_BODY_HEIGHT = 1.735;
    
    const double BODY_MASS = MALE_BODY_MASS;
    const double BODY_HEIGHT = MALE_BODY_HEIGHT;
    
    /******************** ACTUATORS ********************/

    Actuator *rightLowerLegAct, *rightUpperLegAct;
    Actuator *leftLowerLegAct, *leftUpperLegAct;
    Actuator *hipAct;
    Actuator *rightLowerArmAct, *rightUpperArmAct;
    Actuator *leftLowerArmAct, *leftUpperArmAct;
    
    /******************** ANGLES ********************/
    
    double LEFT_LEG_ANGLE = SIMD_PI / 4;
    double RIGHT_LEG_ANGLE = 4 * SIMD_PI / 6;
    double RIGHT_LOWER_LEG_ANGLE = 11 * SIMD_PI / 6;
    
    /******************** PARTS ********************/
    

    
    // Leg body group
    // lower leg
    double L_LEG_RADIUS = 0.05 * BODY_SCALE;
    double L_LEG_HEIGHT = 0.247 * BODY_HEIGHT * BODY_SCALE;
    double L_LEG_MASS = 0.0475 * BODY_MASS * BODY_SCALE;
    btVector3 L_LEG_ORIENTATION = btVector3(0, 0, 0);
    btVector3 L_LEG_POSITION = btVector3(btScalar(0.18 * BODY_SCALE),
                                         btScalar(0.2 * BODY_SCALE),
                                         btScalar(0.0));
    

    //upper leg
    double U_LEG_RADIUS = 0.07 * BODY_SCALE;
    double U_LEG_HEIGHT = 0.232 * BODY_HEIGHT * BODY_SCALE;
    double U_LEG_MASS = 0.105 * BODY_SCALE;
    btVector3 U_LEG_ORIENTATION = btVector3(0, 0, 0);
    btVector3 U_LEG_POSITION = btVector3(btScalar(0.18 * BODY_SCALE),
                                         btScalar(0.65 * BODY_SCALE),
                                         btScalar(0.0));
    

    
    //foots
    double FOOT_MASS = 0.0143 * BODY_MASS * BODY_SCALE;
    btVector3 FOOT_ORIENTATION = btVector3(0, 0, 0);
    btVector3 FOOT_POSITION = btVector3(btScalar(0.18 * BODY_SCALE),
                                        btScalar(-0.1 * BODY_SCALE),
                                        btScalar(-0.075 * BODY_SCALE));
    
    // Arm body group
    //lower arm
    double L_ARM_RADIUS = 0.04 * BODY_SCALE;
    double L_ARM_HEIGHT = 0.157 * BODY_HEIGHT * BODY_SCALE;
    double L_ARM_MASS = 0.0252 * BODY_MASS * BODY_SCALE;
    btVector3 L_ARM_ORIENTATION = btVector3(0, 0, -SIMD_HALF_PI);
    btVector3 L_ARM_POSITION = btVector3(btScalar(0.7 * BODY_SCALE),
                                         btScalar(1.45 * BODY_SCALE),
                                         btScalar(0));
    
    //upper arm
    double U_ARM_RADIUS = 0.05 * BODY_SCALE;
    double U_ARM_HEIGHT = 0.172 * BODY_HEIGHT * BODY_SCALE;
    double U_ARM_MASS = 0.325 * BODY_MASS * BODY_SCALE;
    btVector3 U_ARM_ORIENTATION = btVector3(0, 0, -SIMD_HALF_PI);
    btVector3 U_ARM_POSITION = btVector3(btScalar(0.35 * BODY_SCALE),
                                         btScalar(1.45 * BODY_SCALE),
                                         btScalar(0));
    
    // Torso body group
    // Pelvis
    double PELVIS_RADIUS = 0.15 * BODY_SCALE;
    double PELVIS_HEIGHT = 0.01 * BODY_HEIGHT * BODY_SCALE;
    double PELVIS_MASS = 0.1366 * BODY_MASS * BODY_SCALE;
    btVector3 PELVIS_ORIENTATION = btVector3(0, 0, 0);
    btVector3 PELVIS_POSITION = btVector3(btScalar(0),
                                          btScalar(0.85 * BODY_SCALE),
                                          btScalar(0.0));
    
    // Spine
    double SPINE_RADIUS = 0.15 * BODY_SCALE;
    double SPINE_HEIGHT = 0.127 * BODY_HEIGHT * BODY_SCALE;
    double SPINE_MASS = 0.201 * BODY_MASS * BODY_SCALE;
    btVector3 SPINE_ORIENTATION = btVector3(0, 0, 0);
    btVector3 SPINE_POSITION = btVector3(btScalar(0),
                                         btScalar(1.6 * BODY_SCALE),
                                         btScalar(0));
    
    // HEAD
    double HEAD_RADIUS = 0.10 * BODY_SCALE;
    double HEAD_HEIGHT = 0.1075 * BODY_HEIGHT * BODY_SCALE;
    double HEAD_MASS = 0.0826 * BODY_MASS * BODY_SCALE;
    btVector3 HEAD_ORIENTATION = btVector3(0, 0, 0);
    btVector3 HEAD_POSITION = btVector3(btScalar(0),
                                        btScalar(1.6 * BODY_SCALE),
                                        btScalar(0));
    
    
    double a = (U_LEG_HEIGHT / 2) * sin(SIMD_PI / 6);
    double b = (U_LEG_HEIGHT / 2) * cos(SIMD_PI / 6);
    
    btVector3 RIGHT_L_LEG_POSITION = btVector3(btScalar(0.18 * BODY_SCALE),
                                               btScalar((0.2 + a + 0.1) * BODY_SCALE),
                                               btScalar(-b * 2 - 0.08));
    
    btVector3 RIGHT_U_LEG_POSITION = btVector3(btScalar(0.18 * BODY_SCALE),
                                               btScalar((0.65 + a) * BODY_SCALE),
                                               btScalar(-b));
    
    btVector3 RIGHT_FOOT_POSITION = btVector3(btScalar(0.18 * BODY_SCALE),
                                              btScalar((-0.1 + a + 0.1) * BODY_SCALE),
                                              btScalar((-0.075 - b * 2 - 0.1) * BODY_SCALE));
    

    
    
    /******************** LEG ANGLES ********************/
    
    btQuaternion RIGHT_LEG_ROTATION = btQuaternion(1, 0, 0, RIGHT_LEG_ANGLE);
    btQuaternion RIGHT_LOWER_LEG_ROTATION = btQuaternion(1, 0, 0, RIGHT_LOWER_LEG_ANGLE);
    
    /******************** CONTRAINTS ********************/
    
    
    // ANKLE
    btVector3 ankleFootOffset = btVector3(btScalar(0.065),
                                          btScalar(0.1),
                                          btScalar(0.09));
    btVector3 ankleLowerLegOffset = btVector3(btScalar(0),
                                              btScalar(-L_LEG_HEIGHT / 2),
                                              btScalar(0));
    btVector3 ankleAngularLowerLimit = btVector3(-SIMD_EPSILON,-SIMD_EPSILON,-SIMD_EPSILON);
    btVector3 ankleAngularUpperLimit = btVector3(SIMD_EPSILON,SIMD_EPSILON,SIMD_EPSILON);
    
    
    // KNEE
    btVector3 kneeUpperLegOffset = btVector3(btScalar(0),
                                             btScalar(-U_LEG_HEIGHT / 2),
                                             btScalar(0));
    btVector3 kneeLowerLegOffset = btVector3(btScalar(0),
                                             btScalar(L_LEG_HEIGHT / 2),
                                             btScalar(0));
    btVector3 kneeAngularLowerLimit = btVector3(-SIMD_EPSILON, -SIMD_EPSILON, -SIMD_EPSILON);
    btVector3 kneeAngularUpperLimit = btVector3(SIMD_PI * 0.7, SIMD_EPSILON, SIMD_EPSILON);
    
    
    // SPINE-PELVIS
    btVector3 pelvisOffset = btVector3(btScalar(0.),
                                       btScalar(0.15 * BODY_SCALE),
                                       btScalar(0.));
    btVector3 lowerSpineOffset = btVector3(btScalar(0.),
                                           btScalar(-0.15 * BODY_SCALE),
                                           btScalar(0.));
    
    btVector3 hipLowerAngularLimit = btVector3(-SIMD_PI * 0.2, -SIMD_EPSILON, -SIMD_PI * 0.3);
    btVector3 hipUpperAngularLimit = btVector3(SIMD_PI * 0.2, SIMD_EPSILON, SIMD_PI * 0.6);
    
    btVector3 hipPelvis_eulerZYX = btVector3(0, SIMD_HALF_PI, 0);
    btVector3 hipSpine_eulerZYX = btVector3(0, SIMD_HALF_PI, 0);
    
    
    // NECK
    btVector3 neckUpperSpineOffset = btVector3(btScalar(0.),
                                               btScalar(0.30 * BODY_SCALE),
                                               btScalar(0.));
    btVector3 headOffset = btVector3(btScalar(0.),
                                     btScalar(-0.10 * BODY_SCALE),
                                     btScalar(0.));
    
    btVector3 neckLowerAngularLimit = btVector3(-SIMD_PI * 0.3f, -SIMD_EPSILON, -SIMD_PI * 0.3f);
    btVector3 neckUpperAngularLimit = btVector3(SIMD_PI * 0.5f, SIMD_EPSILON, SIMD_PI * 0.3f);
    
    
    // ELBOW
    btVector3 elbowUpperOffset = btVector3(btScalar(0), btScalar(0.18 * BODY_SCALE), 0);
    btVector3 elbowLowerOffset = btVector3(btScalar(0), btScalar(-0.14 * BODY_SCALE), 0);
    btVector3 elbowAngularUpperLimit = btVector3(-SIMD_EPSILON, -SIMD_EPSILON, -SIMD_EPSILON);
    btVector3 elbowAngularLowerLimit = btVector3(SIMD_PI * 0.7, SIMD_EPSILON, SIMD_EPSILON);
    

    // LEFT SHOULDER
    btVector3 leftShoulderTorsoOffset = btVector3(btScalar(-0.2 * BODY_SCALE),
                                                  btScalar(0.15 * BODY_SCALE),
                                                  btScalar(0.));
    
    btVector3 leftShoulderLeftArmOffset = btVector3(btScalar(0.),
                                                    btScalar(-0.18 * BODY_SCALE),
                                                    btScalar(0.));
    
    btVector3 leftShoulderLeftArmEulerZYX = btVector3(SIMD_HALF_PI, 0, -SIMD_HALF_PI);
    
    btVector3 leftShoulderAngularLowerLimit = btVector3(-SIMD_PI * 0.8, -SIMD_EPSILON, -SIMD_PI * 0.5);
    btVector3 leftShoulderAngularUpperLimit = btVector3(SIMD_PI * 0.8, SIMD_EPSILON, SIMD_PI * 0.5);
    

    // RIGHT SHOULDER
    btVector3 rightShoulderTorsoOffset = btVector3(btScalar(0.2 * BODY_SCALE),
                                                   btScalar(0.15 * BODY_SCALE),
                                                   btScalar(0.));
    
    btVector3 rightShoulderRightArmOffset = btVector3(btScalar(0.),
                                                      btScalar(-0.18 * BODY_SCALE),
                                                      btScalar(0.));
    
    btVector3 rightShoulderRightArmEulerZYX = btVector3(0, 0, SIMD_HALF_PI);
    
    btVector3 rightShoulderAngularLowerLimit = btVector3(-SIMD_PI * 0.8, -SIMD_EPSILON, -SIMD_PI * 0.5);
    btVector3 rightShoulderAngularUpperLimit = btVector3(SIMD_PI * 0.8, SIMD_EPSILON, SIMD_PI * 0.5);
    
    
    // LEFT HIP
    btVector3 leftHipTorsoOffset = btVector3(btScalar(-PELVIS_RADIUS),
                                             btScalar(-PELVIS_HEIGHT),
                                             btScalar(0.));
    
    btVector3 leftHipOffset = btVector3(btScalar(0.),
                                        btScalar(U_LEG_HEIGHT / 2),
                                        btScalar(0.));
    
    btVector3 leftHipAngularUpperLimit = btVector3(SIMD_HALF_PI * 0.8, 0., 0.);
    btVector3 leftHipAngularLowerLimit = btVector3(-SIMD_HALF_PI * 0.5, 0., 0.);
    
    
    // RIGHT HIP
    btVector3 rightHipTorsoOffset = btVector3(btScalar(PELVIS_RADIUS),
                                              btScalar(-PELVIS_HEIGHT),
                                              btScalar(0.));
    
    btVector3 rightHipOffset = btVector3(btScalar(0.),
                                         btScalar(U_LEG_HEIGHT / 2),
                                         btScalar(0.));
    
    btVector3 rightHipAngularUpperLimit = btVector3(SIMD_HALF_PI * 0.8, 0., 0.);
    btVector3 rightHipAngularLowerLimit = btVector3(-SIMD_HALF_PI * 0.5, 0., 0.);
};

#endif /* defined(__test__BodyParameters__) */
