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
	CreatePatrol();


}

void ExecutionNode::CreatePatrol()
{

	//�p�g���[�����W�̐���
	//0.�G�̏����n�_
	auto Pointo = std::make_unique<PatrolPointo>();
	Pointo->Position = DirectX::SimpleMath::Vector3(0, 5.75f, -10);
	m_patrolPoint.push_back(std::move(Pointo));
	//1.����
	Pointo = std::make_unique<PatrolPointo>();
	Pointo->Position = DirectX::SimpleMath::Vector3(-16, 5.75f, -14);
	m_patrolPoint.push_back(std::move(Pointo));
	//2.��
	Pointo = std::make_unique<PatrolPointo>();
	Pointo->Position = DirectX::SimpleMath::Vector3(-27, 5.75f, 0);
	m_patrolPoint.push_back(std::move(Pointo));
	//3.����
	Pointo = std::make_unique<PatrolPointo>();
	Pointo->Position = DirectX::SimpleMath::Vector3(-16, 5.75f, 14);
	m_patrolPoint.push_back(std::move(Pointo));
	//4.�v���C���̏����n�_
	Pointo = std::make_unique<PatrolPointo>();
	Pointo->Position = DirectX::SimpleMath::Vector3(0, 2.75f, 10);
	m_patrolPoint.push_back(std::move(Pointo));
	//5.�E��
	Pointo = std::make_unique<PatrolPointo>();
	Pointo->Position = DirectX::SimpleMath::Vector3(16, 5.75f, 14);
	m_patrolPoint.push_back(std::move(Pointo));
	//6.�E
	Pointo = std::make_unique<PatrolPointo>();
	Pointo->Position = DirectX::SimpleMath::Vector3(27, 5.75f, 0);
	m_patrolPoint.push_back(std::move(Pointo));
	//7.�E��
	Pointo = std::make_unique<PatrolPointo>();
	Pointo->Position = DirectX::SimpleMath::Vector3(16, 5.75f, -14);
	m_patrolPoint.push_back(std::move(Pointo));


	//�אڃ|�C���g�̓o�^
	//0�ɓo�^
	m_patrolPoint.at(0)->SetAdjacentPosint(1, m_patrolPoint[1].get());
	m_patrolPoint.at(0)->SetAdjacentPosint(2, m_patrolPoint[2].get());
	m_patrolPoint.at(0)->SetAdjacentPosint(4, m_patrolPoint[4].get());
	m_patrolPoint.at(0)->SetAdjacentPosint(6, m_patrolPoint[6].get());
	m_patrolPoint.at(0)->SetAdjacentPosint(7, m_patrolPoint[7].get());
	//1�ɓo�^
	m_patrolPoint.at(1)->SetAdjacentPosint(0, m_patrolPoint[0].get());
	m_patrolPoint.at(1)->SetAdjacentPosint(2, m_patrolPoint[2].get());
	m_patrolPoint.at(1)->SetAdjacentPosint(7, m_patrolPoint[7].get());
	//2�ɓo�^
	m_patrolPoint.at(2)->SetAdjacentPosint(0, m_patrolPoint[0].get());
	m_patrolPoint.at(2)->SetAdjacentPosint(1, m_patrolPoint[1].get());
	m_patrolPoint.at(2)->SetAdjacentPosint(3, m_patrolPoint[3].get());
	m_patrolPoint.at(2)->SetAdjacentPosint(4, m_patrolPoint[4].get());
	//3�ɓo�^
	m_patrolPoint.at(3)->SetAdjacentPosint(2, m_patrolPoint[2].get());
	m_patrolPoint.at(3)->SetAdjacentPosint(4, m_patrolPoint[4].get());
	m_patrolPoint.at(3)->SetAdjacentPosint(5, m_patrolPoint[5].get());
	//4�ɓo�^
	m_patrolPoint.at(4)->SetAdjacentPosint(0, m_patrolPoint[0].get());
	m_patrolPoint.at(4)->SetAdjacentPosint(2, m_patrolPoint[2].get());
	m_patrolPoint.at(4)->SetAdjacentPosint(4, m_patrolPoint[4].get());
	m_patrolPoint.at(4)->SetAdjacentPosint(5, m_patrolPoint[5].get());
	m_patrolPoint.at(4)->SetAdjacentPosint(6, m_patrolPoint[6].get());
	//5�ɓo�^
	m_patrolPoint.at(5)->SetAdjacentPosint(3, m_patrolPoint[3].get());
	m_patrolPoint.at(5)->SetAdjacentPosint(4, m_patrolPoint[4].get());
	m_patrolPoint.at(5)->SetAdjacentPosint(6, m_patrolPoint[6].get());
	//6�ɓo�^
	m_patrolPoint.at(6)->SetAdjacentPosint(0, m_patrolPoint[0].get());
	m_patrolPoint.at(6)->SetAdjacentPosint(4, m_patrolPoint[4].get());
	m_patrolPoint.at(6)->SetAdjacentPosint(5, m_patrolPoint[5].get());
	m_patrolPoint.at(6)->SetAdjacentPosint(7, m_patrolPoint[7].get());
	//7�ɓo�^
	m_patrolPoint.at(7)->SetAdjacentPosint(0, m_patrolPoint[0].get());
	m_patrolPoint.at(7)->SetAdjacentPosint(1, m_patrolPoint[1].get());
	m_patrolPoint.at(7)->SetAdjacentPosint(6, m_patrolPoint[6].get());


	//�����n�_��0������
	m_currentPointNumber = 0;
	DecideNextPosition();
}

