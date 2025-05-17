/*
	@file	SwingDownAttackRaisePhase.cpp
	@brief	プレイシーンクラス
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

#include "Game/Enemys/BossEnemy/BossEnemy.h"
#include "Game/Player/Player.h"
#include "Game/Enemys/BossEnemy/ActionNode/JumpAttack/BossJumpAttackAction.h"

using namespace DirectX;
using namespace DirectX::SimpleMath;



/// <summary>
/// コンストラクタ
/// </summary>
/// <param name="resources">共通リソース</param>
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
/// デストラクタ
/// </summary>
SwingDownAttackRaisePhase::~SwingDownAttackRaisePhase()
{
	// do nothing.
}

void SwingDownAttackRaisePhase::Initialize()
{


}

SwingDownAttackRaisePhase::ActionState SwingDownAttackRaisePhase::Update(const float& elapsedTime)
{
	//時間はアニメーションと合わせる
	if (m_time >= 2.0f)
	{
		return ActionState::End;
	}

	
	m_time += elapsedTime;

	return ActionState::Running;

}






void SwingDownAttackRaisePhase::Enter()
{

	m_owner->ChangeAnimation("SwingDown");
	m_time = 0;



}

void SwingDownAttackRaisePhase::Exit()
{
}
