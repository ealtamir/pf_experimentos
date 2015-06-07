#ifndef BODYGROUP_H_INCLUDED
#define BODYGROUP_H_INCLUDED

#include <vector>
#include <BulletDynamics/btBulletDynamicsCommon>

class BodyGroup {

public:
	BodyGroup();
	~BodyGroup();

private:
	std::vector<BodyPart*> bodyParts;

	void addRigidBodiesToWorld(btDynamicWorld* world);

};

#endif
