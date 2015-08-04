//
//  GenericActuator.cpp
//  test
//
//  Created by Enzo Altamiranda G on 04.08.15.
//  Copyright (c) 2015 Enzo Altamiranda G. All rights reserved.
//

#include "GenericActuator.h"


GenericActuator::GenericActuator() {
    
}

btVector3
GenericActuator::actuatorFunc(double t) {
    
    return btVector3(0, 0, 0);
}