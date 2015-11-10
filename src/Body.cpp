#include "Body.h"
#include <BulletDynamics/btBulletDynamicsCommon.h>
#include "BodyGroup.h"
#include "ArmBodyGroup.h"
#include "LegBodyGroup.h"
#include "GenericTorsoBodyGroup.h"
#include "ConstraintBuilder.h"


Body::Body(btDynamicsWorld* world) {
	this->world = world;
}

Body::~Body() {
    
    for (btTypedConstraint* constraint : constraints) {
        world->removeConstraint(constraint);
        delete constraint;
    }
    for (BodyGroup* group : bodyGroups) {
		delete group;
	}
}

void
Body::actuate(double t, int stage) {
    for (BodyGroup* group : bodyGroups) {
        group->actuate(t, stage);
    }
}


std::vector<BodyGroup*> Body::getBodyGroups(){
    return bodyGroups;
}


btTypedConstraint*
Body::createLeftShoulder(BodyPart* leftArm, BodyPart* torso,
                                BodyParameters &params) {
    ConstraintParams constraintParams = {
        torso,
        leftArm,
        params.leftShoulderTorsoOffset,
        params.leftShoulderLeftArmOffset,
        nullptr,
        &params.leftShoulderLeftArmEulerZYX,
        params.leftShoulderAngularLowerLimit,
        params.leftShoulderAngularUpperLimit
    };
    
    btTypedConstraint* constraint = ConstraintBuilder::create6DoFConstraint(constraintParams);
    constraints.push_back(constraint);
    world->addConstraint(constraint, true);
    return constraint;
}

btTypedConstraint*
Body::createRightShoulder(BodyPart* rightArm, BodyPart* torso,
                                 BodyParameters &params) {
    
    ConstraintParams constraintParams = {
        torso,
        rightArm,
        params.rightShoulderTorsoOffset,
        params.rightShoulderRightArmOffset,
        nullptr,
        &params.rightShoulderRightArmEulerZYX,
        params.rightShoulderAngularLowerLimit,
        params.rightShoulderAngularUpperLimit
    };
    
    btTypedConstraint* constraint = ConstraintBuilder::create6DoFConstraint(constraintParams);
    constraints.push_back(constraint);
    world->addConstraint(constraint, true);
    return constraint;
}

btTypedConstraint*
Body::createLeftHip(BodyPart* leftHip, BodyPart* torso,
                           BodyParameters &params) {
    
    ConstraintParams constraintParams = {
        torso,
        leftHip,
        params.leftHipTorsoOffset,
        params.leftHipOffset,
        nullptr,
        nullptr,
        params.leftHipAngularLowerLimit,
        params.leftHipAngularUpperLimit
    };
    
    btTypedConstraint* constraint = ConstraintBuilder::create6DoFConstraint(constraintParams);
    constraints.push_back(constraint);
    world->addConstraint(constraint, true);
    return constraint;
}

btTypedConstraint*
Body::createRightHip(BodyPart* rightHip, BodyPart* torso,
                            BodyParameters &params) {
    
    ConstraintParams constraintParams = {
        torso,
        rightHip,
        params.rightHipTorsoOffset,
        params.rightHipOffset,
        nullptr,
        nullptr,
        params.rightHipAngularLowerLimit,
        params.rightHipAngularUpperLimit
    };
    
    btTypedConstraint* constraint = ConstraintBuilder::create6DoFConstraint(constraintParams);
    
    constraints.push_back(constraint);
    world->addConstraint(constraint, true);
    return constraint;
}

BodyGroup*
Body::createLeftArm(btDynamicsWorld* world,
                           BodyParameters &params) {
    BodyGroup* left_arm = new ArmBodyGroup(world,
                                           params,
                                           leftOffset);
    bodyGroups.push_back(left_arm);
    left_arm->initBodyGroup();
    return left_arm;
}

BodyGroup*
Body::createRightArm(btDynamicsWorld* world,
                            BodyParameters &params) {
    BodyGroup* right_arm = new ArmBodyGroup(world,
                                            params,
                                            rightOffset);
    bodyGroups.push_back(right_arm);
    right_arm->initBodyGroup();
    return right_arm;
}

BodyGroup*
Body::createLeftLeg(btDynamicsWorld* world,
                           BodyParameters &params) {
    BodyGroup* left_leg = new LegBodyGroup(world,
                                           params,
                                           leftOffset, true);
    bodyGroups.push_back(left_leg);
    left_leg->initBodyGroup();
    return left_leg;
}

BodyGroup*
Body::createRightLeg(btDynamicsWorld* world,
                            BodyParameters &params) {
    BodyGroup* right_leg = new LegBodyGroup(world,
                                            params,
                                            rightOffset);
    bodyGroups.push_back(right_leg);
    right_leg->initBodyGroup();
    return right_leg;
}

BodyGroup*
Body::createTorso(btDynamicsWorld* world, BodyParameters &params) {
    
    BodyGroup* torso = new GenericTorsoBodyGroup(world,
                                                 params,
                                                 rightOffset);
    bodyGroups.push_back(torso);
    torso->initBodyGroup();
    return torso;
}

