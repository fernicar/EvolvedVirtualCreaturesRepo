#pragma once

#include <Scene/SceneObject.h>

#include <bullet/btBulletDynamicsCommon.h>
#include <bullet/btBulletCollisionCommon.h>

#include <Constructs/BulletConversions.h>

#include <bullet/BulletCollision/CollisionDispatch/btGhostObject.h>

class SceneObject_PhysicsWorld :
	public SceneObject
{
public:
	btBroadphaseInterface* m_pBroadphase;
	btDefaultCollisionConfiguration* m_pCollisionConfiguration;
    btCollisionDispatcher* m_pDispatcher;

	btSequentialImpulseConstraintSolver* m_pSolver;
 
    btDiscreteDynamicsWorld* m_pDynamicsWorld;

	btGhostPairCallback* m_pGhostPairCallBack;

	SceneObject_PhysicsWorld();
	~SceneObject_PhysicsWorld();

	// Inherited from SceneObject
	void Logic();
};

