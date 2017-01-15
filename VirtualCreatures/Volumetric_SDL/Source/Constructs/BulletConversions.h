#pragma once

#include <Constructs/Vec3f.h>
#include <Constructs/Quaternion.h>

#include <bullet/btBulletDynamicsCommon.h>
#include <bullet/btBulletCollisionCommon.h>

// Functions for converting from this game engine's constructs to Bullet physics constructs
btVector3 bt(const Vec3f &vec);

btQuaternion bt(const Quaternion &quat);

Vec3f cons(const btVector3 &bt);

Quaternion cons(const btQuaternion &bt);