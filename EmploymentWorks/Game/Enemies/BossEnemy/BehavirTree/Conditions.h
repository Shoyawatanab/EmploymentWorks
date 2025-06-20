/*
	Conditions.h
	�n��Ė�
	Decorator�ɓn�������֐��̊Ǘ��N���X
*/

#pragma once
#include "Game/Interface/IBehaviorNode.h"

class CommonResources;
class Player;
class BossEnemy;

class Conditions 
{

public:

	//�ߋ����U���͈̔�
	static constexpr float CLOSERANGE_ATTACK_DISTANCE{ 7.0f };
	//�������U���͈̔�
	static constexpr float LONGRANGE_ATTACK_DISTANCE{ 18.0f };
	//�W�����v���U���͈̔�
	static constexpr float JUMP_ATTACK_DISTANCE{ 18.0f };

	//�G�̎���p
	static constexpr float ANGLE{ 60.0f };



public:
	//�R���X�g���N�^
	Conditions( Player* player, BossEnemy* enmey);
	//�f�X�g���N�^
	~Conditions();

	//�ߋ����U���͈͓����ǂ���
	bool IsInCloseRangeAttack();
	//�������U���͈͓����ǂ���
	bool IsInLongRangeAttack();
	//�W�����v�U���͈͓����ǂ���
	bool IsJumpAttackRange();

	//���E�Ȃ����ǂ���
	bool IsEnemyInview(const DirectX::SimpleMath::Vector3& playerPos, const DirectX::SimpleMath::Vector3& playerForward, const DirectX::SimpleMath::Vector3& enemyPos);
	//HP���ő傩�ǂ���
	bool IsMaxHp();
	//HP�������ȏォ
	bool IsHPMoreThanHalf();

	//�U�����邩�ǂ���
	bool IsAttack();


private:
	//�v���C��
	Player* m_palyer;
	//�{�X�G
	BossEnemy* m_enemy;

	//IsAttack�p�ϐ�
	float m_attackCoolTime;

};


/*����
�@BehaviorTree�N���X�ŃC���X�^���X���Ă��̃C���X�^���X��std::bind�Ń|�C���^�œn���Ă���̂ŃR���X�g���N�^�œn�����v���C����G�Ȃǂ��g�p���邱�Ƃ��ł���
�@
*/