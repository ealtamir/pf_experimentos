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
    btTransform v = rigidBody->getCenterOfMassTransform();
    return v.getOrigin().getY();
}

double
WalkerBody::getPosition(){
    GenericTorsoBodyGroup* torso = dynamic_cast<GenericTorsoBodyGroup*>(bodyGroups.back());
    BodyPart* bp = torso->getLeftHipPart();
    btRigidBody* rigidBody = bp->getRigidBody();
    btTransform v = rigidBody->getCenterOfMassTransform();
    return v.getOrigin().getZ();
}

double
WalkerBody::getAngleInclination(){
    GenericTorsoBodyGroup* torso = dynamic_cast<GenericTorsoBodyGroup*>(bodyGroups.back());
    BodyPart* bp = torso->getLeftHipPart();
    btRigidBody* rigidBody = bp->getRigidBody();
    btTransform v = rigidBody->getCenterOfMassTransform();
    double x = v.getOrigin().getX();
    double y = v.getOrigin().getY();
    if (x==0){
        return 0;
    }
    return (asin(fmin(1.0, fmax(-1.0,x/y)))*180/M_PI);
    //return (acos(fmin(1.0, fmax(-1.0,y/x)))*180/M_PI); // lo del fmin y fmax es para limitar el input de acos entre 1 y -1 (y a veces puede haber error de cómputo)
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
