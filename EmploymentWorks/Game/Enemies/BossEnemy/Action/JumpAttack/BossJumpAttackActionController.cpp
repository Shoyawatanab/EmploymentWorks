/*
	@file	BossJumpAttackActionController.cpp
	@brief	�v���C�V�[���N���X
*/
#include "pch.h"
#include "BossJumpAttackActionController.h"
#include "GameBase/Common/Commons.h"
#include "Game/Params.h"
#include "Game/Player/Player.h"
#include "Game/Enemies/BossEnemy/BossEnemy.h"



/// <summary>
/// �R���X�g���N�^
/// </summary>
/// <param name="resources">���ʃ��\�[�X</param>
BossJumpAttackActionController::BossJumpAttackActionController(BossEnemy* bossenemy
	, Player* player)
	:
	m_commonResources{}
{

	m_commonResources = CommonResources::GetInstance();

	//�e��Ԃ��쐬
	m_charge = std::make_unique<BossJumpAttackCharge>(this,bossenemy,player);
	m_jump = std::make_unique<BossJumpAttackJump>( this, bossenemy, player);
	m_orientation = std::make_unique<OrientationAction>(bossenemy, player);


	//m_currentState->Enter();


	//���쏇�ɒǉ�
	AddAction({
		m_orientation.get(),
		m_charge.get(),
		m_jump.get()
		});


}

/// <summary>
/// �f�X�g���N�^
/// </summary>
BossJumpAttackActionController::~BossJumpAttackActionController()
{
	// do nothing.
}






