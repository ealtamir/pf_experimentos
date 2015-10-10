#include "LegBodyGroup.h"
#include "CapsuleBodyPart.h"
#include "ConstraintBuilder.h"
#include "GenericActuator.h"

#define     USE_DEFAULT     false


LegBodyGroup::LegBodyGroup(btDynamicsWorld* world,
                           BodyParameters &params,
                           const btVector3 positionAdjust,
                           bool isLeft) : BodyGroup(world){
    
    Actuator* lowerLegAct;
    Actuator* upperLegAct;
    BodyPart* lowerLeg;
    BodyPart* upperLeg;
    BodyPart* foot;

    btTransform trans;
    trans.setIdentity();
    if (isLeft) {
        lowerLegAct = params.leftLowerLegAct;
        upperLegAct = params.leftUpperLegAct;
        
    } else {
        lowerLegAct = params.rightLowerLegAct;
        upperLegAct = params.rightUpperLegAct;
    }
    
    btVector3 lowerLegCenterOfMass(0,
                                   params.L_LEG_HEIGHT+params.L_LEG_RADIUS,
                                   0);
//    btVector3 lowerLegCenterOfMass(0,0,0);

    if (isLeft || USE_DEFAULT) {
        btVector3 lowerLegPos(params.L_LEG_POSITION.x() * positionAdjust.x(),
                              params.L_LEG_POSITION.y() * positionAdjust.y(),
                              params.L_LEG_POSITION.z() * positionAdjust.z());
        
        lowerLeg = generateStandardPart(params.L_LEG_RADIUS,
                                        params.L_LEG_HEIGHT,
                                        params.L_LEG_MASS,
                                        lowerLegPos,
                                        params.bodyInitialPosition,
                                        lowerLegCenterOfMass,
                                        lowerLegAct);
    } else {

        btVector3 lowerLegPos(params.RIGHT_L_LEG_POSITION.x() * positionAdjust.x(),
                              params.RIGHT_L_LEG_POSITION.y() * positionAdjust.y(),
                              params.RIGHT_L_LEG_POSITION.z() * positionAdjust.z());
        trans.setIdentity();
        trans.setOrigin(lowerLegPos);
        trans.setRotation(params.RIGHT_LOWER_LEG_ROTATION);
        lowerLeg = generateStandardPart(params.L_LEG_RADIUS,
                                        params.L_LEG_HEIGHT,
                                        params.L_LEG_MASS,
                                        trans,
                                        params.bodyInitialPosition,
                                        lowerLegCenterOfMass,
                                        lowerLegAct);
    }
    
    //cambio el centro de masa, que supongo esta en el (0,0,0) a la parte de arriba
    btVector3 upperLegCenterOfMass(0,
                                   (params.U_LEG_HEIGHT+params.U_LEG_RADIUS),
                                   0);
    
//    btVector3 upperLegCenterOfMass(0,0,0);
    
    if (isLeft || USE_DEFAULT) {
        btVector3 upperLegPos(params.U_LEG_POSITION.x() * positionAdjust.x(),
                              params.U_LEG_POSITION.y() * positionAdjust.y(),
                              params.U_LEG_POSITION.z() * positionAdjust.z());
        upperLeg = generateStandardPart(params.U_LEG_RADIUS,
                                        params.U_LEG_HEIGHT,
                                        params.U_LEG_MASS,
                                        upperLegPos,
                                        params.bodyInitialPosition,
                                        upperLegCenterOfMass,
                                        upperLegAct);

    } else {
        btVector3 upperLegPos(params.RIGHT_U_LEG_POSITION.x() * positionAdjust.x(),
                              params.RIGHT_U_LEG_POSITION.y() * positionAdjust.y(),
                              params.RIGHT_U_LEG_POSITION.z() * positionAdjust.z());
        
        trans.setIdentity();
        trans.setOrigin(upperLegPos);
        trans.setRotation(params.RIGHT_LEG_ROTATION);
        upperLeg = generateStandardPart(params.U_LEG_RADIUS,
                                        params.U_LEG_HEIGHT,
                                        params.U_LEG_MASS,
                                        trans,
                                        params.bodyInitialPosition,
                                        upperLegCenterOfMass,
                                        upperLegAct);
    }

    if (isLeft || USE_DEFAULT) {
        btTransform footTrans;
        btVector3 footPos(params.FOOT_POSITION.x() * positionAdjust.x(),
                          params.FOOT_POSITION.y() * positionAdjust.y(),
                          params.FOOT_POSITION.z() * positionAdjust.z());
        footTrans.setIdentity();
        footTrans.setOrigin(footPos);
        footTrans.getBasis().setEulerZYX(params.FOOT_ORIENTATION.x(),
                                         params.FOOT_ORIENTATION.y(),
                                         params.FOOT_ORIENTATION.z());
        foot = generateFoot(params.FOOT_MASS,
                            footTrans,
                            params.bodyInitialPosition);
    } else {
        btTransform footTrans;
        btVector3 footPos(params.RIGHT_FOOT_POSITION.x() * positionAdjust.x(),
                          params.RIGHT_FOOT_POSITION.y() * positionAdjust.y(),
                          params.RIGHT_FOOT_POSITION.z() * positionAdjust.z());
        footTrans.setIdentity();
        footTrans.setOrigin(footPos);
        footTrans.getBasis().setEulerZYX(params.FOOT_ORIENTATION.x(),
                                         params.FOOT_ORIENTATION.y(),
                                         params.FOOT_ORIENTATION.z());
        foot = generateFoot(params.FOOT_MASS,
                            footTrans,
                            params.bodyInitialPosition);
    }

    
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

double*
LegBodyGroup::getAngles() {
    
    BodyPart* lower= bodyParts[0];
    btRigidBody * lower_rigid = lower->getRigidBody();
    btTransform v = lower_rigid->getCenterOfMassTransform();
    double z = v.getOrigin().getZ();
    double y = v.getOrigin().getY();
    angles[0] = ((z==0)?0:(asin(fmin(1.0, fmax(-1.0,z/y)))*180/M_PI));
    
    BodyPart* upper= bodyParts[1];
    btRigidBody * upper_rigid = upper->getRigidBody();
    v = upper_rigid->getCenterOfMassTransform();
    z = v.getOrigin().getZ();
    y = v.getOrigin().getY();
    angles[1] = ((z==0)?0:(asin(fmin(1.0, fmax(-1.0,z/y)))*180/M_PI));
    
    btRigidBody * foot_rigid = upper->getRigidBody();
    v = foot_rigid->getCenterOfMassTransform();
    z = v.getOrigin().getZ();
    y = v.getOrigin().getY();
    angles[2] = ((z==0)?0:(asin(fmin(1.0, fmax(-1.0,z/y)))*180/M_PI));
    
    /*for (int i=0; i<2; i++) {
        BodyPart* bp= bodyParts[i];
        btRigidBody * bp_rigid = bp->getRigidBody();
        btTransform v = bp_rigid->getCenterOfMassTransform();
        double z = v.getOrigin().getZ();
        double y = v.getOrigin().getY();
        angles[i] = ((z==0)?0:(asin(fmin(1.0, fmax(-1.0,z/y)))*180/M_PI));
    }*/
    
    return angles;
}