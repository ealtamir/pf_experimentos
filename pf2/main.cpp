//
//  main.cpp
//  pf2
//
//  Created by Enzo Altamiranda G on 13.04.15.
//  Copyright (c) 2015 Enzo Altamiranda G. All rights reserved.
//


#include "GLDebugDrawer.h"
//#include "TranslatingCube.h"
#include "FallingBall.h"

int main(int argc,char* argv[])
{
    FallingBall demoApp;
    demoApp.enableStoppingCondition(false);
    
    //demoApp.configDebugDrawer(&debugDrawer);
    
    demoApp.initPhysics();
    demoApp.setCameraDistance(btScalar(60.));
//    demoApp.setCameraForwardAxis(0);
    demoApp.setCameraUp(btVector3(0, 10, 0));
    
    return glutmain(argc, argv, 1024, 768, "Experiment",&demoApp);
    
}
