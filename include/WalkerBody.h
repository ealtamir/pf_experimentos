//
//  WalkerBody.h
//  test
//
//  Created by Enzo Altamiranda G on 05.08.15.
//  Copyright (c) 2015 Enzo Altamiranda G. All rights reserved.
//

#ifndef __test__WalkerBody__
#define __test__WalkerBody__

#include <stdio.h>
#include <math.h>
#include "Body.h"
#include "Chromosome.h"
#include "ValueSets.h"
 


const btScalar BODY_PART_QTY = 6;


class WalkerBody : public Body {
public:
    WalkerBody(btDynamicsWorld* world, BodyParameters &params);
    
    Chromosome::Representation::GaIntervalValueSet<double>** getMultiValueSet();
    
    virtual void setActuatorValues(std::vector<double> vals) = 0;
    
    BodyPart* getLowerLeftLeg();
    BodyPart* getUpperLeftLeg();
    BodyPart* getLowerRightLeg();
    BodyPart* getUpperRightLeg();
    
    int numberOfParams;
    
protected:
    
    virtual void initializeMultiValueSet() = 0;
    
    
    void initializeIntervalBounds();
    
    
    Chromosome::Representation::GaIntervalValueSet<double>** multiValueSet = nullptr;
    
    Chromosome::Representation::GaValueIntervalBounds<double>* amplitude;
    Chromosome::Representation::GaValueIntervalBounds<double>* frequency;
    Chromosome::Representation::GaValueIntervalBounds<double>* phase;
    Chromosome::Representation::GaValueIntervalBounds<double>* independentTerm;
    
    Chromosome::Representation::GaIntervalValueSet<double>* amplitudeValueSet;
    Chromosome::Representation::GaIntervalValueSet<double>* frequencyValueSet;
    Chromosome::Representation::GaIntervalValueSet<double>* phaseValueSet;
    Chromosome::Representation::GaIntervalValueSet<double>* independentTermValueSet;
    
};


#endif /* defined(__test__WalkerBody__) */
