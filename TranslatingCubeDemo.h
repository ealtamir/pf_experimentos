//
//  TranslatingCubeDemo.h
//  pf2
//
//  Created by Enzo Altamiranda G on 14.04.15.
//  Copyright (c) 2015 Enzo Altamiranda G. All rights reserved.
//

#ifndef pf2_TranslatingCubeDemo_h
#define pf2_TranslatingCubeDemo_h

#ifdef _WINDOWS
#include "Win32DemoApplication.h"
#define PlatformDemoApplication Win32DemoApplication
#else
#include "GlutDemoApplication.h"
#define PlatformDemoApplication GlutDemoApplication
#endif

#include <time.h>

class TranslatingCubeDemo : public PlatformDemoApplication
{
private:
    btRigidBody* box;
    
    time_t initTime;
    time_t prevTime;
    
public:
    void initPhysics();
    
    virtual void clientMoveAndDisplay();
    
    virtual void displayCallback();
    
private:
    void createGround();
    
    void createBox();
};

#endif
