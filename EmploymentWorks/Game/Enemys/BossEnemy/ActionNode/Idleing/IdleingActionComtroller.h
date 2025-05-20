/*
	@file	IdleingActionComtroller.h
	@brief	�v���C�V�[���N���X
*/
#pragma once
#include "Game/Entities/ActionStateController.h"
#include "Game/Enemys/BossEnemy/ActionNode/Idleing/IdleingAction.h"

// �O���錾
class CommonResources;
class CharacterEntity;




class IdleingActionComtroller : public ActionStateController
{

public:


public:
	//�R���X�g���N
	IdleingActionComtroller(CommonResources* resources,
		CharacterEntity* own
		);
	//�f�X�g���N�^
	~IdleingActionComtroller();

private:
	// ���ʃ��\�[�X
	CommonResources* m_commonResources;
	//���L��
	CharacterEntity* m_own;
	//�ʏ���
	std::unique_ptr<IdleingAction> m_idle;
};
