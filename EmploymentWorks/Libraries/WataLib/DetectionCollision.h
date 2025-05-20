#pragma once
#include "Game/Entities/CollisionEntity.h"


namespace WataLib
{
	class DetectionCollision
	{

	public:
		//コンストラクタ
		DetectionCollision() = default;
		//デストラクタ
		~DetectionCollision() = default;
		//当たったかどうか
		static void CheckHit(CollisionEntity* object1, CollisionEntity* object2, bool& isHit);
		//円と四角の判定
		static bool Circle_RectCheckHit(const DirectX::SimpleMath::Vector2& circleCenter, float circleRadius,
			const DirectX::SimpleMath::Vector2& rectCenter, float rectWidth, float rectHeight);

	private:
		//AABB同士
		static void AABB_AABB(CollisionEntity* object1, CollisionEntity* object2, bool& isHit);
		//OBB同士
		static void OBB_OBB(CollisionEntity* object1, CollisionEntity* object2, bool& isHit);
		//スフィア同士
		static void SPHERE_SPHERE(CollisionEntity* object1, CollisionEntity* object2, bool& isHit);
		//AABBとOBB
		static void AABB_OBB(CollisionEntity* object1, CollisionEntity* object2, bool& isHit);
		//AABBとスフィア
		static void AABB_SPHERE(CollisionEntity* object1, CollisionEntity* object2, bool& isHit);


	private:

		//判定のリスト
		static std::unordered_map<int, std::function<void(CollisionEntity* object1, CollisionEntity* object2, bool& isHit)>> m_detectionFunction;

	};
}