double
Body::getHeight(){
    GenericTorsoBodyGroup* torso = dynamic_cast<GenericTorsoBodyGroup*>(bodyGroups.back());
    BodyPart* bp = torso->getBodyParts()[0];
    btRigidBody* rigidBody = bp->getRigidBody();
    btTransform v;
    rigidBody->getMotionState()->getWorldTransform(v);
    return v.getOrigin().getY();
}

double
Body::getLeftFootHeight(){
    LegBodyGroup* left_leg = dynamic_cast<LegBodyGroup*>(bodyGroups[0]);
    BodyPart* bp_left_leg = left_leg->getBodyParts()[2];
    
    btRigidBody* rigid_body_left_leg = bp_left_leg->getRigidBody();
    btTransform v;
    rigid_body_left_leg->getMotionState()->getWorldTransform(v);
    
    return v.getOrigin().getY();
}

double
Body::getRightFootHeight(){
    LegBodyGroup* right_leg = dynamic_cast<LegBodyGroup*>(bodyGroups[1]);
    BodyPart* bp_right_leg = right_leg->getBodyParts()[2];
    
    btRigidBody* rigid_body_right_leg = bp_right_leg->getRigidBody();
    btTransform v;
    rigid_body_right_leg->getMotionState()->getWorldTransform(v);
    
    return v.getOrigin().getY();
}

btVector3
Body::getPosition(){
    GenericTorsoBodyGroup* torso = dynamic_cast<GenericTorsoBodyGroup*>(bodyGroups.back());
    BodyPart* bp = torso->getLeftHipPart();
    btRigidBody* rigidBody = bp->getRigidBody();
    btTransform v;
    rigidBody->getMotionState()->getWorldTransform(v);
    return v.getOrigin();
}

btVector3
Body::getVelocity(){
    GenericTorsoBodyGroup* torso = dynamic_cast<GenericTorsoBodyGroup*>(bodyGroups.back());
    BodyPart* bp = torso->getLeftHipPart();
    btRigidBody* rigidBody = bp->getRigidBody();
    // btTransform v;
    // rigidBody->getMotionState()->getWorldTransform(v);
    
    return rigidBody->getLinearVelocity();
}

// Converts a quaternion to an euler angle
void QuaternionToEuler(const btQuaternion &TQuat, btVector3 &TEuler)
{
    btScalar W = TQuat.getW();
    btScalar X = TQuat.getX();
    btScalar Y = TQuat.getY();
    btScalar Z = TQuat.getZ();
    float WSquared = W * W;
    float XSquared = X * X;
    float YSquared = Y * Y;
    float ZSquared = Z * Z;
    
    TEuler.setX(atan2f(2.0f * (Y * Z + X * W), -XSquared - YSquared + ZSquared + WSquared));
    TEuler.setY(asinf(-2.0f * (X * Z - Y * W)));
    TEuler.setZ(atan2f(2.0f * (X * Y + Z * W), XSquared - YSquared - ZSquared + WSquared));
    TEuler *= 57.2957795;
}

double
Body::getAngleInclination(){
    GenericTorsoBodyGroup* torso = dynamic_cast<GenericTorsoBodyGroup*>(bodyGroups.back());
    BodyPart* bp = torso->getLeftHipPart();
    btRigidBody* rigidBody = bp->getRigidBody();
    btTransform v;
    rigidBody->getMotionState()->getWorldTransform(v);
    btVector3 actual_position = v.getOrigin();
    
    double deltaX = -actual_position.getX();
    double deltaZ = -actual_position.getZ()-0.15;
    double resp = atan2(deltaZ, deltaX) * 180 / SIMD_PI;
    return resp;
}

void
Body::cicleQuantity(){
    LegBodyGroup* leg_2 = dynamic_cast<LegBodyGroup*>(bodyGroups[1]);
    double* angles_2 = leg_2->getAngles();
    
    //tomo el upper de la pierna 2 para definir los ciclos
    
    if(cicleQty<0 && angles_2[1]!=0){
        cicleQty=0;
        last_angle= angles_2[1];
        return;
    }
    
    //si la cantidad de ciclos es par, busco el mínimo. Si es impar, el máximo
    if(cicleQty%2==0){
        if(last_angle<angles_2[1]){
            cicleQty++;
        }
    }
    else {
        if(last_angle>angles_2[1]){
            cicleQty++;
        }
    }
    last_angle= angles_2[1];
    
    return;
}

int
Body::getCycleQuantity(){
    return cicleQty;
}

double*
Body::getAnglesLegs(){
    double * angles= new double[6];
    LegBodyGroup* leg_1 = dynamic_cast<LegBodyGroup*>(bodyGroups[0]);
    LegBodyGroup* leg_2 = dynamic_cast<LegBodyGroup*>(bodyGroups[1]);
    double* angles_1 = leg_1->getAngles();
    double* angles_2 = leg_2->getAngles();
    /*for(int i=0; i<3;i++){
     angles[i]=angles_1[i];
     }
     for(int i=0; i<3;i++){
     angles[3+i]=angles_2[i];
     }*/
    std::copy(angles_1,angles_1+3,angles);
    std::copy(angles_2,angles_2+3,angles+3);
    return angles;
}