#ifndef CAPSULEBODYPART_H_INCLUDED
#define CAPSULEBODYPART_H_INCLUDED

#include <vector>
#include "BodyPart.h"

class CapsuleBodyPart : public BodyPart {

public:
    
	CapsuleBodyPart(btScalar radius, btScalar height,
			btScalar mass, const btTransform& transform, btVector3 centerOfMass);
    
    CapsuleBodyPart(btScalar r, btScalar h, btScalar m, const btTransform &trans, std::vector<Actuator*> actuator, btVector3 centerOfMass);
};

#endif
