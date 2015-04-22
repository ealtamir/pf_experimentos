//
//  BouncingBall.cpp
//  pf2
//
//  Created by Enzo Altamiranda G on 15.04.15.
//  Copyright (c) 2015 Enzo Altamiranda G. All rights reserved.
//

#include "BouncingBall.h"
#include "GLDebugDrawer.h"
#include <BulletDynamics/btBulletDynamicsCommon.h>

GLDebugDrawer debugDrawerSphere;

void BouncingBall::initPhysics()
{
    setTexturing(true);
    setShadows(true);
    
    btDefaultCollisionConfiguration* collision_config = new btDefaultCollisionConfiguration();
    btCollisionDispatcher* dispatcher = new btCollisionDispatcher(collision_config);
    
    btVector3 worldAabbMin(-10000, -10000, -10000);
    btVector3 worldAabbMax(10000, 10000, 10000);
    
    btBroadphaseInterface* overlappingPairCache = new btAxisSweep3(worldAabbMin, worldAabbMax);
    
    btConstraintSolver* constraintSolver = new btSequentialImpulseConstraintSolver;
    
    m_dynamicsWorld = new btDiscreteDynamicsWorld(dispatcher, overlappingPairCache, constraintSolver, collision_config);
    
    btVector3 gravity(0, -10, 0);
    
    m_dynamicsWorld->setGravity(gravity);
    m_dynamicsWorld->setDebugDrawer(&debugDrawerSphere);
    
    createGround();
    createWall();
    createBall();
    
    clientResetScene();
}

void BouncingBall::createGround()
{
    btCollisionShape* groundShape = new btBoxShape(btVector3(btScalar(200.), btScalar(1.), btScalar(200.)));
    //    btCollisionShape* planeShape = new btStaticPlaneShape(btVector3(0, 1, 0), 1);
    btTransform groundTransform;
    groundTransform.setIdentity();
    groundTransform.setOrigin(btVector3(0, -0.5, 0));
    btRigidBody* ground = localCreateRigidBody(btScalar(0.), groundTransform, groundShape);
    ground->setFriction(btScalar(.5));
}

void BouncingBall::createWall()
{
    btCollisionShape* wallShape = new btBoxShape(btVector3(btScalar(20), btScalar(20), btScalar(1)));
    btTransform groundTransform;
    groundTransform.setIdentity();
    groundTransform.setOrigin(btVector3(0, 10.5, 10));
    wall = localCreateRigidBody(btScalar(0), groundTransform, wallShape);
    wall->setFriction(btScalar(.5));
    wall->setRestitution(btScalar(.2));
}

void BouncingBall::createBall()
{
    btCollisionShape* sphereShape = new btSphereShape(2.);
    btTransform groundTransform;
    groundTransform.setIdentity();
    groundTransform.setOrigin(btVector3(0, 20, -30));
    ball = localCreateRigidBody(1, groundTransform, sphereShape);
    ball->setFriction(btScalar(.5));
    ball->setRestitution(btScalar(.5));

}

void BouncingBall::clientMoveAndDisplay()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    //simple dynamics world doesn't handle fixed-time-stepping
    float ms = getDeltaTimeMicroseconds();
    
    float minFPS = 1000000.f/60.f;
    if (ms > minFPS)
        ms = minFPS;
    
    if (m_dynamicsWorld)
    {
        initObjects();
        m_dynamicsWorld->stepSimulation(ms / 1000000.);
        //optional but useful: debug drawing
        m_dynamicsWorld->debugDrawWorld();
    }
    
    renderme();
    
    glFlush();
    
    swapBuffers();
}

void BouncingBall::displayCallback()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    if (m_dynamicsWorld)
        m_dynamicsWorld->debugDrawWorld();
    
    renderme();
    
    glFlush();
    swapBuffers();
}

void BouncingBall::initObjects() {
    if (objectsInitialized) {
        return;
    }
    ball->activate(true);
    ball->applyCentralImpulse(btVector3(0, 0, 50));
    objectsInitialized = true;
}

void BouncingBall::keyboardCallback(unsigned char key, int x, int y)
{
    switch (key)
    {
        case ' ':
            objectsInitialized = false;
        default:
            DemoApplication::keyboardCallback(key, x, y);
    }
    
    
}