//
//  TranslatingCubeDemo.cpp
//  pf2
//
//  Created by Enzo Altamiranda G on 14.04.15.
//  Copyright (c) 2015 Enzo Altamiranda G. All rights reserved.
//

#include "TranslatingCubeDemo.h"
#include "GLDebugDrawer.h"
#include <BulletDynamics/btBulletDynamicsCommon.h>

GLDebugDrawer debugDrawerCube;
float counter = 0;

void TranslatingCubeDemo::initPhysics()
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
    m_dynamicsWorld->setDebugDrawer(&debugDrawerCube);
    
    createGround();
    createBox();
    
    clientResetScene();
    
    initTime = time(NULL);
}

void TranslatingCubeDemo::createGround()
{
    btCollisionShape* groundShape = new btBoxShape(btVector3(btScalar(200.), btScalar(1.), btScalar(200.)));
//    btCollisionShape* planeShape = new btStaticPlaneShape(btVector3(0, 1, 0), 1);
    btTransform groundTransform;
    groundTransform.setIdentity();
    groundTransform.setOrigin(btVector3(0, -0.5, 0));
    btRigidBody* ground = localCreateRigidBody(btScalar(0.), groundTransform, groundShape);
    ground->setFriction(btScalar(.5));
}

void TranslatingCubeDemo::createBox()
{
    float size = 5.;
    float sizeScalar = btScalar(size);
    btCollisionShape* boxShape = new btBoxShape(btVector3(sizeScalar, sizeScalar, sizeScalar));
//    btCollisionShape* boxShape = new btSphereShape(size/2);
    btTransform boxTransform;
    boxTransform.setIdentity();
    boxTransform.setOrigin(btVector3(-50, size + .5, 0));
    this->box = localCreateRigidBody(btScalar(1.5), boxTransform, boxShape);
    box->setFriction(btScalar(.5));
}

void TranslatingCubeDemo::clientMoveAndDisplay()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    float ms = getDeltaTimeMicroseconds();
    
    float minFPS = 100000.f/60.f;
    if (ms > minFPS)
    {
        ms = minFPS;
    }
    
    time_t currentTime = time(NULL) - initTime;
    
    
    if (m_dynamicsWorld) {
        btVector3 oldForces = box->getTotalForce();

        if (currentTime < 10) {
            box->applyCentralForce(btVector3(10, 0, 0));
        } else if (currentTime > 20) {
            exit(0);
        }
        btVector3 speed = box->getLinearVelocity();
        btVector3 forces = box->getTotalForce();
        btVector3 center = box->getCenterOfMassPosition();
        
        if (currentTime == counter) {
            counter += 1;
            printf("t = %ds\n", (int) currentTime);
            printf("v: %f\n", speed.getX());
            printf("x: %f\n", center.getX());
        }

        m_dynamicsWorld->stepSimulation(1 / 60., 1);
//        m_dynamicsWorld->stepSimulation(1 / 60.);
        m_dynamicsWorld->debugDrawWorld();
    }
    
    renderme();
    glFlush();
    swapBuffers();
}

void TranslatingCubeDemo::displayCallback()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    if (m_dynamicsWorld)
        m_dynamicsWorld->debugDrawWorld();
    
    renderme();
    
    glFlush();
    swapBuffers();
}
