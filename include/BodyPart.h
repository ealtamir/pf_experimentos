#ifndef BODYPART_H_INCLUDE
#define BODYPART_H_INCLUDE

#include <BulletDynamics/btBulletDynamicsCommon>
#include <string>

class BodyPart {

public:
	BodyPart();
	virtual ~BodyPart();

private:
	btRigidBody* body;
	std::string identifier;

	btRigidBody* getRigidBody() {return body;};
};


#endif
