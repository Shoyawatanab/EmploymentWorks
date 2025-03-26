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

#include "Game/Enemys/BossEnemy/BossEnemy.h"
#include "Game/Player/Player.h"


using namespace DirectX;
using namespace DirectX::SimpleMath;



/// <summary>
/// コンストラクタ
/// </summary>
/// <param name="resources">共通リソース</param>
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

void BossJumpAttackJump::Initialize()
{



}

IBehaviorNode::State BossJumpAttackJump::Update(const float& elapsedTime)
{

	float speed = 9.0f;


	Vector3 velocity = m_bossEnemy->GetVelocity();

	velocity.x = m_jumpDirection.x * elapsedTime * speed;

	velocity.z = m_jumpDirection.z * elapsedTime * speed;

	m_bossEnemy->SetVelocity(velocity);

	return IBehaviorNode::State::Runngin;

}





void BossJumpAttackJump::Enter()
{

	Vector3 velocity = m_bossEnemy->GetVelocity();

	velocity.y += 1.0f;

	m_bossEnemy->SetVelocity(velocity);


	Vector3 bossPos = m_bossEnemy->GetPosition();

	Vector3 playerPos = m_player->GetPosition();



	//方向を求める
	m_jumpDirection = playerPos - bossPos;
	//正規化
	m_jumpDirection.Normalize();


}

void BossJumpAttackJump::Exit()
{

	m_bossEnemy->ChangeAnimation("Idel");


}
