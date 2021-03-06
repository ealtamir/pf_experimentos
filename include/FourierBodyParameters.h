#ifndef __test__FourierBodyParameters__
#define __test__FourierBodyParameters__

#include <stdio.h>
#include "BodyParameters.h"

class FourierBodyParameters : public BodyParameters {
    
public:
    FourierBodyParameters(Actuator *firstStepActuator);
    ~FourierBodyParameters();
};

#endif /* defined(__test__FourierBodyParameters__) */
