#include "GenericBody.h"
#include "BodyGroup.h"
#include "ArmBodyGroup.h"
#include "LegBodyGroup.h"
#include "TorsoBodyGroup.h"
#include "ConstraintBuilder.h"
#include "GenericActuator.h"


GenericBody::GenericBody(btDynamicsWorld* world, BodyParameters& params) : WalkerBody(world, params) {
    numberOfParams = 12;
}

void GenericBody::setActuatorValues(int index, std::vector<double> vals) {
    if(index!=0){
        return;
    }
    GenericActuator* actuator;
    double values[30] = {
        vals[0], vals[1], vals[2], vals[3], vals[4], vals[5],
        vals[6], vals[7], vals[8], vals[9], vals[10], vals[11]
    };
    
    BodyPart* leftLowerLeg = getLowerLeftLeg();
    actuator = dynamic_cast<GenericActuator*>(leftLowerLeg->getActuator(index));
    actuator->setActuatorValues(values);
    
    BodyPart* leftUpperLeg = getUpperLeftLeg();
    actuator = dynamic_cast<GenericActuator*>(leftUpperLeg->getActuator(index));
    actuator->setActuatorValues(&values[6]);

    values[4] += SIMD_PI;
    values[10] += SIMD_PI;
    
    BodyPart* rightLowerLeg = getLowerRightLeg();
    actuator = dynamic_cast<GenericActuator*>(rightLowerLeg->getActuator(index));
    actuator->setActuatorValues(values);
    
    BodyPart* rightUpperLeg = getUpperRightLeg();
    actuator = dynamic_cast<GenericActuator*>(rightUpperLeg->getActuator(index));
    actuator->setActuatorValues(&values[6]);
    
}