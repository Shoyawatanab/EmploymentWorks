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
	static constexpr float CLOSERANGEDISTANCE{ 7.0f };
	//�������U���͈̔�
	static constexpr float LONGRANGEDISTANCE{ 18.0f };

	//�G�̎���p
	static constexpr float ANGLE{ 60.0f };



public:
	//�R���X�g���N�^
	Conditions(CommonResources* resources, Player* player, BossEnemy* enmey);
	//�f�X�g���N�^
	~Conditions();
	//�ߋ����U���͈͓����ǂ���
	bool IsInCloseRangeAttack();
	//�������U���͈͓����ǂ���
	bool IsInLongRangeAttack();
	//����p�����ǂ���
	bool WithinViewingAngle();

	//���E�Ȃ����ǂ���
	bool IsEnemyInview(const DirectX::SimpleMath::Vector3& playerPos, const DirectX::SimpleMath::Vector3& playerForward, const DirectX::SimpleMath::Vector3& enemyPos);
private:
	//���ʃ��\�[�X
	CommonResources* m_commonResources;
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