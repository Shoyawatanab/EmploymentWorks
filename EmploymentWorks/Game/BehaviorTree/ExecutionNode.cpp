#include "pch.h"
#include "Game/BehaviorTree/ExecutionNode.h"
#include "ExecutionNode.h"

#include "Game/Object/Player.h"
#include "Game/Object/Enemy/Enemy.h"

ExecutionNode::ExecutionNode(Player* player, Enemy* enemy)
	:
	m_palyer{player},
	m_enemy{enemy},
	m_rotationTime{},
	m_waitTime{},
	m_moveDistance{}
{

}

ExecutionNode::~ExecutionNode()
{

}

//IBehaviorNode::State ExecutionNode::Check(Player* player, Enemy* enemy)
//{
//

//
//	return IBehaviorNode::State::Failure;
//}



/// <summary>
/// �v���C����ǂ�������
/// </summary>
/// <param name="elapsdTime"></param>
/// <returns></returns>
IBehaviorNode::State ExecutionNode::ChaseToPlayer(float elapsdTime)
{

	using namespace DirectX::SimpleMath;

	//���W�̎擾
	Vector3 enemyPos = m_enemy->GetPos();
	Vector3 playerPos = m_palyer->GetPos();

	//�����x�N�g��
	Vector3 direction = playerPos - enemyPos;
	//���K��
	direction.Normalize();

	Vector3 distance = direction * CHASESPEED * elapsdTime;

	//�ʒu�̍X�V
	enemyPos += distance;

	m_enemy->SetPos(enemyPos);



	m_moveDistance += abs(distance.Length());

	if (m_moveDistance >= 5)
	{
		return IBehaviorNode::State::Success;
	}


	return IBehaviorNode::State::Runngin;
}


/// <summary>
/// �ҋ@�@��~
/// </summary>
/// <param name="elapsdTime"></param>
/// <returns></returns>
IBehaviorNode::State ExecutionNode::Wait(float elapsdTime)
{

	if (m_waitTime >= 2)
	{
		m_waitTime = 0;
		return IBehaviorNode::State::Success;
	}

	m_waitTime += elapsdTime;

	return IBehaviorNode::State::Runngin;
}


/// <summary>
/// ����m�[�h
/// </summary>
/// <param name="elapsdTime"></param>
/// <returns></returns>
IBehaviorNode::State ExecutionNode::Patrol(float elapsdTime)
{




	return IBehaviorNode::State::Failure;
}


