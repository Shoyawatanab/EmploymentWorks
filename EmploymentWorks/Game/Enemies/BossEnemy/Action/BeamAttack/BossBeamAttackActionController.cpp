/*
	@file	BossBeamAttackActionController.cpp
	@brief	�v���C�V�[���N���X
*/
#include "pch.h"
#include "BossBeamAttackActionController.h"
#include "GameBase/Common/Commons.h"
#include "Game/Params.h"




/// <summary>
/// �R���X�g���N�^
/// </summary>
/// <param name="resources">���ʃ��\�[�X</param>
BossBeamAttackActionController::BossBeamAttackActionController(Actor* bossenemy
	, BossEnemyBeam* beam
	, Actor* player)
	:
	m_commonResources{}
	,m_preliminaryAction{}
	,m_charge{}
	,m_shot{}
	,m_attackEnd{}
{
	//�e��Ԃ̐���
	m_preliminaryAction = std::make_unique<BossBeamAttackPreliminaryAction>(bossenemy,beam,this);
	m_charge = std::make_unique<BossBeamAttackCharge>( bossenemy, beam,this);
	m_shot = std::make_unique<BossBeamAttackShot>( bossenemy, beam,this,player);
	m_attackEnd = std::make_unique<BossBeamAttackEnd>( bossenemy, beam,this);



	//�s�����ɒǉ�
	AddAction(
		{
		m_preliminaryAction.get()
		,m_charge.get()
		,m_shot.get()
		,m_attackEnd.get()
		}
	);

}

/// <summary>
/// �f�X�g���N�^
/// </summary>
BossBeamAttackActionController::~BossBeamAttackActionController()
{
}





