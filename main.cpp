//
//  main.cpp
//  pf2
//
//  Created by Enzo Altamiranda G on 13.04.15.
//  Copyright (c) 2015 Enzo Altamiranda G. All rights reserved.
//

#include "BouncingBall.h"
#include "TranslatingCubeDemo.h"

int main(int argc,char* argv[])
{
    BouncingBall demoApp;
    //	demoApp.configDebugDrawer(&debugDrawer);
    
    demoApp.initPhysics();
    demoApp.setCameraDistance(btScalar(80.));
    demoApp.setCameraForwardAxis(0 );
//    demoApp.setCameraUp(btVector3(10, 50, -10));
    
    return glutmain(argc, argv, 1024, 768,"Translating Cube",&demoApp);
    
}
