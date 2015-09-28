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
void BodyPart::setActuatorValues(double sin_ampl, double sin_freq, double cos_ampl,
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
//void BodyPart::setActuatorValues(double stage_0_ampl1, double stage_0_freq1, double stage_0_freq2,
//                                 double stage_0_fase, double stage_0_indTerm,
//                                 double stage_1_ampl1, double stage_1_freq1, double stage_1_freq2,
//                                 double stage_1_fase, double stage_1_indTerm) {
//    if (actuator == NULL) {
//        return;
//    }
//    double params[10] = {stage_0_ampl1, stage_0_freq1, stage_0_freq2, stage_0_fase, stage_0_indTerm,
//                         stage_1_ampl1, stage_1_freq1, stage_1_freq2, stage_1_fase, stage_1_indTerm};
//    actuator->setParameters(params);
//    
//}