//
//  GenericActuator.h
//  test
//
//  Created by Enzo Altamiranda G on 04.08.15.
//  Copyright (c) 2015 Enzo Altamiranda G. All rights reserved.
//

#ifndef __test__GenericActuator__
#define __test__GenericActuator__

#include <stdio.h>
#include "Actuator.h"

class GenericActuator : public Actuator {
    
public:
    GenericActuator(bool isLeft = false);
    
    void setA(double valueA);
    void setB(double valueB);
    void setw1(double valuew1);
    void setw2(double valuew2);
    void setFase(double valueFase);
    void setIndTerm(double value);

    
protected:
    btVector3 actuatorFunc(double t);
    
    double sin_amplitude;
    double cos_amplitude;
    double sin_freq;
    double cos_freq;
    double fase;
    double C;
    
};

#endif /* defined(__test__GenericActuator__) */
