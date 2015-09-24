#include "CosineDoubleFrecActuator.h"

#define A 0
#define W1 1
#define W2 2
#define FASE 3
#define IND_TERM 4


CosineDoubleFrecActuator::CosineDoubleFrecActuator(bool isLeft) : Actuator(isLeft) {
    
}

btVector3 CosineDoubleFrecActuator::actuatorFunc(double t) {
    double psi_t = t + parameters[FASE] - ((t + parameters[FASE])/((SIMD_PI/parameters[W1])*(SIMD_PI/parameters[W2])))*((SIMD_PI/parameters[W1])*(SIMD_PI/parameters[W2]));
    bool function_condition = (parameters[W1]*psi_t) < SIMD_PI;
    if (function_condition) {
        return btVector3(parameters[A]*cos(parameters[W1]*psi_t) + parameters[IND_TERM],0,0);
    } else {
        return btVector3(parameters[A]*cos(parameters[W2]*(psi_t-(SIMD_PI/parameters[W1])+(SIMD_PI/parameters[W2]))) + parameters[IND_TERM],0,0);
    }
}