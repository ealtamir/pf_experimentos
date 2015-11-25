#ifndef __proyecto_pf__CosineDoubleFrecActuator__
#define __proyecto_pf__CosineDoubleFrecActuator__

#include <stdio.h>
#include "Actuator.h"

class CosineDoubleFrecActuator : public Actuator {
    
public:    
    virtual void setActuatorValues(double vals[]);
    
    virtual void setActuatorValues(double vals1[], double vals2[]);
    
    virtual Actuator* clone();
    
protected:
    virtual btVector3 actuatorFunc(double t, int stage);
};

#endif /* defined(__proyecto_pf__CosineDoubleFrecActuator__) */
