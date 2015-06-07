#ifndef CAPSULEBODYPART_H_INCLUDED
#define CAPSULEBODYPART_H_INCLUDED

#include "BodyPart.h"

class CapsuleBodyPart : public BodyPart {

public:
	CapsuleBodyPart(btScalar radius, btScalar height,
			btScalar mass, const btVector3 origin);
	~CapsuleBodyPart();
};

#endif
