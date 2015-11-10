#include "GenericBody.h"
#include "BodyGroup.h"
#include "ArmBodyGroup.h"
#include "LegBodyGroup.h"
#include "TorsoBodyGroup.h"
#include "ConstraintBuilder.h"
#include "GenericActuator.h"


GenericBody::GenericBody(btDynamicsWorld* world, BodyParameters& params) : WalkerBody(world, params) {
    
}


void GenericBody::initializeMultiValueSet() {
    multiValueSet = new Chromosome::Representation::GaIntervalValueSet<double>*[numberOfParams];
    
    multiValueSet[0] = amplitudeValueSet;
    multiValueSet[1] = amplitudeValueSet;
    multiValueSet[2] = frequencyValueSet;
    multiValueSet[3] = frequencyValueSet;
    multiValueSet[4] = phaseValueSet;
    multiValueSet[5] = independentTermValueSet;
    
    multiValueSet[6] = amplitudeValueSet;
    multiValueSet[7] = amplitudeValueSet;
    multiValueSet[8] = frequencyValueSet;
    multiValueSet[9] = frequencyValueSet;
    multiValueSet[10] = phaseValueSet;
    multiValueSet[11] = independentTermValueSet;
    
}

void GenericBody::setActuatorValues(const std::vector<double>& vals) {
    
    GenericActuator* actuator;
    double values[30] = {
        vals[0], vals[1], vals[2], vals[3], vals[4], vals[5],
        vals[6], vals[7], vals[8], vals[9], vals[10], vals[11]
    };
    
    BodyPart* leftLowerLeg = getLowerLeftLeg();
    actuator = dynamic_cast<GenericActuator*>(leftLowerLeg->getActuator());
    actuator->setActuatorValues(values);
    
    BodyPart* leftUpperLeg = getUpperLeftLeg();
    actuator = dynamic_cast<GenericActuator*>(leftUpperLeg->getActuator());
    actuator->setActuatorValues(values);
    
    BodyPart* rightLowerLeg = getUpperRightLeg();
    actuator = dynamic_cast<GenericActuator*>(rightLowerLeg->getActuator());
    actuator->setActuatorValues(&values[6]);
    
    BodyPart* rightUpperLeg = getUpperRightLeg();
    actuator = dynamic_cast<GenericActuator*>(rightUpperLeg->getActuator());
    actuator->setActuatorValues(&values[6]);
    
}