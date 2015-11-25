#ifndef __test__MetaActuator__
#define __test__MetaActuator__

#include <stdio.h>
#include <BulletDynamics/btBulletDynamicsCommon.h>
#include "Actuator.h"

#define META_PARAMS_SIZE 50

class MetaActuator : public Actuator {
    
public:
    
    MetaActuator(Actuator *first, Actuator *second);
    
    btVector3 eval(double t, int stage);
    
    void setParameters(double *parameters);
    
    virtual void setActuatorValues(double vals[]);
    
    Actuator *first = nullptr;
    Actuator *second = nullptr;
    
    virtual Actuator* clone();
    
protected:
    double parameters[PARAMS_SIZE];
    
    virtual btVector3 actuatorFunc(double t, int stage);

};

#endif /* defined(__test__MetaActuator__) */
