#pragma once
#include "GameBase/Component/Collider/ColliderComponent.h"

class DetectionCollision2
{

public:
	//�R���X�g���N�^
	DetectionCollision2() = default;
	//�f�X�g���N�^
	~DetectionCollision2() = default;
	//�����������ǂ����̃`�F�b�N true : ��������  false : �������ĂȂ�
	static bool ChecOnCollision(ColliderComponent* collider1, ColliderComponent* collier2);

	static const DirectX::SimpleMath::Vector3 Extrusion(ColliderComponent* collider1, ColliderComponent* collider2);

private:

//�������Ă��邩�̔���֐�
	//AABB���m�̔���
	static bool AABB_AABB_CheckCollision(ColliderComponent& collider1, ColliderComponent& collider2);
	//OBB���m�̔���
	static bool OBB_OBB_CheckCollision(ColliderComponent& collider1, ColliderComponent& collider2);
	//�X�t�B�A���m�̔���
	static bool SPHERE_SPHERE_CheckCollision(ColliderComponent& collider1, ColliderComponent& collider2);
	//AABB��OBB�̔���
	static bool AABB_OBB_CheckCollision(ColliderComponent& collider1, ColliderComponent& collider2);
	//AABB�ƃX�t�B�A�̔���
	static bool AABB_SPHERE_CheckCollision(ColliderComponent& collider1, ColliderComponent& collider2);

//���������̊֐�

	//AABB���m�̉����o��
	static DirectX::SimpleMath::Vector3 AABB_AABB_Extrusion(ColliderComponent& collider1, ColliderComponent& collider2);
	//OBB���m�̉����o��
	static DirectX::SimpleMath::Vector3 OBB_OBB_Extrusion(ColliderComponent& collider1, ColliderComponent& collider2);
	//�X�t�B�A���m�̉����o��
	static DirectX::SimpleMath::Vector3 SPHERE_SPHERE_Extrusion(ColliderComponent& collider1, ColliderComponent& collider2);
	//AABB��OBB�̉����o��
	static DirectX::SimpleMath::Vector3 AABB_OBB_Extrusion(ColliderComponent& collider1, ColliderComponent& collider2);
	//AABB�ƃX�t�B�A�̉����o��
	static DirectX::SimpleMath::Vector3 AABB_SPHERE_Extrusion(ColliderComponent& collider1, ColliderComponent& collider2);


private:


	//�����蔻��̃��X�g
	static std::unordered_map<int, std::function<bool(ColliderComponent& Collider1, ColliderComponent& Collider2)>> m_checkCollisionFunction;
	//�����o�����X�g
	static std::unordered_map<int, std::function<DirectX::SimpleMath::Vector3(ColliderComponent& Collider1, ColliderComponent& Collider2)>> m_extrusionFunction;



};



