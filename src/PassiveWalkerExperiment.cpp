#include "PassiveWalkerExperiment.h"

PassiveWalkerExperiment::PassiveWalkerExperiment() {
}

PassiveWalkerExperiment::~PassiveWalkerExperiment() {
	delete body;
}

void PassiveWalkerExperiment::initializeBodies() {
	body = new PassiveWalkerBody(m_dynamicsWorld);
}

void PassiveWalkerExperiment::initObjects() {
	objectsInitialized = true;
}

void PassiveWalkerExperiment::worldStep() {
	// TODO
}

bool PassiveWalkerExperiment::stopExperiment() {
	return false;
}
