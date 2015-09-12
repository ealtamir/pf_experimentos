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
    
protected:
    btVector3 actuatorFunc(double t);
    
    double A;
    double B;
    double w1;
    double w2;
    double fase;
    
};

#endif /* defined(__test__GenericActuator__) */
