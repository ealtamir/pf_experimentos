#include "FourierBodyParameters.h"
#include "FourierActuator.h"


FourierBodyParameters::FourierBodyParameters() {
    rightLowerArmAct.push_back(new FourierActuator());
    rightUpperArmAct.push_back( new FourierActuator());
    
    leftLowerArmAct.push_back( new FourierActuator());
    leftUpperArmAct.push_back( new FourierActuator());
    
    hipAct.push_back( new FourierActuator());
    
    rightLowerLegAct.push_back( new FourierActuator());
    rightUpperLegAct.push_back( new FourierActuator());
    
    leftLowerLegAct.push_back( new FourierActuator(true));
    leftUpperLegAct.push_back( new FourierActuator(true));
}

FourierBodyParameters::~FourierBodyParameters() {
}