#pragma once
#include "Game/Entities/CollisionEntity.h"


namespace WataLib
{
	class DetectionCollision
	{

	public:
		//�R���X�g���N�^
		DetectionCollision() = default;
		//�f�X�g���N�^
		~DetectionCollision() = default;
		//�����������ǂ���
		static void CheckHit(CollisionEntity* object1, CollisionEntity* object2, bool& isHit);
		//�~�Ǝl�p�̔���
		static bool Circle_RectCheckHit(const DirectX::SimpleMath::Vector2& circleCenter, float circleRadius,
			const DirectX::SimpleMath::Vector2& rectCenter, float rectWidth, float rectHeight);

	private:
		//AABB���m
		static void AABB_AABB(CollisionEntity* object1, CollisionEntity* object2, bool& isHit);
		//OBB���m
		static void OBB_OBB(CollisionEntity* object1, CollisionEntity* object2, bool& isHit);
		//�X�t�B�A���m
		static void SPHERE_SPHERE(CollisionEntity* object1, CollisionEntity* object2, bool& isHit);
		//AABB��OBB
		static void AABB_OBB(CollisionEntity* object1, CollisionEntity* object2, bool& isHit);
		//AABB�ƃX�t�B�A
		static void AABB_SPHERE(CollisionEntity* object1, CollisionEntity* object2, bool& isHit);


	private:

		//����̃��X�g
		static std::unordered_map<int, std::function<void(CollisionEntity* object1, CollisionEntity* object2, bool& isHit)>> m_detectionFunction;

	};
}