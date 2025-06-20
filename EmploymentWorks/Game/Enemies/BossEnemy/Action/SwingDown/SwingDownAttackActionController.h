/*
	@file	SwingDownAttackActionController.h
	@brief	�v���C�V�[���N���X
*/
#pragma once
#include "GameBase/Action/ActionController.h"
#include "GameBase/Actor.h"
#include "Game/Enemies/BossEnemy/Action/SwingDown/SwingDownAttackRaisePhase.h"
#include "Game/Enemies/BossEnemy/Action/SwingDown/SwingDownAttackSwingPhase.h"

// �O���錾
class CommonResources;


class SwingDownAttackActionController : public ActionController 
{

public:

	static  constexpr float JUMPPOWER = 0.3f;

	static  constexpr float MOVESPEED = 9.0f;



public:
	//�R���X�g���N�^
	SwingDownAttackActionController(Actor* owner);

	//�f�X�g���N�^
	~SwingDownAttackActionController()override;


private:
	// ���ʃ��\�[�X
	CommonResources* m_commonResources;

	//�U��グ
	std::unique_ptr<SwingDownAttackRaisePhase> m_raisePhase;
	//�U�艺�낵
	std::unique_ptr<SwingDownAttackSwingPhase> m_swingPhase;

};
