#ifndef LEGBODYGROUP_H_DEFINED
#define LEGBODYGROUP_H_DEFINED

#include "BodyGroup.h"

class LegBodyGroup : public BodyGroup {
  
public:
    LegBodyGroup(btDynamicsWorld* world,
                 double multiplier = 1.0,
                 const btVector3 positionAdjust = btVector3(1, 1, 1),
                 const btVector3 positionOffset = btVector3(0, 20, 0));
    
    BodyPart* getJointPart();
    
private:
    btGeneric6DofConstraint*
    joinLegParts(BodyPart* upperLeg,
                 BodyPart* lowerLeg,
                 double multiplier);
    
    btGeneric6DofConstraint*
    createAnkle(BodyPart* lowerLeg,
                BodyPart* ankle,
                double multiplier);
    
    
    const double LOWER_LEG_R = 0.05, LOWER_LEG_H = 0.37, LOWER_LEG_M = 1;
    const double UPPER_LEG_R = 0.07, UPPER_LEG_H = 0.45, UPPER_LEG_M = 1;
    const double FOOT_R = 0.05, FOOT_H = 0.15, FOOT_M = 1;
};

#endif
