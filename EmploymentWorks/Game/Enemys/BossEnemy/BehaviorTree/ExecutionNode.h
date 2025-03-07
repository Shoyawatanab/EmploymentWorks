/*
	ExecutionNode.h
	�n��Ė�
	���s�m�[�h�ɓn�������̊֐��̊Ǘ��N���X
*/

#pragma once
#include "Game/Interface/IBehaviorNode.h"
#include  <unordered_map>

class CommonResources;
class Player;
class BossEnemy;


class ExecutionNode
{

public:
	//�R���X�g���N�^
	ExecutionNode(Player* player, BossEnemy* enmey);
	//�f�X�g���N�^
	~ExecutionNode();
	//������
	void Initialize(CommonResources* resources);


	//�v���C���̂ق��Ɍ���
	IBehaviorNode::State FacingThePlayer(float elapsdTime);
	//�r�[���U��
	IBehaviorNode::State BeamAttack(float elapsdTime);
	
	//�v���C���ɋ߂Â�
	IBehaviorNode::State ApproachingThePlayer(float elapsdTime);

	//�ߋ����U��
	IBehaviorNode::State CloseRangeAttacks(float elapsdTime);
	//�������U��
	IBehaviorNode::State RangedAttack(float elapsdTime);

	//�������Ȃ�
	IBehaviorNode::State DoNothing();

private:
	CommonResources* m_commonResources;

	Player* m_palyer;
	BossEnemy* m_enemy;


};


/*����
�@BehaviorTree�N���X�ŃC���X�^���X���Ă��̃C���X�^���X��std::bind�Ń|�C���^�œn���Ă���̂ŃR���X�g���N�^�œn�����v���C����G�Ȃǂ��g�p���邱�Ƃ��ł���
�@
*/