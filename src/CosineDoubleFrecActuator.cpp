#include "CosineDoubleFrecActuator.h"

#define A 0
#define W1 1
#define W2 2
#define FASE 3
#define IND_TERM 4


CosineDoubleFrecActuator::CosineDoubleFrecActuator(bool isLeft) : Actuator(isLeft) {
    
}

btVector3 CosineDoubleFrecActuator::actuatorFunc(double t, int stage) {
    int stage_index = 0;
    if (stage == 1) {
        stage_index = 5;
    }
    double psi_t = t + parameters[stage_index+FASE] - ((t + parameters[stage_index+FASE])/((SIMD_PI/parameters[stage_index+W1])*(SIMD_PI/parameters[stage_index+W2])))*((SIMD_PI/parameters[stage_index+W1])*(SIMD_PI/parameters[stage_index+W2]));
    bool function_condition = (parameters[stage_index+W1]*psi_t) < SIMD_PI;
    if (function_condition) {
        return btVector3(parameters[stage_index+A]*cos(parameters[stage_index+W1]*psi_t) + parameters[stage_index+IND_TERM],0,0);
    } else {
        return btVector3(parameters[stage_index+A]*cos(parameters[stage_index+W2]*(psi_t-(SIMD_PI/parameters[stage_index+W1])+(SIMD_PI/parameters[stage_index+W2]))) + parameters[stage_index+IND_TERM],0,0);
    }
}