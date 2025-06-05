/*
	@file	SwingDownAttackSwingPhase.cpp
	@brief	プレイシーンクラス
*/
#include "pch.h"
#include "SwingDownAttackSwingPhase.h"
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

using namespace DirectX;
using namespace DirectX::SimpleMath;



/// <summary>
/// コンストラクタ
/// </summary>
/// <param name="resources">共通リソース</param>
SwingDownAttackSwingPhase::SwingDownAttackSwingPhase(CommonResources* resources
	, ActionStateController* controller
	, CharacterEntity* owner
	)
	:
	m_commonResources{resources}
	, m_owner{ owner }
	, m_controller{ controller }
	,m_time{}
{

}

/// <summary>
/// デストラクタ
/// </summary>
SwingDownAttackSwingPhase::~SwingDownAttackSwingPhase()
{
	// do nothing.
}

void SwingDownAttackSwingPhase::Initialize()
{



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

	m_owner->ChangeAnimation("Idel");


}
