#include "PassiveWalkerExperiment.h"
#include "GenericBodyParameters.h"

PassiveWalkerExperiment::PassiveWalkerExperiment() {
}

PassiveWalkerExperiment::~PassiveWalkerExperiment() {
	delete body;
    delete params;
}

void PassiveWalkerExperiment::initializeBodies() {
    params = new GenericBodyParameters();
    body = new WalkerBody(m_dynamicsWorld, *params);
}

void PassiveWalkerExperiment::initObjects() {
	objectsInitialized = true;
}

void PassiveWalkerExperiment::worldStep() {
    timeCount += 1. / 60.;
    body->actuate(timeCount);
}

bool PassiveWalkerExperiment::stopExperiment() {
	return false;
}
