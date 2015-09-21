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
    
    double f = sin_amplitude * sin(sin_freq * t + fase) + cos_amplitude * cos(cos_freq * t + fase) + C;
    return btVector3(f, 0, 0);
}

void GenericActuator::setA(double valueA) {
    sin_amplitude = valueA;
}

void GenericActuator::setB(double valueB) {
    cos_amplitude = valueB;
}

void GenericActuator::setw1(double valuew1) {
    sin_freq = valuew1;
}

void GenericActuator::setw2(double valuew2) {
    cos_freq = valuew2;
}

void GenericActuator::setFase(double valueFase) {
    fase = valueFase;
}
void GenericActuator::setIndTerm(double value) {
    C = value;
}