#ifndef ARMBODYGROUP_H_INCLUDED
#define ARMBODYGROUP_H_INCLUDED

#include "BodyGroup.h"
#include "BodyParameters.h"

class ArmBodyGroup : public BodyGroup {

public:
	ArmBodyGroup(btDynamicsWorld* world,
                 BodyParameters &params,
                 const btVector3& posAdjust = btVector3(1, 1, 1));
    
    BodyPart* getJointPart();
    
private:
    btGeneric6DofConstraint*
    joinArmParts(BodyPart* upperArm, BodyPart* lowerArm, BodyParameters &params);

};

#endif
