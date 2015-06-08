#ifndef BODYPART_H_INCLUDED
#define BODYPART_H_INCLUDED

#include <BulletDynamics/btBulletDynamicsCommon.h>
#include <string>

class BodyPart {

public:
	virtual ~BodyPart();

	btRigidBody* getRigidBody() {return body;};

protected:
	btRigidBody* body;
	std::string identifier;

};


#endif
