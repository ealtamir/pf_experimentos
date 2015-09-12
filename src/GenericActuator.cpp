//
//  GenericActuator.cpp
//  test
//
//  Created by Enzo Altamiranda G on 04.08.15.
//  Copyright (c) 2015 Enzo Altamiranda G. All rights reserved.
//

#include "GenericActuator.h"


GenericActuator::GenericActuator(bool isLeft) : Actuator(isLeft) {

}

btVector3 GenericActuator::actuatorFunc(double t) {
    
    double f = A * sin(w1 * t + fase) + B * cos(w2 * t + fase);
    return btVector3(f, 0, 0);
}

void GenericActuator::setA(double valueA) {
    A = valueA;
}

void GenericActuator::setB(double valueB) {
    B = valueB;
}

void GenericActuator::setw1(double valuew1) {
    w1 = valuew1;
}

void GenericActuator::setw2(double valuew2) {
    w2 = valuew2;
}

void GenericActuator::setFase(double valueFase) {
    fase = valueFase;
}