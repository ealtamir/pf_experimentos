#ifndef __proyecto_pf__CosineDoubleFrecActuator__
#define __proyecto_pf__CosineDoubleFrecActuator__

#include <stdio.h>
#include "Actuator.h"

class CosineDoubleFrecActuator : public Actuator {
    
public:
    CosineDoubleFrecActuator(bool isLeft = false);
    
    virtual void setActuatorValues(double vals[]);
    
    virtual bool isFirstStep(double t);
    
protected:
    virtual btVector3 actuatorFunc(double t, int stage);
};

#endif /* defined(__proyecto_pf__CosineDoubleFrecActuator__) */
