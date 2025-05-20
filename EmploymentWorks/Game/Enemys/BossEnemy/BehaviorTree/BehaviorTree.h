/*
	BehaviorTree.h
	�n��Ė�
	�r�w�C�r�A�c���[��Root�ɓ�����N���X
*/
#pragma once
#include "Game/Interface/ICompositeNode.h"

class CommonResources;
class Root;
class Player;
class BossEnemy;
class ExecutionNode;
class Conditions;
class ActionNode;
class DecoratorNode;

class BehaviorTree
{
public:
	//�R���X�g���N�^
	BehaviorTree();
	//�f�X�g���N�^
	~BehaviorTree();
	//������
	void Initialize(CommonResources* resources);
	//�X�V
	void Update(float elapsedTime);
	//�N���X�ɕK�v�ȏ��i�|�C���^�j�̓o�^
	void AddPointer(Player* player, BossEnemy* enemy);

private:
	//�U�艺�낵�U���̍쐬
	std::unique_ptr<ActionNode> CreateSwingDownActionNode();
	//�r�[���U���̍쐬
	std::unique_ptr<ActionNode> CreateBeamAttackActionNode();
	//�����̍쐬
	std::unique_ptr<ActionNode> CreateWalkingActionNode();
	//�W�����v�U���̍쐬
	std::unique_ptr<ActionNode> CreateJumpAttackActionNode();





	//�ߋ����U���͈͓̔����ǂ�����Decorator�̍쐬
	std::unique_ptr<DecoratorNode> CreateCloseRangeAttackDecorator();
	//�������U���͈͓̔����ǂ�����Decorator�̍쐬
	std::unique_ptr<DecoratorNode> CreateLongRangeAttackDecorator();
	//�W�����v�U���͈͓̔����ǂ�����Decorator�̍쐬
	std::unique_ptr<DecoratorNode> CreateJumpAttackDecorator();


private:
	//���ʃ��\�[�X
	CommonResources* m_commonResources;

	//Root�Œ�`����ƏI�����ɃG���[���͂�
	std::unique_ptr<ICompositeNode> m_root;
	//�v���C��
	Player* m_player;
	//�{�X�G
	BossEnemy* m_enemy;

	//���s�m�[�h�N���X
	std::unique_ptr<ExecutionNode> m_executionNode;
	//�����m�[�h�̃N���X
	std::unique_ptr<Conditions> m_conditions;
	//���݂̏��
	IBehaviorNode::State m_currentState;

};

/*����
�@���t���[�����߂���`�F�b�N����
�@���s���m�[�h������ΏI���܂ł͎��s���̂ݓ�����
 

 ���P���邩���ȓ_
 �@���̃t���[�����Ƃɂ�����H�@���t���[���ł͂Ȃ�
�@�@���̎��͎��s��������΂�����ǂ����s���Ă��������l���Ȃ���΂Ȃ�Ȃ�
  ���s���͖��t���[�����s���𓮂����ĂȂ���Έ��̃t���[���ōX�V������ł��悢

*/