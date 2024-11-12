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



//

/// <summary>
///HP��MAX���ǂ��� 
/// </summary>
/// <returns>true : MAX�@false : NotMAX</returns>
bool Conditions::IsHPMax()
{
	//MAX�Ȃ�
	if (m_enemy->GetMAXHp() == m_enemy->GetHp())
	{
		return true;
	}


	return false;
}

/// <summary>
///�U�����邩�ǂ��� 
/// </summary>
/// <param name="elapsdTime"></param>
/// <returns>true : �U���@false : �U�����Ȃ�</returns>
bool Conditions::IsAttack(float elapsdTime)
{

	//�T�b�Ɉ��U��
	if (m_attackCoolTime >= 5)
	{
		//�ǂ����ŃN�[���^�C���̃��Z�b�g���K�v
		m_attackCoolTime = 0;
		//�U��
		return true;
	}

	m_attackCoolTime += elapsdTime;
	//�U�����Ȃ�
	return false;
}

//

/// <summary>
/// HP��HP�ȏォ�ǂ���
/// </summary>
/// <returns>true : �����ȏ�@false : ��������</returns>
bool Conditions::IsHPMoreThanHalf()
{

	float halfHP = m_enemy->GetMAXHp() / 2;


	//�����ȏ�Ȃ�
	if (halfHP <= m_enemy->GetHp())
	{
		return true;
	}

	return false;
}

//

/// <summary>
/// ���̋�����艓�����ǂ���
/// </summary>
/// <returns>true : �����@false :�@�߂�</returns>
bool Conditions::IsFarDistance()
{
	//���W�̎擾
	DirectX::SimpleMath::Vector3 PlayerPosition = m_palyer->GetPosition();
	DirectX::SimpleMath::Vector3 EnemyPosition = m_enemy->GetPosition();

	//Y���W�𓝈ꂷ��
	PlayerPosition.y = 0;
	EnemyPosition.y = 0;

	//���������߂�
	float Distance = DirectX::SimpleMath::Vector3::Distance(PlayerPosition, EnemyPosition);

	//�K��l��艓�����ǂ���
	if (Distance >= 30)
	{
		return true;
	}

	return false;
}

//

///// <summary>
///// �������߂����ǂ���
///// </summary>
///// <returns> true : �߂��@false : �߂��Ȃ�</returns>
//bool Conditions::IsCloseDistance()
//{
//
//	//���W�̎擾
//	DirectX::SimpleMath::Vector3 PlayerPosition = m_palyer->GetPosition();
//	DirectX::SimpleMath::Vector3 EnemyPosition = m_enemy->GetPosition();
//
//	//Y���W�𓝈ꂷ��
//	PlayerPosition.y = 0;
//	EnemyPosition.y = 0;
//
//	//���������߂�
//	float Distance = DirectX::SimpleMath::Vector3::Distance(PlayerPosition, EnemyPosition);
//
//	//�K��l���߂����ǂ���
//	if (Distance < 5)
//	{
//		return true;
//	}
//
//
//	return false;
//}

///// <summary>
///// �ߋ����U�����ǂ���
///// </summary>
///// <returns> true : �ߋ����U���@false : �������U��</returns>
//bool Conditions::IsCloseRangeAttack()
//{
//
//	//if (m_commonResources->GetJudgement()->GetLenght(m_palyer->GetPos(), m_enemy->GetPos()) <= 7)
//	//{
//	//	//�ߋ����U��
//	//	return true;
//	//}
//
//	//�������U��
//	return false;
//}

/// <summary>
/// �ߋ����U���͈͓����ǂ���
/// </summary>
/// <returns></returns>
bool Conditions::IsInCloseRangeAttack()
{


	//���W�̎擾
	DirectX::SimpleMath::Vector3 PlayerPosition = m_palyer->GetPosition();
	DirectX::SimpleMath::Vector3 EnemyPosition = m_enemy->GetPosition();

	//Y���W�𓝈ꂷ��
	PlayerPosition.y = 0;
	EnemyPosition.y = 0;

	//���������߂�
	float Distance = DirectX::SimpleMath::Vector3::Distance(PlayerPosition, EnemyPosition);

	//�U���͈͓����ǂ���
	if(Distance < 15.0f)
	{
		return true;
	}

	return false;
}


