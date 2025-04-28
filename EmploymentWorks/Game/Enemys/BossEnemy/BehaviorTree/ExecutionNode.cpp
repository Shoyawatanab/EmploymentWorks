#include "pch.h"
#include "ExecutionNode.h"

#include "Game/Player/Player.h"
#include "Game/Enemys/BossEnemy/BossEnemy.h"
#include "Game/CommonResources.h"

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
/// �f�X�g���N�^
/// </summary>
ExecutionNode::~ExecutionNode()
{

}

/// <summary>
/// ������
/// </summary>
/// <param name="resources">���ʃ��\�[�X</param>
void ExecutionNode::Initialize(CommonResources* resources)
{

	m_commonResources = resources;



}

IBehaviorNode::State ExecutionNode::Action()
{
	
	m_enemy->ChangeAction("JumpAttack");

	return IBehaviorNode::State::Success;

}


