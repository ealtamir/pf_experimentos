#ifndef ARMBODYGROUP_H_INCLUDED
#define ARMBODYGROUP_H_INCLUDED

#include "BodyGroup.h"

class ArmBodyGroup : public BodyGroup {

public:
	ArmBodyGroup(btDynamicsWorld* world, double multiplier = 1.0,
			const btVector3& positionOffset = btVector3(0, 20, 0));
    
    BodyPart* getJointPart();
    
private:
    btGeneric6DofConstraint*
    joinArmParts(BodyPart* upperArm, BodyPart* lowerArm, double multiplier);
    
    BodyPart*
    generateArmPart(const double r,
                    const double h,
                    const double m,
                    const btVector3& positionOffset);

    // radius, height and mass
    const double LOWER_ARM_R = 0.04, LOWER_ARM_H = 0.25,LOWER_ARM_M = 1.0;
    const double UPPER_ARM_R = 0.05, UPPER_ARM_H = 0.33,
        UPPER_ARM_M = 1.0;
};

#endif
