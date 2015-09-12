#include "BodyPart.h"


BodyPart::~BodyPart() {
	delete body->getMotionState();
	delete body;
}

void BodyPart::actuate(double t) {
    if (actuator != nullptr) {
        body->applyTorque(actuator->eval(t));
    }
}

void BodyPart::setActuatorValues(double paramA, double paramB, double paramw1, double paramw2, double paramFase) {
    if (actuator == NULL) {
        return;
    }
    actuator->setA(paramA);
    actuator->setB(paramB);
    actuator->setw1(paramw1);
    actuator->setw2(paramw2);
    actuator->setFase(paramFase);

}