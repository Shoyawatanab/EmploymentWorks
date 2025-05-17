#include "pch.h"
#include "ExecutionNode.h"

#include "Game/Player/Player.h"
#include "Game/Enemys/BossEnemy/BossEnemy.h"
#include "Game/CommonResources.h"

#include "Game/Observer/Enemy/EnemyMessenger.h"

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

IBehaviorNode::State ExecutionNode::Action()
{
	
	return IBehaviorNode::State::Success;

}

IBehaviorNode::State ExecutionNode::BossEnemyBeamAction()
{

	EnemyMessenger::GetInstance()->Notify(m_enemy->GetID(), EnemyMessageType::BeamAttack, nullptr);


	return IBehaviorNode::State::Success;

}

IBehaviorNode::State ExecutionNode::BossEnemyBarrierDefenseAction()
{

	EnemyMessenger::GetInstance()->Notify(m_enemy->GetID(), EnemyMessageType::BarrierDefense, nullptr);

	return IBehaviorNode::State::Success;

}

IBehaviorNode::State ExecutionNode::BossEnemyJumpAttackAction()
{

	EnemyMessenger::GetInstance()->Notify(m_enemy->GetID(), EnemyMessageType::JumpAttack, nullptr);


	return IBehaviorNode::State::Success;

}

IBehaviorNode::State ExecutionNode::BossEnemyWalking()
{
	EnemyMessenger::GetInstance()->Notify(m_enemy->GetID(), EnemyMessageType::Walking, nullptr);

	return IBehaviorNode::State::Success;

}

IBehaviorNode::State ExecutionNode::BossEnemySwingDown()
{

	EnemyMessenger::GetInstance()->Notify(m_enemy->GetID(), EnemyMessageType::SwingDown, nullptr);


	return IBehaviorNode::State::Success;
}


