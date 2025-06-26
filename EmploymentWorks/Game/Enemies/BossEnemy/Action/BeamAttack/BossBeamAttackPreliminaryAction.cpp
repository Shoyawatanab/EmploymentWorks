/*
	@file	BossBeamAttackPreliminaryAction.cpp
	@brief	�v���C�V�[���N���X
*/
#include "pch.h"
#include "BossBeamAttackPreliminaryAction.h"
#include "GameBase/Common/Commons.h"
#include "Libraries/MyLib/DebugCamera.h"
#include "Libraries/MyLib/DebugString.h"
#include "Libraries/MyLib/GridFloor.h"
#include "Libraries/MyLib/InputManager.h"
#include "Libraries/MyLib/MemoryLeakDetector.h"
#include <cassert>

#include "Game/Params.h"



/// <summary>
/// �R���X�g���N�^
/// </summary>
/// <param name="resources">���ʃ��\�[�X</param>
/// <param name="bossEnemy">���L��</param>
/// <param name="beam">�r�[��</param>
/// <param name="beamAttack">�r�[���U��</param>
BossBeamAttackPreliminaryAction::BossBeamAttackPreliminaryAction(Actor* bossEnemy
	, BossEnemyBeam* beam
	, BossBeamAttackActionController* beamAttack)
	:
	m_commonResources{}
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


}

/// <summary>
/// ��Ԃ𔲂�����
/// </summary>
void BossBeamAttackPreliminaryAction::Exit()
{



}
