#include "MetaActuator.h"


MetaActuator::MetaActuator(Actuator *first, Actuator *second) {
    this->first = first;
    this->second = second;
}

btVector3 MetaActuator::actuatorFunc(double t, int stage) {
    return second->actuatorFunc(t, stage);
}

void MetaActuator::setActuatorValues(double vals[]) {
    second->setActuatorValues(vals);
}

void MetaActuator::setActuatorValues(double vals1[], double vals2[]) {
    first->setActuatorValues(vals1);
    second->setActuatorValues(vals2);
}

Actuator* MetaActuator::clone() {
    return new MetaActuator(first->clone(), second->clone());
}