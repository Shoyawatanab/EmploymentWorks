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
	
	//�r�[���U��
	IBehaviorNode::State BossEnemyBeamAction();
	//�W�����v�U��
	IBehaviorNode::State BossEnemyJumpAttackAction();
	//����
	IBehaviorNode::State BossEnemyWalking();
	//�U�艺�낵�U��
	IBehaviorNode::State BossEnemySwingDown();


private:
	CommonResources* m_commonResources;

	Player* m_palyer;
	BossEnemy* m_enemy;


};


/*����
�@BehaviorTree�N���X�ŃC���X�^���X���Ă��̃C���X�^���X��std::bind�Ń|�C���^�œn���Ă���̂ŃR���X�g���N�^�œn�����v���C����G�Ȃǂ��g�p���邱�Ƃ��ł���
�@
*/