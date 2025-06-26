/*
	@file	SwingDownAttackRaisePhase.cpp
	@brief	�v���C�V�[���N���X
*/
#include "pch.h"
#include "SwingDownAttackRaisePhase.h"
#include "GameBase/Common/Commons.h"
#include "Libraries/MyLib/DebugCamera.h"
#include "Libraries/MyLib/DebugString.h"
#include "Libraries/MyLib/GridFloor.h"
#include "Libraries/MyLib/InputManager.h"
#include "Libraries/MyLib/MemoryLeakDetector.h"
#include <cassert>


#include "Game/Player/Player.h"
#include "Game/Enemies/BossEnemy/Action/SwingDown/SwingDownAttackActionController.h"


/// <summary>
/// �R���X�g���N�^
/// </summary>
/// <param name="resources">���ʃ��\�[�X</param>
/// <param name="controller">�R���g���[���[</param>
/// <param name="owner">���L��</param>
SwingDownAttackRaisePhase::SwingDownAttackRaisePhase(SwingDownAttackActionController* controller
	, Actor* owner
	)
	:
	m_commonResources{}
	, m_owner{ owner }
	, m_controller{controller}
	,m_time{}
{

}

/// <summary>
/// �f�X�g���N�^
/// </summary>
SwingDownAttackRaisePhase::~SwingDownAttackRaisePhase()
{
	// do nothing.
}


/// <summary>
/// �X�V����
/// </summary>
/// <param name="elapsedTime">�o�ߎ���</param>
/// <returns>�p�����I����</returns>
SwingDownAttackRaisePhase::ActionState SwingDownAttackRaisePhase::Update(const float& elapsedTime)
{
	//���Ԃ̓A�j���[�V�����ƍ��킹��
	if (m_time >= RAISE_TIME)
	{
		return ActionState::END;
	}

	
	m_time += elapsedTime;

	return ActionState::RUNNING;

}



/// <summary>
/// ��Ԃɓ�������
/// </summary>
void SwingDownAttackRaisePhase::Enter()
{

	m_time = 0;



}

/// <summary>
/// ��Ԃ𔲂�����
/// </summary>
void SwingDownAttackRaisePhase::Exit()
{
}
