#pragma once
#include "Game/Entities/CollisionEntity.h"

// �O���錾
class CommonResources;


class CollisionManager
{

public:
	//�R���X�g���N�^
	CollisionManager();
	//�f�X�g���N�^
	~CollisionManager();
	//������
	void Initialize(CommonResources* resources);
	//�X�V
	void Update();
	//�����蔻��N���X�̓o�^
	void AddCollsion(CollisionEntity* object);
	//�����o��
	void Extrusion(CollisionEntity* object1, CollisionEntity* object2);
	//AABB���m�̉����o��
	static void AABB_AABB_Extrusion(CollisionEntity* object1, CollisionEntity* object2);

private:
	// ���ʃ��\�[�X
	CommonResources* m_commonResources;
	//�����蔻��N���X�̔z��
	std::vector<CollisionEntity*> m_collisionObjects;
	//�����o����
	static std::unordered_map<int, std::function<void(CollisionEntity* object1, CollisionEntity* object2)>> m_extrusionFunction;

};