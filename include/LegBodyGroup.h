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
    
    // retorna un array en donde el primero es lower y el segundo es upper y el tercero es foot
    double* getAngles();
    
private:
    double angles[3];
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
