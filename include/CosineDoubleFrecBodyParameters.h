#ifndef __test__CosineDoubleFrecBodyParameters__
#define __test__CosineDoubleFrecBodyParameters__

#include <stdio.h>
#include "BodyParameters.h"

class CosineDoubleFrecBodyParameters : public BodyParameters {
    
public:
    CosineDoubleFrecBodyParameters(Actuator *firstStepActuator);
    ~CosineDoubleFrecBodyParameters();
};

#endif /* defined(__test__CosineDoubleFrecBodyParameters__) */
