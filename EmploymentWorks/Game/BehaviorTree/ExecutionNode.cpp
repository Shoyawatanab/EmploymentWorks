#include "pch.h"
#include "Game/BehaviorTree/ExecutionNode.h"
#include "ExecutionNode.h"

#include "Game/Object/Player/Player.h"
#include "Game/Object/Enemy/Enemy.h"
#include "Game/CommonResources.h"


static const float ROTATESPEED = 1.0f;
static const float PATROLSPEED = 2.0f;;


ExecutionNode::ExecutionNode(Player* player, Enemy* enemy)
	:
	m_commonResources{},
	m_palyer{ player },
	m_enemy{ enemy }
{

}

ExecutionNode::~ExecutionNode()
{

}

void ExecutionNode::Initialize(CommonResources* resources)
{

	m_commonResources = resources;


}






/// <summary>
/// �v���C���̂ق��Ɍ���
/// </summary>
/// <returns>true:���� , false:���s</returns>
IBehaviorNode::State ExecutionNode::FacingThePlayer(float elapsdTime)
{
	//������������
	DirectX::SimpleMath::Vector3 direction = m_palyer->GetPosition() - m_enemy->GetPosition();
	direction.Normalize();
	//���̓G�̑O����
	DirectX::SimpleMath::Vector3 forward = m_enemy->Getforward();
	//forward.Normalize();

	DirectX::SimpleMath::Vector3 moveAxis = forward.Cross(direction);

	if (moveAxis.y >= 0.0f)
	{
		moveAxis = DirectX::SimpleMath::Vector3::Up;
	}
	else
	{
		moveAxis = DirectX::SimpleMath::Vector3::Down;
	}

	//�p�x�����߂�
	float moveAngle = forward.Dot(direction);

	//if (moveAngle < 0.01f)
	//{
	//	return IBehaviorNode::State::Failure;
	//}

//���W�A���l�ɕϊ�
	moveAngle = acosf(moveAngle);

	//�p�x�Ƒ��x�̔�r�ŏ������ق����擾
	moveAngle = std::min(moveAngle, ROTATESPEED * elapsdTime);

	//�G�̉�]�̎擾
	DirectX::SimpleMath::Quaternion Rotate = m_enemy->GetRotate();
	//Y���ɑ΂��ĉ�]��������
	Rotate *= DirectX::SimpleMath::Quaternion::CreateFromAxisAngle(moveAxis, moveAngle);
	m_enemy->SetRotate(Rotate);

	//��]�����ƂɓG�̏����̕����x�N�g���̍X�V
	forward = DirectX::SimpleMath::Vector3::Transform(Enemy::INITIALFORWARD, Rotate);
	forward.Normalize();
	m_enemy->Setforward(forward);
	
	//����
	return IBehaviorNode::State::Success;
}

//�v���C���ɋ߂Â�
IBehaviorNode::State ExecutionNode::ApproachingThePlayer(float elapsdTime)
{
	//�v���C���̕���������
	FacingThePlayer(elapsdTime);

	//�G�̕����̏���
	m_enemy->Walk(elapsdTime);

	return IBehaviorNode::State::Success;

	////�v���C���̍��W�̎擾
	//DirectX::SimpleMath::Vector3 playerPosition = m_palyer->GetPosition();
	////�G�̍��W�̎擾
	//DirectX::SimpleMath::Vector3 enemyPosition = m_enemy->GetPosition();

	////���������߂�
	//DirectX::SimpleMath::Vector3 direction = playerPosition - enemyPosition;

	////���K��
	//direction.Normalize();


	//direction *= std::sin( elapsdTime * 2.0f);

	//enemyPosition += direction;

	//m_enemy->SetPosition(enemyPosition);

	//return IBehaviorNode::State::Success;
}

/// <summary>
/// �ߋ����U��
/// </summary>
/// <param name="elapsdTime"></param>
/// <returns></returns>
IBehaviorNode::State ExecutionNode::CloseRangeAttacks(float elapsdTime)
{
	assert(elapsdTime);

	//�v���C���̕���������
	FacingThePlayer(elapsdTime);

	//Enemy�N���X�̊֐����g�p
	return m_enemy->CloseRangeAttack(elapsdTime);
}

/// <summary>
/// �������U��
/// </summary>
/// <param name="elapsdTime"></param>
/// <returns></returns>
IBehaviorNode::State ExecutionNode::RangedAttack(float elapsdTime)
{
	assert(elapsdTime);

	//�������U����Render�̊֌W��Enemy�N���X�ō����BeamAttack���g�p���Ă���

	return m_enemy->BeamAttack(elapsdTime);

	//�U����
	//return IBehaviorNode::State::Runngin;
}

/// <summary>
/// �������Ȃ�
/// </summary>
/// <returns>������Ԃ�</returns>
IBehaviorNode::State ExecutionNode::DoNothing()
{
	//������Ԃ�
	return IBehaviorNode::State::Success;
}

