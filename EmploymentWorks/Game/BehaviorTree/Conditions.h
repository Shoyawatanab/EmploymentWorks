/*
	Conditions.h
	�n��Ė�
	Decorator�ɓn�������֐��̊Ǘ��N���X
*/

#pragma once
#include "Interface/IBehaviorNode.h"

class CommonResources;
class Player;
class Enemy;

class Conditions 
{




private:
	CommonResources* m_commonResources;

	Player* m_palyer;
	Enemy* m_enemy;

	//IsAttack�p�ϐ�
	float m_attackCoolTime;


public:
	Conditions(CommonResources* resources, Player* player, Enemy* enmey);
	~Conditions();


	//HP��MAX���ǂ���
	bool IsHPMax();
	//�U�����邩�ǂ���
	bool IsAttack(float elapsdTime);
	//HP��HP�ȏォ�ǂ���
	bool IsHPMoreThanHalf();
	//�������������ǂ���
	bool IsFarDistance();
	//�������߂����ǂ���
	//bool IsCloseDistance();
	//�ߋ����U�����ǂ���
	//bool IsCloseRangeAttack();
	//�ߋ����U���͈͓����ǂ���
	bool IsInCloseRangeAttack();

};


/*����
�@BehaviorTree�N���X�ŃC���X�^���X���Ă��̃C���X�^���X��std::bind�Ń|�C���^�œn���Ă���̂ŃR���X�g���N�^�œn�����v���C����G�Ȃǂ��g�p���邱�Ƃ��ł���
�@
*/