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

void BodyPart::setActuatorValues(double sin_ampl, double cos_ampl, double sin_freq,
                                 double cos_freq, double phase, double indTerm) {
    if (actuator == NULL) {
        return;
    }
    actuator->setA(sin_ampl);
    actuator->setB(cos_ampl);
    actuator->setw1(sin_freq);
    actuator->setw2(cos_freq);
    actuator->setFase(phase);
    actuator->setIndTerm(indTerm);

}