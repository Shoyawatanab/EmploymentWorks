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
	//CommonResources* m_commonResources;

	Player* m_palyer;
	Enemy* m_enemy;

	//ChasingDistance�p�ϐ�


	//IsRotation�p�ϐ�


public:
	Conditions(Player* player, Enemy* enmey);
	~Conditions();

	bool ChasingDistance();

	bool IsRotation();


	bool FindToPlayer();
};


/*����
�@BehaviorTree�N���X�ŃC���X�^���X���Ă��̃C���X�^���X��std::bind�Ń|�C���^�œn���Ă���̂ŃR���X�g���N�^�œn�����v���C����G�Ȃǂ��g�p���邱�Ƃ��ł���
�@
*/