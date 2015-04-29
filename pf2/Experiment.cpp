
#include "Experiment.h"
#include "GLDebugDrawer.h"
#include <BulletDynamics/btBulletDynamicsCommon.h>
#include <BulletCollision/Gimpact/btGImpactCollisionAlgorithm.h>
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
    
    btBroadphaseInterface* broadphase = new btDbvtBroadphase();
    btDefaultCollisionConfiguration* collision_config = new btDefaultCollisionConfiguration();
    btCollisionDispatcher* dispatcher = new btCollisionDispatcher(collision_config);
    btGImpactCollisionAlgorithm::registerAlgorithm(dispatcher);
    
    btSequentialImpulseConstraintSolver* solver = new btSequentialImpulseConstraintSolver();

    m_dynamicsWorld = new btDiscreteDynamicsWorld(dispatcher, broadphase, solver, collision_config);
    
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
    btCollisionShape* wallShape = new btBoxShape(btVector3(btScalar(40), btScalar(40), btScalar(1)));
    btTransform groundTransform;
    groundTransform.setIdentity();
    groundTransform.setOrigin(btVector3(-4, 10.5, -4));
    return localCreateRigidBody(btScalar(0), groundTransform, wallShape);
}

btRigidBody* Experiment::createBall()
{
    float radius = 2.;
    int mass = 1;
    btCollisionShape* sphereShape = new btSphereShape(radius);
    btTransform groundTransform;
    groundTransform.setIdentity();
    groundTransform.setOrigin(BALL_ORIGIN);
    return localCreateRigidBody(mass, groundTransform, sphereShape);
}

btRigidBody* Experiment::createCube()
{
    float size = 3;
    float sizeScalar = btScalar(size);
    float mass = 1;
    btCollisionShape* boxShape = new btBoxShape(btVector3(sizeScalar, sizeScalar, sizeScalar));
    btTransform boxTransform;
    boxTransform.setIdentity();
    boxTransform.setOrigin(btVector3(0, size, 0));
    return localCreateRigidBody(mass, boxTransform, boxShape);
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
        if (!objectsInitialized) {
            initObjects();
        }
        worldStep();
        m_dynamicsWorld->stepSimulation(1 / 60.);
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