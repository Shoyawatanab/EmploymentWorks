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


/// <summary>
/// �v���C���̂ق��Ɍ���
/// </summary>
/// <returns>true:���� , false:���s</returns>
IBehaviorNode::State ExecutionNode::FacingThePlayer(float elapsdTime)
{
	return IBehaviorNode::State::Success;


	//������������
	DirectX::SimpleMath::Vector3 direction = m_palyer->GetPosition() - m_enemy->GetPosition();
	direction.Normalize();
	//���̓G�̑O����
	DirectX::SimpleMath::Vector3 forward = Vector3::Transform(Vector3::Backward,m_enemy->GetRotation());
	//forward.Normalize();
	//��]���̍쐬
	DirectX::SimpleMath::Vector3 moveAxis = forward.Cross(direction);

	if (moveAxis.y >= 0.0f)
	{
		//���Ȃ�����
		moveAxis = DirectX::SimpleMath::Vector3::Up;
	}
	else
	{
		//���Ȃ牺����
		moveAxis = DirectX::SimpleMath::Vector3::Down;
	}

	//�p�x�����߂�
	float moveAngle = forward.Dot(direction);


//���W�A���l�ɕϊ�
	moveAngle = acosf(moveAngle);

	//�p�x�Ƒ��x�̔�r�ŏ������ق����擾
	moveAngle = std::min(moveAngle, ROTATESPEED * elapsdTime);

	//�G�̉�]�̎擾
	DirectX::SimpleMath::Quaternion Rotate = m_enemy->GetRotation();
	//Y���ɑ΂��ĉ�]��������
	Rotate *= DirectX::SimpleMath::Quaternion::CreateFromAxisAngle(moveAxis, moveAngle);
	m_enemy->SetRotation(Rotate);

	
	//����
	return IBehaviorNode::State::Success;
}

/// <summary>
/// �r�[���U��
/// </summary>
/// <param name="elapsdTime">�o�ߎ���</param>
/// <returns>���s����</returns>
IBehaviorNode::State ExecutionNode::BeamAttack(float elapsdTime)
{
	//�v���C���̕���������
	FacingThePlayer(elapsdTime);

	//�G�N���X�̊֐����Ăяo��
	return m_enemy->BeamAttack(elapsdTime);
}

//�v���C���ɋ߂Â�

/// <summary>
/// �v���C���ɋ߂Â�
/// </summary>
/// <param name="elapsdTime">�o�ߎ���</param>
/// <returns>���s����</returns>
IBehaviorNode::State ExecutionNode::ApproachingThePlayer(float elapsdTime)
{
	//�v���C���̕���������
	FacingThePlayer(elapsdTime);


	return m_enemy->Walk(elapsdTime);


}

/// <summary>
/// �ߋ����U��
/// </summary>
/// <param name="elapsdTime"></param>
/// <returns>���s����</returns>
IBehaviorNode::State ExecutionNode::CloseRangeAttacks(float elapsdTime)
{
	assert(elapsdTime);

	return m_enemy->Pounding(elapsdTime);

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

	//return m_enemy->BeamAttack(elapsdTime);
	return IBehaviorNode::State::Success;

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

/// <summary>
/// �u�[�������̍U�����������߂�
/// </summary>
/// <returns></returns>
IBehaviorNode::State ExecutionNode::FindAttackDirection()
{
	return IBehaviorNode::State::Success;
}

IBehaviorNode::State ExecutionNode::BarrierAction(float elapsdTime)
{
	return m_enemy->BarrierDefense(elapsdTime) ;
}

