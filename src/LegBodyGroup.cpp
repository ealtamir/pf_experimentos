#include "LegBodyGroup.h"
#include "CapsuleBodyPart.h"
#include "ConstraintBuilder.h"


LegBodyGroup::LegBodyGroup(btDynamicsWorld* world,
                           double multiplier,
                           const btVector3 positionAdjust,
                           const btVector3 positionOffset) : BodyGroup(world){
    
    
    btVector3 lowerLegPos(btScalar(0.18) * positionAdjust.x(),
                          btScalar(0.2) * positionAdjust.y(),
                          btScalar(0.) * positionAdjust.z());
    BodyPart* lowerLeg = generateStandardPart(multiplier * LOWER_LEG_R,
                                              multiplier * LOWER_LEG_H,
                                              LOWER_LEG_M,
                                              lowerLegPos,
                                              positionOffset);

    btVector3 upperLegPos(btScalar(0.18) * positionAdjust.x(),
                          btScalar(0.65) * positionAdjust.y(),
                          btScalar(0.) * positionAdjust.z());
    BodyPart* upperLeg = generateStandardPart(multiplier * UPPER_LEG_R,
                                              multiplier * UPPER_LEG_H,
                                              UPPER_LEG_M,
                                              upperLegPos,
                                              positionOffset);
    
    btTransform footTrans;
    btVector3 footPos(btScalar(0.18) * positionAdjust.x(),
                      btScalar(0.2) * positionAdjust.y(),
                      btScalar(0.) * positionAdjust.z());
    footTrans.setIdentity();
    footTrans.setOrigin(footPos);
    footTrans.getBasis().setEulerZYX(SIMD_HALF_PI, 0, 0);
    BodyPart* foot = generateStandardPart(multiplier * FOOT_R,
                                          multiplier * FOOT_H,
                                          FOOT_M,
                                          footTrans,
                                          positionOffset);
    
    bodyParts.push_back(lowerLeg);
    bodyParts.push_back(upperLeg);
    bodyParts.push_back(foot);
    
    btTypedConstraint* knee = joinLegParts(upperLeg, lowerLeg, multiplier);
    btTypedConstraint* ankle = createAnkle(lowerLeg, foot, multiplier);
    
    constraints.push_back(knee);
    constraints.push_back(ankle);
}

btGeneric6DofConstraint*
LegBodyGroup::joinLegParts(BodyPart* upperLeg,
                           BodyPart* lowerLeg,
                           double multiplier) {

    btVector3 upperOffset(btScalar(0.),
                         btScalar(-0.225 * multiplier),
                         btScalar(0.));
    
    btVector3 lowerOffset(btScalar(0.),
                         btScalar(0.185 * multiplier),
                         btScalar(0.));
    
    btVector3 angularLowerLimit(-SIMD_EPSILON,-SIMD_EPSILON,-SIMD_EPSILON);
    btVector3 angularUpperLimit(SIMD_PI*0.7f, SIMD_EPSILON, SIMD_EPSILON);
    
    ConstraintParams params = {
        upperLeg,
        lowerLeg,
        upperOffset,
        lowerOffset,
        nullptr,
        nullptr,
        angularLowerLimit,
        angularUpperLimit,
        multiplier
    };
    
    return ConstraintBuilder::create6DoFConstraint(params);
    
}

btGeneric6DofConstraint*
LegBodyGroup::createAnkle(BodyPart* lowerLeg,
                          BodyPart* ankle,
                          double multiplier) {
    
    btVector3 upperOffset(btScalar(0.),
                          btScalar(-0.225 * multiplier),
                          btScalar(0.));
    
    btVector3 lowerOffset(btScalar(0.),
                          btScalar(0.185 * multiplier),
                          btScalar(0.));
    
    btVector3 angularLowerLimit(SIMD_EPSILON * 0.5, SIMD_EPSILON, SIMD_EPSILON);
    btVector3 angularUpperLimit(-SIMD_PI, -SIMD_EPSILON, -SIMD_EPSILON);
    
    ConstraintParams params = {
        lowerLeg,
        ankle,
        upperOffset,
        lowerOffset,
        nullptr,
        nullptr,
        angularLowerLimit,
        angularUpperLimit,
        multiplier
    };
    
    return ConstraintBuilder::create6DoFConstraint(params);
}

BodyPart*
LegBodyGroup::getJointPart() {
    return bodyParts[1];
}
