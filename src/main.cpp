#include "GLDebugDrawer.h"
#include "PassiveWalkerExperiment.h"
//#include "TranslatingCube.h"
//#include "FallingBall.h"
//#include "GenericJointDemo.h"

int mainLoop(Experiment*);

int main(int argc,char* argv[])
{
    PassiveWalkerExperiment demoApp;
    demoApp.enableStoppingCondition(false);
    demoApp.initPhysics();
    demoApp.setCameraDistance(btScalar(7.));
    demoApp.setCameraUp(btVector3(0, 10, 0));
    return mainLoop(&demoApp);
    //return glutmain(argc, argv, 1024, 768, "Experiment",&demoApp);
}

int mainLoop(Experiment* demoApp)
{
    demoApp->initPhysics();
    for (; ; ) {
        demoApp->worldStep();
    }
    //demoApp->stopExperiment();
    return 0;
}
