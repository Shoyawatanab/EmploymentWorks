/*
	@file	BossRushAttackCharge.cpp
	@brief	プレイシーンクラス
*/
#include "pch.h"
#include "BossRushAttackCharge.h"
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
#include "Game/Enemys/BossEnemy/ActionNode/RushAttack/BossRushAttackAction.h"

using namespace DirectX;
using namespace DirectX::SimpleMath;



/// <summary>
/// コンストラクタ
/// </summary>
/// <param name="resources">共通リソース</param>
BossRushAttackCharge::BossRushAttackCharge(CommonResources* resources
	, BossRushAttackAction* parent
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
BossRushAttackCharge::~BossRushAttackCharge()
{
	// do nothing.
}

void BossRushAttackCharge::Initialize()
{


}

IBehaviorNode::State BossRushAttackCharge::Update(const float& elapsedTime)
{
	//時間はアニメーションと合わせる
	if (m_time >= 1.5f)
	{
	}

	
	m_time += elapsedTime;

	return IBehaviorNode::State::Runngin;

}






void BossRushAttackCharge::Enter()
{

	m_bossEnemy->ChangeAnimation("JumpCharge");
	m_time = 0;

	Vector3 pos = m_bossEnemy->GetPosition();

	pos.y = 0.1f;

	EventParams::CreateHitEffectDatas aa = {  pos, Vector3(5,5,5)};

	Messenger::Notify(EventParams::EventType::CreateChageEffect, &aa);


}

void BossRushAttackCharge::Exit()
{
}
