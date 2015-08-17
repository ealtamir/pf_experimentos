#ifndef LEGBODYGROUP_H_DEFINED
#define LEGBODYGROUP_H_DEFINED

#include "BodyGroup.h"
#include "BodyParameters.h"

class LegBodyGroup : public BodyGroup {
  
public:
    LegBodyGroup(btDynamicsWorld* world,
                 BodyParameters &params,
                 const btVector3 positionAdjust = btVector3(1, 1, 1),
                 bool isLeft = false);
    
    BodyPart* getJointPart();
    
private:
    btGeneric6DofConstraint*
    joinLegParts(BodyPart* upperLeg,
                 BodyPart* lowerLeg,
                 BodyParameters &params);
    
    btGeneric6DofConstraint*
    createAnkle(BodyPart* lowerLeg,
                BodyPart* ankle,
                BodyParameters &params);
};

#endif
