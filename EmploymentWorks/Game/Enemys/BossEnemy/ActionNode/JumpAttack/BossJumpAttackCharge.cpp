/*
	@file	BossJumpAttackCharge.cpp
	@brief	プレイシーンクラス
*/
#include "pch.h"
#include "BossJumpAttackCharge.h"
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
BossJumpAttackCharge::BossJumpAttackCharge(CommonResources* resources
	,BossJumpAttackAction* parent
	,BossEnemy* bossenemy
	, Player* player)
	:
	m_commonResources{resources}
	,m_bossEnemy{bossenemy}
	,m_player{player}
	,m_parent{parent}
	,m_time{}
{

}

/// <summary>
/// デストラクタ
/// </summary>
BossJumpAttackCharge::~BossJumpAttackCharge()
{
	// do nothing.
}

void BossJumpAttackCharge::Initialize()
{


}

IBehaviorNode::State BossJumpAttackCharge::Update(const float& elapsedTime)
{
	//時間はアニメーションと合わせる
	if (m_time >= 1.5f)
	{
		m_parent->ChangeState(m_parent->GetBossJumpAttackJump());
	}

	
	m_time += elapsedTime;

	return IBehaviorNode::State::Runngin;

}






void BossJumpAttackCharge::Enter()
{

	m_bossEnemy->ChangeAnimation("JumpCharge");
	m_time = 0;

}

void BossJumpAttackCharge::Exit()
{
}
