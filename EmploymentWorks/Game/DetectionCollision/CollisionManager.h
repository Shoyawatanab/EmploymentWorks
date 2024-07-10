#pragma once
/*
	@file	CollisionManager.h.h
	@brief	�v���C�V�[���N���X
*/
#pragma once
#include "pch.h"
#include "Game/Object/Boomerang/Boomerang.h"

// �O���錾
class CommonResources;
class ICollsionObject;


class CollisionManager final 

{
public:


private:
	// ���ʃ��\�[�X
	CommonResources* m_commonResources;
	Player* m_player;
	Enemy* m_enemy;

	//�����蔻��I�u�W�F�N�g�̓o�^�z�� 
	std::vector<ICollisionObject*> m_collsionObjects;

public:
	CollisionManager();

	void Update();

	void AddCollsion(ICollisionObject* object);
private:
};
