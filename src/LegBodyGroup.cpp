#include "LegBodyGroup.h"
#include "CapsuleBodyPart.h"
#include "ConstraintBuilder.h"


LegBodyGroup::LegBodyGroup(btDynamicsWorld* world,
                           double multiplier,
                           const btVector3 positionOffset) : BodyGroup(world){
    BodyPart* lowerLeg = generateLegPart(multiplier * LOWER_LEG_R,
                                         multiplier * LOWER_LEG_H,
                                         LOWER_LEG_M,
                                         positionOffset);
    
    BodyPart* upperLeg = generateLegPart(multiplier * UPPER_LEG_R,
                                         multiplier * UPPER_LEG_H,
                                         UPPER_LEG_M,
                                         positionOffset);
    
    bodyParts.push_back(lowerLeg);
    bodyParts.push_back(upperLeg);
    
    btTypedConstraint* knee = joinLegParts(upperLeg, lowerLeg, multiplier);
    
    constraints.push_back(knee);
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


BodyPart*
LegBodyGroup::generateLegPart(const double r, const double h, const double m, const btVector3 &positionOffset) {
    return new CapsuleBodyPart(btScalar(r), btScalar(h), btScalar(m), positionOffset);
}

BodyPart*
LegBodyGroup::getJointPart() {
    return bodyParts[1];
}