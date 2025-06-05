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

#include "Game/Enemies/BossEnemy/BossEnemy.h"
#include "Game/Player/Player.h"
#include "Game/Enemys/BossEnemy/ActionNode/JumpAttack/BossJumpAttackAction.h"


/// <summary>
/// コンストラクタ
/// </summary>
/// <param name="resources">共通リソース</param>
/// <param name="controller">コントローラー</param>
/// <param name="owner">所有者</param>
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

/// <summary>
/// 初期化
/// </summary>
void SwingDownAttackRaisePhase::Initialize()
{


}

/// <summary>
/// 更新処理
/// </summary>
/// <param name="elapsedTime">経過時間</param>
/// <returns>継続か終了か</returns>
SwingDownAttackRaisePhase::ActionState SwingDownAttackRaisePhase::Update(const float& elapsedTime)
{
	//時間はアニメーションと合わせる
	if (m_time >= RAISE_TIME)
	{
		return ActionState::END;
	}

	
	m_time += elapsedTime;

	return ActionState::RUNNING;

}



/// <summary>
/// 状態に入った時
/// </summary>
void SwingDownAttackRaisePhase::Enter()
{

	m_owner->ChangeAnimation("SwingDown");
	m_time = 0;



}

/// <summary>
/// 状態を抜けた時
/// </summary>
void SwingDownAttackRaisePhase::Exit()
{
}
