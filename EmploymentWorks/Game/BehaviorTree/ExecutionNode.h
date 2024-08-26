/*
	ExecutionNode.h
	�n��Ė�
	���s�m�[�h�ɓn�������̊֐��̊Ǘ��N���X
*/

#pragma once
#include "Interface/IBehaviorNode.h"
#include  <unordered_map>

class CommonResources;
class Player;
class Enemy;


class ExecutionNode
{

public:

	//���񂷂�Ƃ��̍��W
	struct PatrolPointo
	{
		//���W
		DirectX::SimpleMath::Vector3 Position;
		//�אڂ���|�C���g
		//std::vector<PatrolPointo*> m_adjacentPointo;

		std::unordered_map<int, PatrolPointo*> m_adjacentPointo;
		//�אڂ���ԍ�
		std::vector<int> m_adjacentNumber;

		//�אڂ�point�Ɣԍ��̓o�^
		void SetAdjacentPosint(int number, PatrolPointo* point) { m_adjacentPointo[number] = point; m_adjacentNumber.push_back(number); }

		//�אڂ̔ԍ����擾 number:�אڂ̐��͈̔͂Ń����_���ŋ��߂��l
		int GetAdjacentNumber(int number) { return m_adjacentNumber[number]; }
		//Point�̎擾�@number:�אڂ̔ԍ�
		PatrolPointo* GetAdjacentPointo(int number) { return m_adjacentPointo[number]; }


	};



private:
	CommonResources* m_commonResources;

	Player* m_palyer;
	Enemy* m_enemy;

	//Patrol�p�ϐ�
	std::vector<std::unique_ptr< PatrolPointo>> m_patrolPoint;
	//�ڎw�����W
	DirectX::SimpleMath::Vector3 m_endPatrolPos;
	//���݂̃|�C���g�ԍ��@���̐i�ޏꏊ�����߂�̂Ɏg�p
	int m_currentPointNumber;
	//�i��ł���|�C���g�ԍ�
	int m_nextPointNumber;


public:
	ExecutionNode(Player* player, Enemy* enmey);
	~ExecutionNode();

	void Initialize(CommonResources* resources);

	void CreatePatrol();

	void DecideNextPosition();

	//����
	IBehaviorNode::State Patrol(float elapsdTime);
	//�v���C���̂ق��Ɍ���
	IBehaviorNode::State FacingThePlayer(float elapsdTime);
	//�ߋ����U��
	IBehaviorNode::State CloseRangeAttacks(float elapsdTime);
	//�������U��
	IBehaviorNode::State RangedAttack(float elapsdTime);
	//�������Ȃ�
	IBehaviorNode::State DoNothing();
	//������
	IBehaviorNode::State RunAway(float elapsdTime);
};


/*����
�@BehaviorTree�N���X�ŃC���X�^���X���Ă��̃C���X�^���X��std::bind�Ń|�C���^�œn���Ă���̂ŃR���X�g���N�^�œn�����v���C����G�Ȃǂ��g�p���邱�Ƃ��ł���
�@
*/