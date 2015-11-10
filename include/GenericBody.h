#ifndef GENERICBODY_H_INCLUDED
#define GENERICBODY_H_INCLUDED

#include "WalkerBody.h"
#include "BodyParameters.h"




class GenericBody : public WalkerBody {


public:
	GenericBody(btDynamicsWorld* world, BodyParameters &params);

};
#endif
