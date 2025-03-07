#include "pch.h"
#include "Conditions.h"

#include "Game/Player/Player.h"
#include "Game/Enemys/BossEnemy/BossEnemy.h"
#include "Game/CommonResources.h"

using namespace DirectX::SimpleMath;

/// <summary>
/// �R���X�g���N�^
/// </summary>
/// <param name="resources">���ʃ��\�[�X</param>
/// <param name="player">�v���C��</param>
/// <param name="enemy">�{�X�G</param>
Conditions::Conditions(CommonResources* resources, Player* player, BossEnemy* enemy)
	:
	m_commonResources{ resources },
	m_palyer{ player },
	m_enemy{ enemy },
	m_attackCoolTime{}
{

}

/// <summary>
/// �f�X�g���N�^
/// </summary>
Conditions::~Conditions()
{

}





/// <summary>
/// �ߋ����U���͈͓����ǂ���
/// </summary>
/// <returns>ture �͈͓�  false�@�͈͊O�@</returns>
bool Conditions::IsInCloseRangeAttack()
{


	//���W�̎擾
	Vector3 PlayerPosition = m_palyer->GetPosition();
	Vector3 EnemyPosition = m_enemy->GetPosition();

	//Y���W�𓝈ꂷ��
	PlayerPosition.y = 0;
	EnemyPosition.y = 0;

	//���������߂�
	float Distance = Vector3::Distance(PlayerPosition, EnemyPosition);

	//�U���͈͓����ǂ���
	if(Distance < CLOSERANGEDISTANCE)
	{
		return true;
	}

	return false;
}

/// <summary>
/// �������U���͈͓����ǂ���
/// </summary>
/// <returns>true  �͈͓�  false�@�͈͊O�@</returns>
bool Conditions::IsInLongRangeAttack()
{
	//���W�̎擾
	Vector3 PlayerPosition = m_palyer->GetPosition();
	Vector3 EnemyPosition = m_enemy->GetPosition();

	//Y���W�𓝈ꂷ��
	PlayerPosition.y = 0;
	EnemyPosition.y = 0;

	//���������߂�
	float Distance = Vector3::Distance(PlayerPosition, EnemyPosition);

	//�U���͈͓����ǂ���
	if (Distance < LONGRANGEDISTANCE)
	{
		return true;
	}


	return false;
}

/// <summary>
/// ����p�Ȃ����ǂ���
/// </summary>
/// <returns>ture ����p�O  false�@����p�� </returns>
bool Conditions::WithinViewingAngle()
{

	Vector3 forward = Vector3::Backward;

	forward = Vector3::Transform(forward, m_enemy->GetRotation());
	forward.y = 0.0f;
	//�������Ȃ����ǂ���
	if(IsEnemyInview(m_enemy->GetPosition(), forward, m_palyer->GetPosition()))
	{

		//���E���Ȃ� 
		return false;

	}



	//����p����
	return true;
}

/// <summary>
///  �G���v���C���̎��E�ɓ����Ă��邩�ǂ���
/// </summary>
/// <param name="playerPos">�v���C�����W</param>
/// <param name="playerForward">�v���C���̌����Ă������</param>
/// <param name="enemyPos">�G���W</param>
/// <returns>true �F�Ȃ��@false �O</returns>
bool Conditions::IsEnemyInview(const DirectX::SimpleMath::Vector3& playerPos, const DirectX::SimpleMath::Vector3& playerForward, const DirectX::SimpleMath::Vector3& enemyPos)
{
	using namespace DirectX;
	using namespace DirectX::SimpleMath;
	//�p�x�����W�A���ɕϊ�
	float radianViewAngle = XMConvertToRadians(ANGLE);
	float cosViewAngle = cos(radianViewAngle / 2);

	//�G�ւ̃x�N�g���̌v�Z
	Vector3 enemyVector = enemyPos - playerPos;
	enemyVector.Normalize();
	enemyVector.y = 0.0f;

	//�h�b�g�ς̌v�Z
	float dotProduct = enemyVector.Dot(playerForward);

	return dotProduct >= cosViewAngle;

}
