#include "pch.h"
#include "ExecutionNode.h"

#include "Game/Player/Player.h"
#include "Game/Enemies/BossEnemy/BossEnemy.h"
#include "Game/CommonResources.h"

#include "Game/Observer/Messenger.h"

using namespace DirectX::SimpleMath;
using namespace DirectX;

static const float ROTATESPEED = 1.0f;
static const float PATROLSPEED = 2.0f;;

/// <summary>
/// 
/// </summary>
/// <param name="player"></param>
/// <param name="enemy"></param>
ExecutionNode::ExecutionNode(Player* player, BossEnemy* enemy)
	:
	m_commonResources{},
	m_palyer{ player },
	m_enemy{ enemy }
{

}

/// <summary>
/// デストラクタ
/// </summary>
ExecutionNode::~ExecutionNode()
{

}

/// <summary>
/// 初期化
/// </summary>
/// <param name="resources">共通リソース</param>
void ExecutionNode::Initialize(CommonResources* resources)
{

	m_commonResources = resources;



}


/// <summary>
/// ビーム攻撃
/// </summary>
/// <returns></returns>
IBehaviorNode::State ExecutionNode::BossEnemyBeamAction()
{

	//Messenger::GetInstance()->Notify<EnemyMessageType>(m_enemy->GetID(), EnemyMessageType::BEAM_ATTACK, nullptr);


	return IBehaviorNode::State::SUCCESS;

}

/// <summary>
/// バリア防御
/// </summary>
/// <returns></returns>
IBehaviorNode::State ExecutionNode::BossEnemyBarrierDefenseAction()
{

	//Messenger::GetInstance()->Notify<EnemyMessageType>(m_enemy->GetID(), EnemyMessageType::BARRIER_DEFENSE, nullptr);

	return IBehaviorNode::State::SUCCESS;

}

/// <summary>
/// ジャンプ攻撃
/// </summary>
/// <returns></returns>
IBehaviorNode::State ExecutionNode::BossEnemyJumpAttackAction()
{

	//Messenger::GetInstance()->Notify<EnemyMessageType>(m_enemy->GetID(), EnemyMessageType::JUMP_ATTACK, nullptr);


	return IBehaviorNode::State::SUCCESS;

}

/// <summary>
/// 歩き
/// </summary>
/// <returns></returns>
IBehaviorNode::State ExecutionNode::BossEnemyWalking()
{
	//Messenger::GetInstance()->Notify<EnemyMessageType>(m_enemy->GetID(), EnemyMessageType::WALKING, nullptr);

	return IBehaviorNode::State::SUCCESS;

}

/// <summary>
/// 振り下ろし攻撃
/// </summary>
/// <returns></returns>
IBehaviorNode::State ExecutionNode::BossEnemySwingDown()
{

	//Messenger::GetInstance()->Notify<EnemyMessageType>(m_enemy->GetID(), EnemyMessageType::SWING_DOWN, nullptr);


	return IBehaviorNode::State::SUCCESS;
}


