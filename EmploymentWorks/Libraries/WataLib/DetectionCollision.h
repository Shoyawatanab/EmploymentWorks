#pragma once
#include "Game/Entities/CollisionEntity.h"


namespace WataLib
{
	class DetectionCollision
	{

	public:

		DetectionCollision() = default;

		~DetectionCollision() = default;

		static void CheckHit(CollisionEntity* object1, CollisionEntity* object2, bool& isHit);

	private:

		static void AABB_AABB(CollisionEntity* object1, CollisionEntity* object2, bool& isHit);

		static void OBB_OBB(CollisionEntity* object1, CollisionEntity* object2, bool& isHit);

		static void SPHERE_SPHERE(CollisionEntity* object1, CollisionEntity* object2, bool& isHit);

		static void AABB_OBB(CollisionEntity* object1, CollisionEntity* object2, bool& isHit);

		static void AABB_SPHERE(CollisionEntity* object1, CollisionEntity* object2, bool& isHit);

	private:

		static std::unordered_map<int, std::function<void(CollisionEntity* object1, CollisionEntity* object2, bool& isHit)>> m_detectionFunction;

	};
}