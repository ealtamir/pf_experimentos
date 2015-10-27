
#define SHIFT_TRANSFORM 1
//#define CHANGE_COMPOUND_INPLACE 1
//#define USE_RECURSIVE_COMPOUND 1

///create 125 (5x5x5) dynamic object
#define ARRAY_SIZE_X 5
#define ARRAY_SIZE_Y 5
#define ARRAY_SIZE_Z 5

//maximum number of objects (and allow user to shoot additional boxes)
#define MAX_PROXIES (ARRAY_SIZE_X*ARRAY_SIZE_Y*ARRAY_SIZE_Z + 1024)

///scaling of the objects (0.1 = 20 centimeter boxes )
#define SCALING 1
#define START_POS_X -5
#define START_POS_Y -5
#define START_POS_Z -3

#include "BasicDemo.h"
#include "GlutStuff.h"
///btBulletDynamicsCommon.h is the main Bullet include file, contains most common include files.
#include <BulletDynamics/btBulletDynamicsCommon.h>
#include <stdio.h> //printf debugging

btCompoundShape* newBoxCompound=0;
btRigidBody* fractureBody = 0;

void BasicDemo::clientMoveAndDisplay()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); 

	//simple dynamics world doesn't handle fixed-time-stepping
	float ms = getDeltaTimeMicroseconds();

	///step the simulation
	if (m_dynamicsWorld)
	{
		m_dynamicsWorld->stepSimulation(ms / 1000000.f);
		//optional but useful: debug drawing
		m_dynamicsWorld->debugDrawWorld();
	}

	renderme(); 

	glFlush();

	glutSwapBuffers();

}



void BasicDemo::displayCallback(void) {

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); 

	renderme();

	//optional but useful: debug drawing to detect problems
	if (m_dynamicsWorld)
		m_dynamicsWorld->debugDrawWorld();

	glFlush();
	glutSwapBuffers();
}


btCompoundShape* shiftTransform(btCompoundShape* boxCompound,btScalar mass,btTransform& shift)
{
	btTransform principal;
	btVector3 principalInertia;
	btScalar* masses = new btScalar[boxCompound->getNumChildShapes()];
	for (int j=0;j<boxCompound->getNumChildShapes();j++)
	{
		//evenly distribute mass
		masses[j]=mass/boxCompound->getNumChildShapes();
	}


	boxCompound->calculatePrincipalAxisTransform(masses,principal,principalInertia);


	///create a new compound with world transform/center of mass properly aligned with the principal axis

	///non-recursive compound shapes perform better
	
#ifdef USE_RECURSIVE_COMPOUND

	btCompoundShape* newCompound = new btCompoundShape();
	newCompound->addChildShape(principal.inverse(),boxCompound);
	newBoxCompound = newCompound;
	//m_collisionShapes.push_back(newCompound);

	//btDefaultMotionState* myMotionState = new btDefaultMotionState(startTransform);
	//btRigidBody::btRigidBodyConstructionInfo rbInfo(mass,myMotionState,newCompound,principalInertia);

#else
#ifdef CHANGE_COMPOUND_INPLACE
	newBoxCompound = boxCompound;
	for (int i=0;i<boxCompound->getNumChildShapes();i++)
	{
		btTransform newChildTransform = principal.inverse()*boxCompound->getChildTransform(i);
		///updateChildTransform is really slow, because it re-calculates the AABB each time. todo: add option to disable this update
		boxCompound->updateChildTransform(i,newChildTransform);
	}
	bool isDynamic = (mass != 0.f);
	btVector3 localInertia(0,0,0);
	if (isDynamic)
		boxCompound->calculateLocalInertia(mass,localInertia);
	
#else
	///creation is faster using a new compound to store the shifted children
	newBoxCompound = new btCompoundShape();
	for (int i=0;i<boxCompound->getNumChildShapes();i++)
	{
		btTransform newChildTransform = principal.inverse()*boxCompound->getChildTransform(i);
		///updateChildTransform is really slow, because it re-calculates the AABB each time. todo: add option to disable this update
		newBoxCompound->addChildShape(newChildTransform,boxCompound->getChildShape(i));
	}



#endif

#endif//USE_RECURSIVE_COMPOUND

	shift = principal;
	return newBoxCompound;
}


