#include "CosineDoubleFrecBodyParameters.h"
#include "CosineDoubleFrecActuator.h"

CosineDoubleFrecBodyParameters::CosineDoubleFrecBodyParameters() {
    rightLowerArmAct.push_back( new CosineDoubleFrecActuator());
    rightUpperArmAct.push_back( new CosineDoubleFrecActuator());
    
    leftLowerArmAct.push_back( new CosineDoubleFrecActuator());
    leftUpperArmAct.push_back( new CosineDoubleFrecActuator());
    
    hipAct.push_back( new CosineDoubleFrecActuator());
    
    rightLowerLegAct.push_back( new CosineDoubleFrecActuator());
    rightUpperLegAct.push_back( new CosineDoubleFrecActuator());
    
    leftLowerLegAct.push_back( new CosineDoubleFrecActuator(true));
    leftUpperLegAct.push_back( new CosineDoubleFrecActuator(true));
}

CosineDoubleFrecBodyParameters::~CosineDoubleFrecBodyParameters() {
}