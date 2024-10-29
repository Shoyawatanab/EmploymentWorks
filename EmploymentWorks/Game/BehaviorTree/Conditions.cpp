#include "pch.h"
#include "Game/BehaviorTree/Conditions.h"
#include "Conditions.h"

#include "Game/Object/Player/Player.h"
#include "Game/Object/Enemy/Enemy.h"
#include "Game/CommonResources.h"


Conditions::Conditions(CommonResources* resources, Player* player, Enemy* enemy)
	:
	m_commonResources{ resources },
	m_palyer{ player },
	m_enemy{ enemy },
	m_attackCoolTime{}
{

}

Conditions::~Conditions()
{

}



/// <summary>
/// �v���C�������������ǂ���
/// </summary>
/// <returns>���ĂȂ�:true ,������:false</returns>
bool Conditions::IsFindToPlayer()
{
	//����p�O
	if (!m_commonResources->GetJudgement()->IsWithinTheSector(m_palyer->GetPosition(), m_enemy->Getforward(), m_enemy->GetPosition(), 20, 90))
	{
		//����ɍs���Ăق����猩���Ă��Ȃ��Ƃ���true
		return true;
	}

	//Ray�̂��߂̕����x�N�g���̍쐬
	DirectX::SimpleMath::Vector3 Direction = m_palyer->GetPosition() - m_enemy->GetPosition();
	//���K��
	Direction.Normalize();

	//Ray�̍쐬
	DirectX::SimpleMath::Ray ray;
	ray.position = m_enemy->GetPosition();
	//Ray��direction�͐��K������Ă��邱��
	ray.direction = Direction;


	//��Q�������邩�ǂ���
	if (m_commonResources->GetJudgement()->IsRayToBoundingBox(ray, 1000))
	{
		return true;
	}

	//�U���Ȃǂ̃m�[�h�ɍs��
	return false;
}

/// <summary>
/// Hp�������ȏォ�ǂ���
/// </summary>
/// <returns></returns>
bool Conditions::IsMoreThanHalfHP()
{

	if (m_commonResources->GetJudgement()->GetRatio(m_enemy->GetHp(), m_enemy->GetMAXHp()) >= 0.5f)
	{
		//�����ȏ�
		return true;
	}

	//��������
	return false;
}

//�U�����邩�ǂ���
bool Conditions::IsAttack(float elapsdTime)
{

	//�T�b�Ɉ��U��
	if (m_attackCoolTime >= 5)
	{
		//�ǂ����ŃN�[���^�C���̃��Z�b�g���K�v
		m_attackCoolTime = 0;
		m_enemy->RegistrationRungingAnimation("Beam");

		//�U��
		return true;
	}



	m_attackCoolTime += elapsdTime;
	//�U�����Ȃ�
	return false;
}

/// <summary>
/// �ߋ����U�����ǂ���
/// </summary>
/// <returns></returns>
bool Conditions::IsCloseRangeAttack()
{

	//if (m_commonResources->GetJudgement()->GetLenght(m_palyer->GetPos(), m_enemy->GetPos()) <= 7)
	//{
	//	//�ߋ����U��
	//	return true;
	//}

	//�������U��
	return false;
}