/// <summary>
/// ���̍��W�����߂�
/// </summary>
void ExecutionNode::DecideNextPosition()
{

	//�אڂ̐������߂�
	int size = m_patrolPoint.at(m_currentPointNumber)->m_adjacentNumber.size() - 1;
	//�|�C���g�̗אڔԍ��̐������ƂɃ����_���Ŕԍ��̐���
	int number = m_commonResources->GetJudgement()->GetRandom(0, size);
	//�ԍ������ƂɎ��̗אڂ̔ԍ������߂�	
	number = m_patrolPoint.at(m_currentPointNumber)->GetAdjacentNumber(number);

	//number = 4;

	//�I���n�_�ɍ��W��������
	m_endPatrolPos = m_patrolPoint.at(m_currentPointNumber)->GetAdjacentPointo(number)->Position;
	//���̔Ԗ_�̓o�^
	m_nextPointNumber = number;


}


/// <summary>
/// ����m�[�h
/// </summary>
/// <param name="elapsdTime"></param>
/// <returns></returns>
IBehaviorNode::State ExecutionNode::Patrol(float elapsdTime)
{
	DirectX::SimpleMath::Vector3 EnemyPos = m_enemy->GetPos();

	//�i�ޕ��������߂�
	DirectX::SimpleMath::Vector3 MoveDirection = m_endPatrolPos - EnemyPos;
	MoveDirection.Normalize();

	MoveDirection *= PATROLSPEED * elapsdTime;

	EnemyPos += MoveDirection;

	m_enemy->SetPos(EnemyPos);

	//���������߂�
	float distance = (m_endPatrolPos - EnemyPos).Length();


	if (distance <= 2.5f)
	{
		//���̍��W��
		m_currentPointNumber = m_nextPointNumber;
		DecideNextPosition();
	}


	//�����]��
	//���̓G�̑O����
	DirectX::SimpleMath::Vector3 forward = m_enemy->Getforward();

	DirectX::SimpleMath::Vector3 moveAxis = forward.Cross(MoveDirection);

	if (moveAxis.y >= 0.0f)
	{
		moveAxis = DirectX::SimpleMath::Vector3::Up;
	}
	else
	{
		moveAxis = DirectX::SimpleMath::Vector3::Down;
	}

	//�p�x�����߂�
	float moveAngle = forward.Dot(MoveDirection);


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



	return IBehaviorNode::State::Success;
}



/// <summary>
/// �v���C���̂ق��Ɍ���
/// </summary>
/// <returns>true:���� , false:���s</returns>
IBehaviorNode::State ExecutionNode::FacingThePlayer(float elapsdTime)
{
	//������������
	DirectX::SimpleMath::Vector3 direction = m_palyer->GetPos() - m_enemy->GetPos();
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

	return IBehaviorNode::State::Success;
}

/// <summary>
/// �ߋ����U��
/// </summary>
/// <param name="elapsdTime"></param>
/// <returns></returns>
IBehaviorNode::State ExecutionNode::CloseRangeAttacks(float elapsdTime)
{
	return IBehaviorNode::State::Success;
}

/// <summary>
/// �������U��
/// </summary>
/// <param name="elapsdTime"></param>
/// <returns></returns>
IBehaviorNode::State ExecutionNode::RangedAttack(float elapsdTime)
{

	//�������U����Render�̊֌W��Enemy�N���X�ō����BeamAttack���g�p���Ă���



	//�U����
	return IBehaviorNode::State::Runngin;
}

/// <summary>
/// �������Ȃ�
/// </summary>
/// <returns></returns>
IBehaviorNode::State ExecutionNode::DoNothing()
{
	return IBehaviorNode::State::Success;
}

/// <summary>
/// ������
/// </summary>
/// <param name="elapsdTime"></param>
/// <returns></returns>
IBehaviorNode::State ExecutionNode::RunAway(float elapsdTime)
{
	return IBehaviorNode::State::Success;
}

