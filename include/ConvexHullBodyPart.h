//
//  ConvexHullBodyPart.h
//  Prueba2
//
//  Created by Tomas Mehdi on 8/5/15.
//  Copyright (c) 2015 Tomas Mehdi. All rights reserved.
//

#ifndef Prueba2_ConvexHullBodyPart_h
#define Prueba2_ConvexHullBodyPart_h

#include "BodyPart.h"
#include <LinearMath/btVector3.h>

class ConvexHullBodyPart : public BodyPart {
    
public:
    ConvexHullBodyPart(btVector3 points[], btScalar mass, const btTransform& transform);
};

#endif
