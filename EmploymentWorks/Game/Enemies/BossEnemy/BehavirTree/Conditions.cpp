#include "pch.h"
#include "Conditions.h"
#include "GameBase/Common/Commons.h"
#include "Game/Player/Player.h"
#include "Game/Enemies/BossEnemy/BossEnemy.h"
#include "Game/Params.h"
#include "GameBase/Component/Components.h"
#include "Game/MathUtil.h"

/// <summary>
/// �R���X�g���N�^
/// </summary>
/// <param name="resources">���ʃ��\�[�X</param>
/// <param name="player">�v���C��</param>
/// <param name="enemy">�{�X�G</param>
Conditions::Conditions(Player* player, BossEnemy* enemy)
	:
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
	using namespace DirectX::SimpleMath;


	//���W�̎擾
	Vector3 PlayerPosition = m_palyer->GetTransform()->GetPosition();
	Vector3 EnemyPosition = m_enemy->GetTransform()->GetPosition();

	//Y���W�𓝈ꂷ��
	PlayerPosition.y = 0;
	EnemyPosition.y = 0;

	//���������߂�
	float Distance = Vector3::Distance(PlayerPosition, EnemyPosition);

	//�U���͈͓����ǂ���
	if(Distance < CLOSERANGE_ATTACK_DISTANCE)
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
	using namespace DirectX::SimpleMath;

	//���W�̎擾
	Vector3 PlayerPosition = m_palyer->GetTransform()->GetPosition();
	Vector3 EnemyPosition = m_enemy->GetTransform()->GetPosition();

	//Y���W�𓝈ꂷ��
	PlayerPosition.y = 0;
	EnemyPosition.y = 0;

	//���������߂�
	float Distance = Vector3::Distance(PlayerPosition, EnemyPosition);

	//�U���͈͓����ǂ���
	if (Distance < LONGRANGE_ATTACK_DISTANCE)
	{
		return true;
	}


	return false;
}

/// <summary>
/// �W�����v�U���͈͓����ǂ���
/// </summary>
/// <returns>ture : �͈͓�  false :�@�͈͊O</returns>
bool Conditions::IsJumpAttackRange()
{
	using namespace DirectX::SimpleMath;

	//���W�̎擾
	Vector3 PlayerPosition = m_palyer->GetTransform()->GetPosition();
	Vector3 EnemyPosition = m_enemy->GetTransform()->GetPosition();

	//Y���W�𓝈ꂷ��
	PlayerPosition.y = 0;
	EnemyPosition.y = 0;

	//���������߂�
	float Distance = Vector3::Distance(PlayerPosition, EnemyPosition);

	//�U���͈͓����ǂ���
	if (Distance < JUMP_ATTACK_DISTANCE)
	{
		return true;
	}


	return false;

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

/// <summary>
/// HP���ő傩�ǂ���
/// </summary>
/// <returns>ture : �ő� false:�ő傶��Ȃ�</returns>
bool Conditions::IsMaxHp()
{


	if (m_enemy->GetHp() == Params::BOSSENEMY_MAX_HP)
	{
		return true;
	}

	return false;
}

/// <summary>
/// HP�������ȏォ�ǂ���
/// </summary>
/// <returns>true : �����ȏ� false :��������</returns>
bool Conditions::IsHPMoreThanHalf()
{

	if (m_enemy->GetHp() >= Params::BOSSENEMY_MAX_HP / 2)
	{
		return true;
	}

	
	return false;
}

/// <summary>
/// �U�����邩�ǂ���
/// </summary>
/// <returns>ture : �U���@false : �U�����Ȃ�</returns>
bool Conditions::IsAttack()
{

	float ratio =MathUtil::GetRandom(0,100);

	if (ratio >= 30)
	{
		return true;
	}



	return false;
}



