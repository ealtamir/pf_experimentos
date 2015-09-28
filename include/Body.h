#ifndef BODY_H_INCLUDED
#define BODY_H_INCLUDED

#include <vector>
#include <BulletDynamics/btBulletDynamicsCommon.h>
#include "BodyGroup.h"
#include "ConstraintBuilder.h"


class Body : public ConstraintBuilder {

public:
	Body(btDynamicsWorld* world);
	virtual ~Body();
    
    void actuate(double t, int stage);
    std::vector<BodyGroup*> getBodyGroups();


protected:
	std::vector<BodyGroup*> bodyGroups;
    std::vector<btTypedConstraint*> constraints;
    
	btDynamicsWorld* world;
};

#endif
