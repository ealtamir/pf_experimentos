//
//  WalkerBody.cpp
//  test
//
//  Created by Enzo Altamiranda G on 05.08.15.
//  Copyright (c) 2015 Enzo Altamiranda G. All rights reserved.
//

#include "WalkerBody.h"
#include "GenericTorsoBodyGroup.h"
#include "LegBodyGroup.h"

WalkerBody::WalkerBody(btDynamicsWorld* world, BodyParameters &params) : GenericBody(world, params) {
    

    BodyGroup* leftLeg = createLeftLeg(world, params);
    BodyGroup* rightLeg = createRightLeg(world, params);
    BodyGroup* torso = createTorso(world, params);
    
    GenericTorsoBodyGroup* torsoGroup = dynamic_cast<GenericTorsoBodyGroup*>(torso);
    

    createLeftHip(leftLeg->getJointPart(),
                  torsoGroup->getLeftHipPart(),
                  params);
    createRightHip(rightLeg->getJointPart(),
                   torsoGroup->getRightHipPart(),
                   params);

}

BodyGroup*
WalkerBody::createTorso(btDynamicsWorld* world, BodyParameters &params) {
    
    BodyGroup* torso = new GenericTorsoBodyGroup(world,
                                          params,
                                          rightOffset);
    bodyGroups.push_back(torso);
    torso->initBodyGroup();
    return torso;
}

std::vector<BodyGroup*> WalkerBody::getBodyGroups(){
    return bodyGroups;
}

double
WalkerBody::getHeight(){
    GenericTorsoBodyGroup* torso = dynamic_cast<GenericTorsoBodyGroup*>(bodyGroups.back());
    BodyPart* bp = torso->getLeftHipPart();
    btRigidBody* rigidBody = bp->getRigidBody();
    btTransform v;
    rigidBody->getMotionState()->getWorldTransform(v);
    //printf("%f - %f - %f \n",v.getOrigin().getX(),v.getOrigin().getY(),v.getOrigin().getZ());
    
    return v.getOrigin().getY();
}

double
WalkerBody::getPosition(){
    GenericTorsoBodyGroup* torso = dynamic_cast<GenericTorsoBodyGroup*>(bodyGroups.back());
    BodyPart* bp = torso->getLeftHipPart();
    btRigidBody* rigidBody = bp->getRigidBody();
    btTransform v;
    rigidBody->getMotionState()->getWorldTransform(v);
    return v.getOrigin().getZ();
}

btVector3
WalkerBody::getVelocity(){
    GenericTorsoBodyGroup* torso = dynamic_cast<GenericTorsoBodyGroup*>(bodyGroups.back());
    BodyPart* bp = torso->getLeftHipPart();
    btRigidBody* rigidBody = bp->getRigidBody();
    // btTransform v;
    // rigidBody->getMotionState()->getWorldTransform(v);
    
    return rigidBody->getLinearVelocity();
}


double
WalkerBody::getAngleInclination(){
    GenericTorsoBodyGroup* torso = dynamic_cast<GenericTorsoBodyGroup*>(bodyGroups.back());
    BodyPart* bp = torso->getLeftHipPart();
    btRigidBody* rigidBody = bp->getRigidBody();
    btTransform v;
    rigidBody->getMotionState()->getWorldTransform(v);
    btVector3 actual_position = v.getOrigin();
    double angle=actual_position.dot(previous)/(actual_position.norm()*previous.norm());
    
    previous=actual_position; //estamos tomando la ""velocidad"" instantanea
    
    return (acos(fmin(1.0, fmax(-1.0,angle)))*180/M_PI);
    
    /*double actual_position_x = v.getOrigin().getX();
    double actual_position_z = v.getOrigin().getZ();
    
    double x = actual_position_x - previous_position_x;
    double z = actual_position_z - previous_position_z;
    
    previous_position_x = actual_position_x;
    previous_position_z = actual_position_z;
    
    if (x==0){
        return 0;
    }
    return (asin(fmin(1.0, fmax(-1.0,x/z)))*180/M_PI);
    */
}

void
WalkerBody::cicleQuantity(){
    
    LegBodyGroup* leg_1 = dynamic_cast<LegBodyGroup*>(bodyGroups[0]);
    LegBodyGroup* leg_2 = dynamic_cast<LegBodyGroup*>(bodyGroups[1]);
    double* angles_1 = leg_1->getAngles();
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
WalkerBody::getCycleQuantity(){
    
    return cicleQty;
}

double*
WalkerBody::getAnglesLegs(){
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
