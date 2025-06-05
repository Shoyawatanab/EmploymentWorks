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

#include "Game/Enemies/BossEnemy/BossEnemy.h"
#include "Game/Player/Player.h"
#include "Game/Enemys/BossEnemy/ActionNode/RushAttack/BossRushAttackAction.h"



/// <summary>
/// コンストラクタ
/// </summary>
/// <param name="resources">共通リソース</param>
/// <param name="parent">コントローラー</param>
/// <param name="bossenemy">所有者</param>
/// <param name="player">プレイヤ</param>
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

/// <summary>
/// 初期化
/// </summary>
void BossRushAttackCharge::Initialize()
{
}

/// <summary>
/// 更新処理
/// </summary>
/// <param name="elapsedTime">経過時間</param>
/// <returns>継続か終了か</returns>
BossRushAttackCharge::ActionState BossRushAttackCharge::Update(const float& elapsedTime)
{
	//時間はアニメーションと合わせる
	if (m_time >= CHARGE_TIME)
	{

		return ActionState::END;

	}

	
	m_time += elapsedTime;

	return ActionState::RUNNING;
}


/// <summary>
/// 状態に入った時
/// </summary>
void BossRushAttackCharge::Enter()
{

	//m_bossEnemy->ChangeAnimation("JumpCharge");
	//m_time = 0;

	//Vector3 pos = m_bossEnemy->GetPosition();

	//pos.y = 0.1f;

	//Vector3 scale = EFFECTE_SCALE;


	//UnknownDataThree aa = { static_cast<void*>(&pos), static_cast<void*>(&scale) };

	//Messenger::GetInstance()->Notify(GamePlayMessageType::CREATE_CHAGE_EFFECT, &aa);


}

/// <summary>
/// 状態を抜けた時
/// </summary>
void BossRushAttackCharge::Exit()
{
}
