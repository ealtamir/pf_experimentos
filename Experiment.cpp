
#include "Experiment.h"
#include "GLDebugDrawer.h"
#include <BulletDynamics/btBulletDynamicsCommon.h>
#include "test_constants.h"

GLDebugDrawer debugDrawerSphere;

Experiment::Experiment()
{
    startTime = time(0);
}

void Experiment::initPhysics()
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
    
    m_dynamicsWorld->setGravity(GRAVITY);
    m_dynamicsWorld->setDebugDrawer(&debugDrawerSphere);
    
    initializeBodies();

    clientResetScene();
}


btRigidBody* Experiment::createGround()
{
    btCollisionShape* groundShape = new btBoxShape(btVector3(btScalar(200.), btScalar(1.), btScalar(200.)));
    //    btCollisionShape* planeShape = new btStaticPlaneShape(btVector3(0, 1, 0), 1);
    btTransform groundTransform;
    groundTransform.setIdentity();
    groundTransform.setOrigin(btVector3(0, -0.5, 0));
    return localCreateRigidBody(btScalar(0.), groundTransform, groundShape);
}

btRigidBody* Experiment::createWall()
{
    btCollisionShape* wallShape = new btBoxShape(btVector3(btScalar(20), btScalar(20), btScalar(1)));
    btTransform groundTransform;
    groundTransform.setIdentity();
    groundTransform.setOrigin(btVector3(0, 10.5, 10));
    return localCreateRigidBody(btScalar(0), groundTransform, wallShape);
}

btRigidBody* Experiment::createBall()
{
    btCollisionShape* sphereShape = new btSphereShape(2.);
    btTransform groundTransform;
    groundTransform.setIdentity();
    groundTransform.setOrigin(btVector3(0, 20, -30));
    return localCreateRigidBody(1, groundTransform, sphereShape);
}

void Experiment::clientMoveAndDisplay()
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
        worldStep();
        m_dynamicsWorld->stepSimulation(ms / 1000000.);
        //optional but useful: debug drawing
        m_dynamicsWorld->debugDrawWorld();
    }
    
    renderme();
    
    glFlush();
    
    swapBuffers();
}

void Experiment::displayCallback()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    if (m_dynamicsWorld)
    {
        m_dynamicsWorld->debugDrawWorld();
        worldStep();
    }
    
    renderme();
    
    glFlush();
    swapBuffers();
}


void Experiment::keyboardCallback(unsigned char key, int x, int y)
{
    switch (key)
    {
        case ' ':
            objectsInitialized = false;
        default:
            DemoApplication::keyboardCallback(key, x, y);
    }
    
    
}