void   BasicDemo::initPhysics()
{
	setTexturing(true);
	setShadows(false);


	btScalar maxDiag = 2.*btMax(ARRAY_SIZE_X,btMax(ARRAY_SIZE_Y,ARRAY_SIZE_Z));

	btTransform startTransform;
		startTransform.setIdentity();

		startTransform.setOrigin(btVector3(0,maxDiag*SCALING,0));

		btScalar   mass(1.f);


	setCameraDistance(btScalar(SCALING*2*maxDiag));

	///collision configuration contains default setup for memory, collision setup
	m_collisionConfiguration = new btDefaultCollisionConfiguration();
	//m_collisionConfiguration ->setConvexConvexMultipointIterations();

	///use the default collision dispatcher. For parallel processing you can use a diffent dispatcher (see Extras/BulletMultiThreaded)
	m_dispatcher = new   btCollisionDispatcher(m_collisionConfiguration);

	m_broadphase = new btDbvtBroadphase();

	///the default constraint solver. For parallel processing you can use a different solver (see Extras/BulletMultiThreaded)
	btSequentialImpulseConstraintSolver* sol = new btSequentialImpulseConstraintSolver;
	m_solver = sol;

	m_dynamicsWorld = new btDiscreteDynamicsWorld(m_dispatcher,m_broadphase,m_solver,m_collisionConfiguration);
	
	m_dynamicsWorld->setGravity(btVector3(0,-10,0));

	///create a few basic rigid bodies
	//btCollisionShape* groundShape = new btBoxShape(btVector3(btScalar(50.),btScalar(50.),btScalar(50.)));
	btCollisionShape* groundShape = new btStaticPlaneShape(btVector3(0,1,0),50);

	m_collisionShapes.push_back(groundShape);

	btTransform groundTransform;
	groundTransform.setIdentity();
	groundTransform.setOrigin(btVector3(0,-50,0));

	//We can also use DemoApplication::localCreateRigidBody, but for clarity it is provided here:
	{
		btScalar mass(0.);

		//rigidbody is dynamic if and only if mass is non zero, otherwise static
		bool isDynamic = (mass != 0.f);

		btVector3 localInertia(0,0,0);
		if (isDynamic)
			groundShape->calculateLocalInertia(mass,localInertia);

		//using motionstate is recommended, it provides interpolation capabilities, and only synchronizes 'active' objects
		btDefaultMotionState* myMotionState = new btDefaultMotionState(groundTransform);
		btRigidBody::btRigidBodyConstructionInfo rbInfo(mass,myMotionState,groundShape,localInertia);
		btRigidBody* body = new btRigidBody(rbInfo);

		//add the body to the dynamics world
		m_dynamicsWorld->addRigidBody(body);
	}


	{
		//create a few dynamic rigidbodies
		// Re-using the same collision is better for memory usage and performance

		//btCollisionShape* colShape = new btBoxShape(btVector3(SCALING*1,SCALING*1,SCALING*1));
		btCollisionShape* colShape = new btBoxShape(btVector3(SCALING*1,SCALING*1,SCALING*1));
		//btCollisionShape* colShape = new btSphereShape(btScalar(1.*SCALING));

		btCompoundShape* boxCompound = new btCompoundShape();

		btTransform boxLocalTrans;


		/// Create Dynamic Objects
		
		//rigidbody is dynamic if and only if mass is non zero, otherwise static
		bool isDynamic = (mass != 0.f);

		btVector3 localInertia(0,0,0);

		
		float start_x = START_POS_X - ARRAY_SIZE_X/2;
		float start_y = START_POS_Y;
		float start_z = START_POS_Z - ARRAY_SIZE_Z/2;

		for (int k=0;k< ARRAY_SIZE_X;k++)
		{
			for (int i=0;i<ARRAY_SIZE_X;i++)
			{
				for(int j = 0;j<i;j++)
				{
					//if ((i+j+k) %2 == 0)
					//{
					boxLocalTrans.setIdentity();
					boxLocalTrans.setOrigin(btVector3(SCALING*2*i,SCALING*2*j,SCALING*2*k));
					boxCompound->addChildShape(boxLocalTrans, colShape);
					//}

				}
			}
		}




		
#ifdef SHIFT_TRANSFORM
		btTransform shift;
		shift.setIdentity();
		btCompoundShape* newBoxCompound = shiftTransform(boxCompound,mass,shift);
		newBoxCompound->calculateLocalInertia(mass,localInertia);
		btDefaultMotionState* myMotionState = new btDefaultMotionState(startTransform*shift);
		btRigidBody::btRigidBodyConstructionInfo rbInfo(mass,myMotionState,newBoxCompound,localInertia);
#else
		boxCompound->calculateLocalInertia(mass,localInertia);
		btDefaultMotionState* myMotionState = new btDefaultMotionState(startTransform);	
		btRigidBody::btRigidBodyConstructionInfo rbInfo(mass,myMotionState,boxCompound,localInertia);
#endif
		
		
		
		
		

		fractureBody = new btRigidBody(rbInfo);
		
		//fractureBody = localCreateRigidBody(mass, startTransform,new btBoxShape(btVector3(1,1,1)));//btSphereShape(1.));//boxCompound);

		m_dynamicsWorld->addRigidBody(fractureBody);

		//	  body->forceActivationState(ISLAND_SLEEPING);
		//	  body->setDeactivationTime( 0.f );


	}

	//don't call clientResetScene, because it will re-activate the object
	//clientResetScene();
}


