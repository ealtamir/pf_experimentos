#include "GenericBody.h"
#include "BodyGroup.h"
#include "ArmBodyGroup.h"
#include "LegBodyGroup.h"
#include "TorsoBodyGroup.h"
#include "ConstraintBuilder.h"


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