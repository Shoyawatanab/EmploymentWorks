/*
	ExecutionNode.h
	�n��Ė�
	���s�m�[�h�ɓn�������̊֐��̊Ǘ��N���X
*/

#pragma once
#include "Interface/IBehaviorNode.h"

class CommonResources;
class Player;
class Enemy;

class ExecutionNode 
{




private:
	//CommonResources* m_commonResources;

	Player* m_palyer;
	Enemy* m_enemy;


	//FindToPlayer�p�ϐ�

	// ReturnToTheStartingPoint�p�ϐ�
	
	//ChaseToPlayer�p�ϐ�
	static constexpr float CHASESPEED = 0.5f;

	float m_moveDistance;
	//Rotation�p�ϐ�
	
	float m_rotationTime;
	DirectX::SimpleMath::Quaternion m_rotate;

	// Wait�p�ϐ�
	float m_waitTime;

public:
	ExecutionNode(Player* player, Enemy* enmey);
	~ExecutionNode();



	IBehaviorNode::State ChaseToPlayer(float elapsdTime);


	IBehaviorNode::State Wait(float elapsdTime);

	IBehaviorNode::State Patrol(float elapsdTime);

};


/*����
�@BehaviorTree�N���X�ŃC���X�^���X���Ă��̃C���X�^���X��std::bind�Ń|�C���^�œn���Ă���̂ŃR���X�g���N�^�œn�����v���C����G�Ȃǂ��g�p���邱�Ƃ��ł���
�@
*/