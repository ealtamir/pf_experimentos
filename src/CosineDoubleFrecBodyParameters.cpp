#include "CosineDoubleFrecBodyParameters.h"
#include "CosineDoubleFrecActuator.h"
#include "MetaActuator.h"

CosineDoubleFrecBodyParameters::CosineDoubleFrecBodyParameters(Actuator *firstStepActuator) {
    rightLowerArmAct = new MetaActuator(firstStepActuator->clone(), new CosineDoubleFrecActuator());
    rightUpperArmAct = new MetaActuator(firstStepActuator->clone(), new CosineDoubleFrecActuator());
    
    leftLowerArmAct = new MetaActuator(firstStepActuator->clone(), new CosineDoubleFrecActuator());
    leftUpperArmAct = new MetaActuator(firstStepActuator->clone(), new CosineDoubleFrecActuator());
    
    hipAct = new MetaActuator(firstStepActuator->clone(), new CosineDoubleFrecActuator());
    
    rightLowerLegAct = new MetaActuator(firstStepActuator->clone(), new CosineDoubleFrecActuator());
    rightUpperLegAct = new MetaActuator(firstStepActuator->clone(), new CosineDoubleFrecActuator());
    
    leftLowerLegAct = new MetaActuator(firstStepActuator->clone(), new CosineDoubleFrecActuator());
    leftUpperLegAct = new MetaActuator(firstStepActuator->clone(), new CosineDoubleFrecActuator());
}

CosineDoubleFrecBodyParameters::~CosineDoubleFrecBodyParameters() {
}