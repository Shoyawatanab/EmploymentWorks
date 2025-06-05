/*
	@file	BossJumpAttackJump.cpp
	@brief	プレイシーンクラス
*/
#include "pch.h"
#include "BossJumpAttackJump.h"
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
#include "BossJumpAttackAction.h"

using namespace DirectX;
using namespace DirectX::SimpleMath;



/// <summary>
/// コンストラクタ
/// </summary>
/// <param name="resources">共通リソース</param>
/// <param name="parent">コントローラー</param>
/// <param name="bossenemy">所有者</param>
/// <param name="player">プレイヤ</param>
BossJumpAttackJump::BossJumpAttackJump(CommonResources* resources
	,BossJumpAttackAction* parent
	,BossEnemy* bossenemy
	, Player* player)
	:
	m_commonResources{resources}
	,m_bossEnemy{bossenemy}
	,m_player{player}
	,m_parent{parent}
	,m_jumpDirection{}
{



}

/// <summary>
/// デストラクタ
/// </summary>
BossJumpAttackJump::~BossJumpAttackJump()
{
	// do nothing.
}

/// <summary>
/// 初期化
/// </summary>
void BossJumpAttackJump::Initialize()
{



}


/// <summary>
/// 更新処理
/// </summary>
/// <param name="elapsedTime">経過時間</param>
/// <returns>継続か終了か</returns>
BossJumpAttackJump::ActionState BossJumpAttackJump::Update(const float& elapsedTime)
{

	////速度の取得
	//Vector3 velocity = m_bossEnemy->GetVelocity();
	////速度の更新
	//velocity.x = m_jumpDirection.x * elapsedTime * BossJumpAttackAction::MOVESPEED;
	//velocity.z = m_jumpDirection.z * elapsedTime * BossJumpAttackAction::MOVESPEED;

	////速度の登録
	//m_bossEnemy->SetVelocity(velocity);

	////着地したら
	//if (m_bossEnemy->GetIsGrounded())
	//{
	//	return ActionState::END;
	//}

	return ActionState::RUNNING;

}

/// <summary>
/// 状態に入った時
/// </summary>
void BossJumpAttackJump::Enter()
{

	//Vector3 velocity = m_bossEnemy->GetVelocity();

	//velocity.y += BossJumpAttackAction::JUMPPOWER;
	////velocity.y += 5.0f;

	//m_bossEnemy->SetVelocity(velocity);


	//Vector3 bossPos = m_bossEnemy->GetPosition();

	//Vector3 playerPos = m_player->GetPosition();


	////方向を求める
	//m_jumpDirection = playerPos - bossPos;
	////正規化
	//m_jumpDirection.Normalize();


}

/// <summary>
/// 状態を抜けた時
/// </summary>
void BossJumpAttackJump::Exit()
{

	//m_bossEnemy->ChangeAnimation("Idel");

	//Vector3 pos = m_bossEnemy->GetPosition();

	//pos.y = 0.1f;

	//Messenger::GetInstance()->Notify(GamePlayMessageType::CREATE_PARTICLE, &pos);

	//m_bossEnemy->SetVelocity(Vector3::Zero);

}
