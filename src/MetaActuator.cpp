#include "MetaActuator.h"


MetaActuator::MetaActuator(Actuator *first, Actuator *second) {
    this->first = first;
    this->second = second;
}

btVector3 MetaActuator::eval(double t, int stage) {
    return actuatorFunc(t, stage);
}

void MetaActuator::setParameters(double *params) {
    for (int i = 0; i < PARAMS_SIZE; i++) {
        parameters[i] = params[i];
    }
}

btVector3 MetaActuator::actuatorFunc(double t, int stage) {
    return btVector3(0,0,1);
}

void MetaActuator::setActuatorValues(double vals[]) {
}