void   BasicDemo::exitPhysics()
{

	//cleanup in the reverse order of creation/initialization

	//remove the rigidbodies from the dynamics world and delete them
	int i;
	for (i=m_dynamicsWorld->getNumCollisionObjects()-1; i>=0 ;i--)
	{
		btCollisionObject* obj = m_dynamicsWorld->getCollisionObjectArray()[i];
		btRigidBody* body = btRigidBody::upcast(obj);
		if (body && body->getMotionState())
		{
			delete body->getMotionState();
		}
		m_dynamicsWorld->removeCollisionObject( obj );
		delete obj;
	}

	//delete collision shapes
	for (int j=0;j<m_collisionShapes.size();j++)
	{
		btCollisionShape* shape = m_collisionShapes[j];
		delete shape;
	}

	delete m_dynamicsWorld;

	delete m_solver;

	delete m_broadphase;

	delete m_dispatcher;

	delete m_collisionConfiguration;


}

void BasicDemo::keyboardCallback(unsigned char key, int x, int y)
{
	switch (key)
	{
	case 'f':
		{
			if (newBoxCompound->getNumChildShapes()>1)
			{
				btCompoundShape* tmpCompound0 = new btCompoundShape();

				btCompoundShape* tmpCompound1 = new btCompoundShape();

				//fracture the compound body in 2 parts
				//fractureBody->getCollisionShape

				int i=0;
				for (i=0;i<newBoxCompound->getNumChildShapes()/2;i++)
				{
					tmpCompound0->addChildShape(newBoxCompound->getChildTransform(i),newBoxCompound->getChildShape(i));
				}
				for (;i<newBoxCompound->getNumChildShapes();i++)
				{
					tmpCompound1->addChildShape(newBoxCompound->getChildTransform(i),newBoxCompound->getChildShape(i));
				}

					btTransform orgTrans = fractureBody->getWorldTransform();
				btScalar newMass = (1.f/fractureBody->getInvMass())/2;

				{
					btTransform startTransform = fractureBody->getWorldTransform();
					
					btVector3 localInertia;
					btTransform shift;
					btCompoundShape* compound1 = shiftTransform(tmpCompound1,newMass,shift);

					compound1->calculateLocalInertia(newMass,localInertia);
					btRigidBody::btRigidBodyConstructionInfo rbInfo(newMass,0,compound1,localInertia);
					rbInfo.m_startWorldTransform = orgTrans*shift;
					btRigidBody* fractureBody2 = new btRigidBody(rbInfo);
					m_dynamicsWorld->addRigidBody(fractureBody2);
				}

			
				{
					
					btTransform shift;
					btCompoundShape* compound0 = shiftTransform(tmpCompound0,newMass,shift);

					//compound0 = shiftCompoundChildShapes(compound0);
					//compound1 = shiftCompoundChildShapes(compound1);

					m_dynamicsWorld->removeRigidBody(fractureBody);
					fractureBody->setCollisionShape(compound0);
					fractureBody->setWorldTransform(orgTrans*shift);
					btVector3 localInertia;
					compound0->calculateLocalInertia(newMass,localInertia);
					fractureBody->setMassProps(newMass,localInertia);
					m_dynamicsWorld->addRigidBody(fractureBody);
					newBoxCompound = compound0;
				}

			}

			

			break;

		};
	default:
		{
			DemoApplication::keyboardCallback(key,x,y);
		}
	};
}