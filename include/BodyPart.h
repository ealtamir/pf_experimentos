#ifndef BODYPART_H_INCLUDED
#define BODYPART_H_INCLUDED

#include <BulletDynamics/btBulletDynamicsCommon.h>
#include <string>
#include "Actuator.h"

const float LINEAR_DAMPING = 0.05;
const float ANGULAR_DAMPING = 0.85;
const float DEACTIVATION_TIME = 0.8;
const float LINEAR_SLEEPING_THRESHOLD = 1.6;
const float ANGULAR_SLEEPING_THRESHOLD = 2.5;

class BodyPart {

public:
	virtual ~BodyPart();

	btRigidBody* getRigidBody() {return body;};
    
    void actuate(double t);
    
    void setActuatorValues(double A, double B, double w1, double w2, double fase);

protected:
	btRigidBody* body;
    
	std::string identifier;
    
    Actuator* actuator = nullptr;

};


#endif
