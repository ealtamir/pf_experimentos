#include "BodyPart.h"


BodyPart::~BodyPart() {
	delete body->getMotionState();
	delete body;
}

void
BodyPart::actuate(double t) {
    if (actuator != nullptr) {
        body->applyTorque(actuator->eval(t));
    }
}