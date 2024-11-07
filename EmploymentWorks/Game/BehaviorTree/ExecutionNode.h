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




private:
	CommonResources* m_commonResources;

	Player* m_palyer;
	Enemy* m_enemy;

	////Patrol�p�ϐ�
	//std::vector<std::unique_ptr< PatrolPointo>> m_patrolPoint;
	////�ڎw�����W
	//DirectX::SimpleMath::Vector3 m_endPatrolPos;
	////���݂̃|�C���g�ԍ��@���̐i�ޏꏊ�����߂�̂Ɏg�p
	//int m_currentPointNumber;
	////�i��ł���|�C���g�ԍ�
	//int m_nextPointNumber;


public:
	ExecutionNode(Player* player, Enemy* enmey);
	~ExecutionNode();

	void Initialize(CommonResources* resources);


	//�v���C���̂ق��Ɍ���
	IBehaviorNode::State FacingThePlayer(float elapsdTime);
	//�r�[���U��
	//Enemy�N���X�̒��ɂ���
	
	//�v���C���ɋ߂Â�
	IBehaviorNode::State ApproachingThePlayer(float elapsdTime);

	//�ߋ����U��
	IBehaviorNode::State CloseRangeAttacks(float elapsdTime);
	//�������U��
	IBehaviorNode::State RangedAttack(float elapsdTime);

	//�������Ȃ�
	IBehaviorNode::State DoNothing();
};


/*����
�@BehaviorTree�N���X�ŃC���X�^���X���Ă��̃C���X�^���X��std::bind�Ń|�C���^�œn���Ă���̂ŃR���X�g���N�^�œn�����v���C����G�Ȃǂ��g�p���邱�Ƃ��ł���
�@
*/