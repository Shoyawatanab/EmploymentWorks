/*
	@file	SwingDownAttackRaisePhase.cpp
	@brief	�v���C�V�[���N���X
*/
#include "pch.h"
#include "SwingDownAttackRaisePhase.h"
#include "Game/CommonResources.h"
#include "DeviceResources.h"
#include "Libraries/MyLib/DebugCamera.h"
#include "Libraries/MyLib/DebugString.h"
#include "Libraries/MyLib/GridFloor.h"
#include "Libraries/MyLib/InputManager.h"
#include "Libraries/MyLib/MemoryLeakDetector.h"
#include <cassert>

#include "Game/Enemies/BossEnemy/BossEnemy.h"
#include "Game/Player/Player.h"
#include "Game/Enemys/BossEnemy/ActionNode/JumpAttack/BossJumpAttackAction.h"


/// <summary>
/// �R���X�g���N�^
/// </summary>
/// <param name="resources">���ʃ��\�[�X</param>
/// <param name="controller">�R���g���[���[</param>
/// <param name="owner">���L��</param>
SwingDownAttackRaisePhase::SwingDownAttackRaisePhase(CommonResources* resources
	, ActionStateController* controller
	, CharacterEntity* owner
	)
	:
	m_commonResources{resources}
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
/// ������
/// </summary>
void SwingDownAttackRaisePhase::Initialize()
{


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

	m_owner->ChangeAnimation("SwingDown");
	m_time = 0;



}

/// <summary>
/// ��Ԃ𔲂�����
/// </summary>
void SwingDownAttackRaisePhase::Exit()
{
}
