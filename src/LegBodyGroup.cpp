#include "LegBodyGroup.h"
#include "CapsuleBodyPart.h"
#include "ConstraintBuilder.h"
#include "GenericActuator.h"


LegBodyGroup::LegBodyGroup(btDynamicsWorld* world,
                           BodyParameters &params,
                           const btVector3 positionAdjust,
                           bool isLeft) : BodyGroup(world){
    
    Actuator* lowerLegAct;
    Actuator* upperLegAct;
    if (isLeft) {
        lowerLegAct = params.leftLowerLegAct;
        upperLegAct = params.leftUpperLegAct;
    } else {
        lowerLegAct = params.rightLowerLegAct;
        upperLegAct = params.rightUpperLegAct;
    }
    btVector3 lowerLegPos(params.L_LEG_POSITION.x() * positionAdjust.x(),
                          params.L_LEG_POSITION.y() * positionAdjust.y(),
                          params.L_LEG_POSITION.z() * positionAdjust.z());
    
    BodyPart* lowerLeg = generateStandardPart(params.L_LEG_RADIUS,
                                              params.L_LEG_HEIGHT,
                                              params.L_LEG_MASS,
                                              lowerLegPos,
                                              params.bodyInitialPosition,
                                              lowerLegAct);

    btVector3 upperLegPos(params.U_LEG_POSITION.x() * positionAdjust.x(),
                          params.U_LEG_POSITION.y() * positionAdjust.y(),
                          params.U_LEG_POSITION.z() * positionAdjust.z());
    BodyPart* upperLeg = generateStandardPart(params.U_LEG_RADIUS,
                                              params.U_LEG_HEIGHT,
                                              params.U_LEG_MASS,
                                              upperLegPos,
                                              params.bodyInitialPosition,
                                              upperLegAct);
    
    btTransform footTrans;
    btVector3 footPos(params.FOOT_POSITION.x() * positionAdjust.x(),
                      params.FOOT_POSITION.y() * positionAdjust.y(),
                      params.FOOT_POSITION.z() * positionAdjust.z());
    footTrans.setIdentity();
    footTrans.setOrigin(footPos);
    footTrans.getBasis().setEulerZYX(params.FOOT_ORIENTATION.x(),
                                     params.FOOT_ORIENTATION.y(),
                                     params.FOOT_ORIENTATION.z());
    BodyPart* foot = generateFoot(params.FOOT_MASS,
                                  footTrans,
                                  params.bodyInitialPosition);
    
    bodyParts.push_back(lowerLeg);
    bodyParts.push_back(upperLeg);
    bodyParts.push_back(foot);
    
    btTypedConstraint* knee = joinLegParts(upperLeg, lowerLeg, params);
    btTypedConstraint* ankle = createAnkle(lowerLeg, foot, params);
    
    constraints.push_back(knee);
    constraints.push_back(ankle);
}

btGeneric6DofConstraint*
LegBodyGroup::joinLegParts(BodyPart* upperLeg,
                           BodyPart* lowerLeg,
                           BodyParameters &params) {
    
    ConstraintParams constraintParams = {
        upperLeg,
        lowerLeg,
        params.kneeUpperLegOffset,
        params.kneeLowerLegOffset,
        nullptr,
        nullptr,
        params.kneeAngularLowerLimit,
        params.kneeAngularUpperLimit,
    };
    
    return ConstraintBuilder::create6DoFConstraint(constraintParams);
    
}

btGeneric6DofConstraint*
LegBodyGroup::createAnkle(BodyPart* lowerLeg,
                          BodyPart* ankle,
                          BodyParameters &params) {
    
    ConstraintParams constraintParams = {
        lowerLeg,
        ankle,
        params.ankleLowerLegOffset,
        params.ankleFootOffset,
        nullptr,
        nullptr,
        params.ankleAngularLowerLimit,
        params.ankleAngularUpperLimit
    };
    
    return ConstraintBuilder::create6DoFConstraint(constraintParams);
}

BodyPart*
LegBodyGroup::getJointPart() {
    return bodyParts[1];
}
