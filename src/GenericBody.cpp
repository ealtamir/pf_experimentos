#include "GenericBody.h"
#include "BodyGroup.h"
#include "ArmBodyGroup.h"
#include "LegBodyGroup.h"
#include "TorsoBodyGroup.h"
#include "ConstraintBuilder.h"


GenericBody::GenericBody(btDynamicsWorld* world, BodyParameters& params) : WalkerBody(world, params) {
    // Contains nothing
}
