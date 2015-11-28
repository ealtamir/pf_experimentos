
#include "Experiment.h"
#include "GLDebugDrawer.h"
#include <BulletDynamics/btBulletDynamicsCommon.h>
#include <BulletCollision/Gimpact/btGImpactCollisionAlgorithm.h>
#include "test_constants.h"
#include <BulletCollision/CollisionShapes/btMultiSphereShape.h>
#include "BodyPart.h"

GLDebugDrawer debugDrawerSphere;

Experiment::Experiment() {
    // Does Nothing
}

Experiment::~Experiment() {

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

    btContactSolverInfo& info = m_dynamicsWorld->getSolverInfo();

//     This is related to the number of iterations performed
//     by the collision solver algorithm.
    info.m_numIterations = 50;
//
//     If set to 1, it doesn't solve collision between objects in pairs, so when bouncing
//     there isn't any energy added.
    info.m_splitImpulse = 1;


    m_dynamicsWorld->setGravity(btVector3(0, -10, 0));

    createGround();
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
    btRigidBody* floor = localCreateRigidBody(btScalar(0.), groundTransform, groundShape);
    floor->setFriction(1);
    return floor;
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
            timeCount = 0;
        } 
        worldStep();
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
