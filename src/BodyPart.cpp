#include "BodyPart.h"

BodyPart::~BodyPart() {
	delete body->getMotionState();
	delete body;
}

void BodyPart::actuate(double t, int stage) {
    if (actuator != nullptr) {
        body->applyTorque(actuator->eval(t, stage));
    }
}

//// Generic
void BodyPart::setActuatorValues(double sin_ampl, double cos_ampl, double sin_freq,
                                 double cos_freq, double phase, double indTerm) {
    if (actuator == NULL) {
        return;
    }
    double params[6] = {sin_ampl, cos_ampl, sin_freq, cos_freq, phase, indTerm};
    actuator->setParameters(params);

}

//// Fourier
//void BodyPart::setActuatorValues(double ampl1, double ampl2, double ampl3, double ampl4,
//                                 double freq, double phase, double indTerm) {
//    if (actuator == NULL) {
//        return;
//    }
//    double params[6] = {ampl1, ampl2, ampl3, ampl4, phase, indTerm};
//    actuator->setParameters(params);
//    
//}

// Double frec cos
//void BodyPart::setActuatorValues(double ampl1, double freq1, double freq2, double fase, double indTerm) {
//    if (actuator == NULL) {
//        return;
//    }
//    double params[5] = {ampl1, freq1, freq2, fase, indTerm};
//    actuator->setParameters(params);
//    
//}