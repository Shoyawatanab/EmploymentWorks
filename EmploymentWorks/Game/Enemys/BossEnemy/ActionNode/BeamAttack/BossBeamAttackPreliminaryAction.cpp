/*
	@file	BossBeamAttackPreliminaryAction.cpp
	@brief	�v���C�V�[���N���X
*/
#include "pch.h"
#include "BossBeamAttackPreliminaryAction.h"
#include "Game/CommonResources.h"
#include "DeviceResources.h"
#include "Libraries/MyLib/DebugCamera.h"
#include "Libraries/MyLib/DebugString.h"
#include "Libraries/MyLib/GridFloor.h"
#include "Libraries/MyLib/InputManager.h"
#include "Libraries/MyLib/MemoryLeakDetector.h"
#include <cassert>

#include "Game/Params.h"
#include "Game/Enemies/BossEnemy/BossEnemy.h"
#include "Game/Enemys/BossEnemy/Beam/Beam.h"
#include "Game/Enemys/BossEnemy/ActionNode/BeamAttack/BossBeamAttackAction.h"



/// <summary>
/// �R���X�g���N�^
/// </summary>
/// <param name="resources">���ʃ��\�[�X</param>
/// <param name="bossEnemy">���L��</param>
/// <param name="beam">�r�[��</param>
/// <param name="beamAttack">�r�[���U��</param>
BossBeamAttackPreliminaryAction::BossBeamAttackPreliminaryAction(CommonResources* resources
	, CharacterEntity* bossEnemy
	, Beam* beam
	, BossBeamAttackAction* beamAttack)
	:
	m_commonResources{resources}
	,m_time{}
	, m_bossEnemy{ bossEnemy }
	, m_beam{ beam }
	,m_beamAttack{beamAttack}
{
}

/// <summary>
/// �f�X�g���N�^
/// </summary>
BossBeamAttackPreliminaryAction::~BossBeamAttackPreliminaryAction()
{
	// do nothing.
}

/// <summary>
/// ������
/// </summary>
void BossBeamAttackPreliminaryAction::Initialize()
{
}

/// <summary>
/// �X�V����
/// </summary>
/// <param name="elapsedTime">�o�ߎ���</param>
/// <returns>�p�����I����</returns>
BossBeamAttackPreliminaryAction::ActionState BossBeamAttackPreliminaryAction::Update(const float& elapsedTime)
{

	if (m_time >= Params::BOSSENEMY_BEAM_BALL_PRELIMINARY_ACTION_TIME)
	{
		return ActionState::END;
	}



	m_time += elapsedTime;

	return ActionState::RUNNING;

}

/// <summary>
/// ��Ԃɓ�������
/// </summary>
void BossBeamAttackPreliminaryAction::Enter()
{

	m_time = 0.0f;

	//m_bossEnemy->ChangeAnimation("BeamAttack");

}

/// <summary>
/// ��Ԃ𔲂�����
/// </summary>
void BossBeamAttackPreliminaryAction::Exit()
{



}
