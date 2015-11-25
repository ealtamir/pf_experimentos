#include "FourierBodyParameters.h"
#include "FourierActuator.h"
#include "PassiveWalkerExperiment.h"
#include "MetaActuator.h"


FourierBodyParameters::FourierBodyParameters(Actuator *firstStepActuator) {
    rightLowerArmAct = new MetaActuator(firstStepActuator->clone(), new FourierActuator());
    rightUpperArmAct = new MetaActuator(firstStepActuator->clone(), new FourierActuator());
    
    leftLowerArmAct = new MetaActuator(firstStepActuator->clone(), new FourierActuator());
    leftUpperArmAct = new MetaActuator(firstStepActuator->clone(), new FourierActuator());
    
    hipAct = new MetaActuator(firstStepActuator->clone(), new FourierActuator());
    
    rightLowerLegAct = new MetaActuator(firstStepActuator->clone(), new FourierActuator());
    rightUpperLegAct = new MetaActuator(firstStepActuator->clone(), new FourierActuator());
    
    leftLowerLegAct = new MetaActuator(firstStepActuator->clone(), new FourierActuator());
    leftUpperLegAct = new MetaActuator(firstStepActuator->clone(), new FourierActuator());
}

FourierBodyParameters::~FourierBodyParameters() {
}