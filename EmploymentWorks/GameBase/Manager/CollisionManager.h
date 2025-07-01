#pragma once
//#include "GameBase/Component/Components.h"

class ColliderComponent;

class CollisionManager
{

public:
	//�R���X�g���N�^
	CollisionManager();
	//�f�X�g���N�^
	~CollisionManager();
	//�X�V����
	void Update(const float& deltaTime);

	//�R���C�_�[�̒ǉ�
	void AddCollider(ColliderComponent* collider);
	//�R���C�_�[�̍폜
	void RemoveCollider(ColliderComponent* collider);

private:

	//�ړ��I�u�W�F�N�g���m
	void Collision_Collision(ColliderComponent* collider1, ColliderComponent* collider2);
	//�Œ�I�u�W�F�N�g���m
	void Fixed_Fixed(ColliderComponent* collider1, ColliderComponent* collider2);
	//���蔲���I�u�W�F�N�g���m
	void Trigger_Trigger(ColliderComponent* collider1, ColliderComponent* collider2);
	//�Œ�I�u�W�F�N�g�ƈړ��I�u�W�F�N�g
	void Fixed_Collision(ColliderComponent* collider1, ColliderComponent* collider2);
	//�Œ�I�u�W�F�N�g���蔲���I�u�W�F�N�g
	void Fixed_Trigger(ColliderComponent* collider1, ColliderComponent* collider2);
	//�ړ��I�u�W�F�N�g�Ƃ��蔲���I�u�W�F�N�g
	void Collision_Trigger(ColliderComponent* collider1, ColliderComponent* collider2);

	//�ʒm�𑗂�
	void SendNotification(ColliderComponent* collider1, ColliderComponent* collider2,bool isHit);

private:

	std::vector<ColliderComponent*> m_colliderList;

};