#include "FourierBodyParameters.h"
#include "FourierActuator.h"
#include "PassiveWalkerExperiment.h"


FourierBodyParameters::FourierBodyParameters() {
    rightLowerArmAct = new FourierActuator();
    rightUpperArmAct = new FourierActuator();
    
    leftLowerArmAct = new FourierActuator();
    leftUpperArmAct = new FourierActuator();
    
    hipAct = new FourierActuator();
    
    rightLowerLegAct = new FourierActuator();
    rightUpperLegAct = new FourierActuator();
    
    leftLowerLegAct = new FourierActuator();
    leftUpperLegAct = new FourierActuator();
}

FourierBodyParameters::~FourierBodyParameters() {
}