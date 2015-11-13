
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

void Experiment::setBodyActuatorValues(std::vector<double> vals) {
    
    BodyPart* bodyPart;
    
    int LEFT_LEG = 0;
    int RIGHT_LEG = 1;
    
    int LOWER_LEG = 0;
    int UPPER_LEG = 1;
//        // Generic
//        // left lower leg
        bodyPart = selectedBody->getBodyGroups()[LEFT_LEG]->getBodyParts()[LOWER_LEG];
        bodyPart->setActuatorValues(vals[0], vals[1], vals[2], vals[3], vals[4], vals[5]);
    
        // left upper leg
        bodyPart = selectedBody->getBodyGroups()[LEFT_LEG]->getBodyParts()[UPPER_LEG];
        bodyPart->setActuatorValues(vals[6], vals[7], vals[8], vals[9], vals[10], vals[11]);
    
        // right lower leg
        bodyPart = selectedBody->getBodyGroups()[RIGHT_LEG]->getBodyParts()[LOWER_LEG];
        bodyPart->setActuatorValues(vals[0], vals[1], vals[2], vals[3], vals[4] + SIMD_PI, vals[5]);
    
        // right upper leg
        bodyPart = selectedBody->getBodyGroups()[RIGHT_LEG]->getBodyParts()[UPPER_LEG];
        bodyPart->setActuatorValues(vals[6], vals[7], vals[8], vals[9], vals[10] + SIMD_PI, vals[11]);
    
    //    // Fourier
    //    // left lower leg
//        bodyPart = body->getBodyGroups()[LEFT_LEG]->getBodyParts()[LOWER_LEG];
//        bodyPart->setActuatorValues(vals[0], vals[1], vals[2], vals[3], vals[4], vals[5], vals[6]);
//    
//        // left upper leg
//        bodyPart = body->getBodyGroups()[LEFT_LEG]->getBodyParts()[UPPER_LEG];
//        bodyPart->setActuatorValues(vals[7], vals[8], vals[9], vals[10], vals[11], vals[12], vals[13]);
//    
//        // right lower leg
//        bodyPart = body->getBodyGroups()[RIGHT_LEG]->getBodyParts()[LOWER_LEG];
//        bodyPart->setActuatorValues(vals[0], vals[1], vals[2], vals[3], vals[4], vals[5] + SIMD_PI, vals[6]);
//    
//        // right upper leg
//        bodyPart = body->getBodyGroups()[RIGHT_LEG]->getBodyParts()[UPPER_LEG];
//        bodyPart->setActuatorValues(vals[7], vals[8], vals[9], vals[10], vals[11], vals[12] + SIMD_PI, vals[13]);
    
    
//    // Double frec cos
//    // left lower leg
//    bodyPart = body->getBodyGroups()[LEFT_LEG]->getBodyParts()[LOWER_LEG];
//    bodyPart->setActuatorValues(vals[0], vals[1], vals[2], vals[3], vals[4]);
//    
//    // left upper leg
//    bodyPart = body->getBodyGroups()[LEFT_LEG]->getBodyParts()[UPPER_LEG];
//    bodyPart->setActuatorValues(vals[5], vals[6], vals[7], vals[8], vals[9]);
//    
//    // right lower leg
//    bodyPart = body->getBodyGroups()[RIGHT_LEG]->getBodyParts()[LOWER_LEG];
//    bodyPart->setActuatorValues(vals[0], vals[1], vals[2], vals[3] + SIMD_PI, vals[4]);
//    
//    // right upper leg
//    bodyPart = body->getBodyGroups()[RIGHT_LEG]->getBodyParts()[UPPER_LEG];
//    bodyPart->setActuatorValues(vals[5], vals[6], vals[7], vals[8] + SIMD_PI, vals[9]);
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
    info.m_numIterations = 60;
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
    return localCreateRigidBody(btScalar(0.), groundTransform, groundShape);
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
            timeCount = 0;
            initObjects();
        }
        worldStep();

        //optional but useful: debug drawing
//        m_dynamicsWorld->debugDrawWorld();
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
