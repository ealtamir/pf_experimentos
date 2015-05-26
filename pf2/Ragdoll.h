#ifndef RAGDOLL_H_INCLUDED
#define RAGDOLL_H_INCLUDED

#include "DemoApplication.h"
#include "LinearMath/btAlignedObjectArray.h"
#include <BulletDynamics/btBulletDynamicsCommon.h>




class RagDoll
{
	btDynamicsWorld* m_ownerWorld;

	btRigidBody* localCreateRigidBody (btScalar mass, const btTransform& startTransform, btCollisionShape* shape);

public:
    enum
    {
        BODYPART_PELVIS = 0,
//        BODYPART_SPINE,
//        BODYPART_HEAD,
        
        BODYPART_LEFT_UPPER_LEG,
        BODYPART_LEFT_LOWER_LEG,
        BODYPART_LEFT_FOOT,
        
        BODYPART_RIGHT_UPPER_LEG,
        BODYPART_RIGHT_LOWER_LEG,
        BODYPART_RIGHT_FOOT,
        
//        BODYPART_LEFT_UPPER_ARM,
//        BODYPART_LEFT_LOWER_ARM,
        
//        BODYPART_RIGHT_UPPER_ARM,
//        BODYPART_RIGHT_LOWER_ARM,
        
        BODYPART_COUNT
    };
    
    enum
    {
//        JOINT_PELVIS_SPINE = 0,
//        JOINT_SPINE_HEAD,
        
        JOINT_LEFT_HIP = 0,
        JOINT_LEFT_KNEE,
        JOINT_LEFT_FOOT,
        
        JOINT_RIGHT_HIP,
        JOINT_RIGHT_KNEE,
        JOINT_RIGHT_FOOT,
        
//        JOINT_LEFT_SHOULDER,
//        JOINT_LEFT_ELBOW,
        
//        JOINT_RIGHT_SHOULDER,
//        JOINT_RIGHT_ELBOW,
        
        JOINT_COUNT
    };
    
    btCollisionShape* m_shapes[BODYPART_COUNT];
    
    btRigidBody* m_bodies[BODYPART_COUNT];
    btTypedConstraint* m_joints[JOINT_COUNT];
    
	RagDoll (btDynamicsWorld* ownerWorld,
				const btVector3& positionOffset,
				btScalar scale_ragdoll = btScalar(1.0));

	~RagDoll ();
};



#endif // RAGDOLL_H_INCLUDED
