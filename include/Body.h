#ifndef BODY_H_INCLUDED
#define BODY_H_INCLUDED

#include <vector>
#include <BulletDynamics/btBulletDynamicsCommon>

class Body {

public:
	Body(btDynamicsWorld* world);
	virtual ~Body();

private:
	std::vector<BodyGroups*> bodyGroups;
	btDynamicsWorld* world;

};

#endif
