//
//  BouncingBall.h
//  pf2
//
//  Created by Enzo Altamiranda G on 15.04.15.
//  Copyright (c) 2015 Enzo Altamiranda G. All rights reserved.
//

#ifndef __pf2__BouncingBall__
#define __pf2__BouncingBall__

#ifdef _WINDOWS
#include "Win32DemoApplication.h"
#define PlatformDemoApplication Win32DemoApplication
#else
#include "GlutDemoApplication.h"
#define PlatformDemoApplication GlutDemoApplication
#endif

#include <stdio.h>

class BouncingBall : public PlatformDemoApplication
{
private:
    btRigidBody* ball;
    btRigidBody* wall;
    bool objectsInitialized = false;
    
public:
    void initPhysics();
    
    virtual void clientMoveAndDisplay();
    
    virtual void displayCallback();
    
private:
    
    void keyboardCallback(unsigned char key, int x, int y);
    
    void createGround();
    
    void createWall();
    
    void createBall();
    
    void initObjects();
};

#endif /* defined(__pf2__BouncingBall__) */
