#include "CosineDoubleFrecBodyParameters.h"
#include "CosineDoubleFrecActuator.h"

CosineDoubleFrecBodyParameters::CosineDoubleFrecBodyParameters() {
    rightLowerArmAct = new CosineDoubleFrecActuator();
    rightUpperArmAct = new CosineDoubleFrecActuator();
    
    leftLowerArmAct = new CosineDoubleFrecActuator();
    leftUpperArmAct = new CosineDoubleFrecActuator();
    
    hipAct = new CosineDoubleFrecActuator();
    
    rightLowerLegAct = new CosineDoubleFrecActuator();
    rightUpperLegAct = new CosineDoubleFrecActuator();
    
    leftLowerLegAct = new CosineDoubleFrecActuator();
    leftUpperLegAct = new CosineDoubleFrecActuator();
}

CosineDoubleFrecBodyParameters::~CosineDoubleFrecBodyParameters() {
}