//
//  WalkerBody.cpp
//  test
//
//  Created by Enzo Altamiranda G on 05.08.15.
//  Copyright (c) 2015 Enzo Altamiranda G. All rights reserved.
//

#include "WalkerBody.h"
#include "GenericTorsoBodyGroup.h"
#include "LegBodyGroup.h"
#include "Initialization.h"


WalkerBody::WalkerBody(btDynamicsWorld* world, BodyParameters &params) : Body(world) {
    
    initializeIntervalBounds();

    BodyGroup* leftLeg = createLeftLeg(world, params);
    BodyGroup* rightLeg = createRightLeg(world, params);
    BodyGroup* torso = createTorso(world, params);
    
    GenericTorsoBodyGroup* torsoGroup = dynamic_cast<GenericTorsoBodyGroup*>(torso);

    createLeftHip(leftLeg->getJointPart(),
                  torsoGroup->getLeftHipPart(),
                  params);
    createRightHip(rightLeg->getJointPart(),
                   torsoGroup->getRightHipPart(),
                   params);
}

Chromosome::Representation::GaIntervalValueSet<double>**
WalkerBody::getMultiValueSet() {
    if (multiValueSet == nullptr) {
        initializeMultiValueSet();
    }
    return multiValueSet;
}

void WalkerBody::initializeIntervalBounds() {

    Chromosome::Representation::GaValueIntervalBounds<double> amplitude(-80, 80);
    Chromosome::Representation::GaValueIntervalBounds<double> frequency(0.01, 5);
    Chromosome::Representation::GaValueIntervalBounds<double> phase(0, SIMD_PI);
    Chromosome::Representation::GaValueIntervalBounds<double> independentTerm(-5, 5);
    
    amplitudeValueSet = new Chromosome::Representation::GaIntervalValueSet<double>(amplitude, amplitude, GaGlobalRandomDoubleGenerator, false);
    
    frequencyValueSet = new Chromosome::Representation::GaIntervalValueSet<double>(frequency, frequency, GaGlobalRandomDoubleGenerator, false);
    
    phaseValueSet = new Chromosome::Representation::GaIntervalValueSet<double>(phase, phase, GaGlobalRandomDoubleGenerator, false);
    
    independentTermValueSet = new Chromosome::Representation::GaIntervalValueSet<double>(independentTerm, independentTerm, GaGlobalRandomDoubleGenerator, false);
}

BodyPart* WalkerBody::getLowerLeftLeg() {
    return bodyGroups[0]->getBodyParts()[0];
}

BodyPart* WalkerBody::getUpperLeftLeg() {
    return bodyGroups[0]->getBodyParts()[1];
}

BodyPart* WalkerBody::getLowerRightLeg() {
    return bodyGroups[1]->getBodyParts()[0];
}

BodyPart* WalkerBody::getUpperRightLeg() {
    return bodyGroups[1]->getBodyParts()[0];
}

