/*
	@file	SwingDownAttackSwingPhase.cpp
	@brief	�v���C�V�[���N���X
*/
#include "pch.h"
#include "SwingDownAttackSwingPhase.h"
#include "GameBase/Common/Commons.h"
#include "Libraries/MyLib/DebugCamera.h"
#include "Libraries/MyLib/DebugString.h"
#include "Libraries/MyLib/GridFloor.h"
#include "Libraries/MyLib/InputManager.h"
#include "Libraries/MyLib/MemoryLeakDetector.h"
#include <cassert>

#include "Game/Player/Player.h"

using namespace DirectX;
using namespace DirectX::SimpleMath;



/// <summary>
/// �R���X�g���N�^
/// </summary>
/// <param name="resources">���ʃ��\�[�X</param>
SwingDownAttackSwingPhase::SwingDownAttackSwingPhase(SwingDownAttackActionController* controller
	, Actor* owner
	)
	:
	m_commonResources{}
	, m_owner{ owner }
	, m_controller{ controller }
	,m_time{}
{

}

/// <summary>
/// �f�X�g���N�^
/// </summary>
SwingDownAttackSwingPhase::~SwingDownAttackSwingPhase()
{
	// do nothing.
}



SwingDownAttackSwingPhase::ActionState SwingDownAttackSwingPhase::Update(const float& elapsedTime)
{

	if (m_time >= SWING_TIME)
	{
		return ActionState::END;
	}

	m_time += elapsedTime;

	return ActionState::RUNNING
		;

}





void SwingDownAttackSwingPhase::Enter()
{

	m_time = 0.0f;

}

void SwingDownAttackSwingPhase::Exit()
{

}
