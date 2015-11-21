#include "CosineDoubleFrecActuator.h"
#include <iostream>

#define A 0
#define W1 1
#define W2 2
#define FASE 3
#define IND_TERM 4


CosineDoubleFrecActuator::CosineDoubleFrecActuator(bool isLeft) : Actuator(isLeft) {
    
}

btVector3 CosineDoubleFrecActuator::actuatorFunc(double t, int stage) {
    btVector3 resp;
//    double omega = (2*parameters[W1]*parameters[W2])/(parameters[W1]+parameters[W2]);
    
    double psi = t + parameters[FASE] - floor((t + parameters[FASE])/((SIMD_PI/parameters[W1]) + (SIMD_PI/parameters[W2]))) * ((SIMD_PI/parameters[W1]) + (SIMD_PI/parameters[W2]));
    
    if(parameters[W1]*psi < SIMD_PI) {
        resp = btVector3(parameters[A]*cos(parameters[W1]*psi) + parameters[IND_TERM],0,0);
    } else {
        resp = btVector3(parameters[A]*cos(parameters[W2]*(psi-(SIMD_PI/parameters[W1])+(SIMD_PI/parameters[W2]))) + parameters[IND_TERM],0,0);
    }
    
//    std::cout << resp.x() << std::endl;
//    std::cout << t << std::endl;
    return resp;
}

bool CosineDoubleFrecActuator::isFirstStep(double t){
    return false;
}

void CosineDoubleFrecActuator::setActuatorValues(double vals[]) {
    parameters[A] = vals[A];
    parameters[W1] = vals[W1];
    parameters[W2] = vals[W2];
    parameters[FASE] = vals[FASE];
    parameters[IND_TERM] = vals[IND_TERM];
}
