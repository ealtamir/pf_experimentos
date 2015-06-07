#include "GLDebugDrawer.h"
#include "PassiveWalkerExperiment.h"
//#include "TranslatingCube.h"
//#include "FallingBall.h"
//#include "GenericJointDemo.h"

int main(int argc,char* argv[])
{
    PassiveWalkerExperiment demoApp;
    demoApp.enableStoppingCondition(false);
    demoApp.initPhysics();
    demoApp.setCameraDistance(btScalar(20.));
    demoApp.setCameraUp(btVector3(0, 10, 0));
    return glutmain(argc, argv, 1024, 768, "Experiment",&demoApp);
}
