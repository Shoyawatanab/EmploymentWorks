#include "pch.h"
#include "BossBehaviorTree.h"
#include "GameBase/Common/Commons.h"
#include "GameBase/BehaviorTree/BehaviorTrees.h"

#include "ExecutionNode.h"
#include "Conditions.h"
#include "Game/Player/Player.h"
#include "Game/Enemies/BossEnemy/BossEnemy.h"



/// <summary>
/// �R���X�g���N�^
/// </summary>
BossBehaviorTree::BossBehaviorTree(Player* player, BossEnemy* enemy)
	:
	m_commonResources{}
	,m_root{}
	,m_player{player}
	,m_enemy{enemy}
	,m_executionNode{}
	,m_conditions{}
	,m_currentState{}
{

	m_commonResources = CommonResources::GetInstance();
	m_enemy = enemy;

	m_player =player;

	//���s�m�[�h�̍쐬
	m_executionNode = std::make_unique<ExecutionNode>(m_player, m_enemy);
	//�����m�[�h�̍쐬
	m_conditions = std::make_unique<Conditions>(m_player, m_enemy);

	//�m�[�h�c���[�̍쐬
	CreateNodeTree();


}

/// <summary>
/// �f�X�g���N�^
/// </summary>
BossBehaviorTree::~BossBehaviorTree()
{

}

/// <summary>
/// �X�V
/// </summary>
/// <param name="elapsedTime">�o�ߎ���</param>
void BossBehaviorTree::Update(const float& deltaTime)
{

	//���s���Ƃ���ȊO�ōX�V������ς���
	switch (m_currentState)
	{
		case IBehaviorNode::State::SUCCESS:
		case IBehaviorNode::State::FAILURE:
			//�]���Ƒ��
			m_currentState = m_root->Update(deltaTime);
			break;
		default:
			break;
	}

}



/// <summary>
/// �m�[�h�c���[�̍쐬
/// </summary>
void BossBehaviorTree::CreateNodeTree()
{


	//////HP�����ȉ�

		//�W�����v�U���̃f�R���[�^�[
	auto jumpAttackDecorator = CreateJumpAttackDecorator();
	jumpAttackDecorator->AddNode(CreateJumpAttackActionNode());

	//�U�艺�낵�U���̃f�R���[�^�[
	auto closeRangeAttackDecorator = CreateCloseRangeAttackDecorator();
	//�U�艺�낵�U���̒ǉ�
	closeRangeAttackDecorator->AddNode(CreateSwingDownActionNode());



	//HP�������ȉ���Selector
	auto lessThanHalfHP = std::make_unique<SelectorNode>();
	//�ߋ����U���̒ǉ�
	lessThanHalfHP->AddNode(std::move(closeRangeAttackDecorator));
	//�W�����v�U���̒ǉ�
	lessThanHalfHP->AddNode(std::move(jumpAttackDecorator));
	//�����̒ǉ�
	lessThanHalfHP->AddNode(CreateWalkingActionNode());



	///////HP�����ȏ�

		//�������U���̃f�R���[�^�[
	auto longRangeAttackDecorator = CreateLongRangeAttackDecorator();
	//�r�[���U���̒ǉ�
	longRangeAttackDecorator->AddNode(CreateBeamAttackActionNode());


	//�U�艺�낵�U���̃f�R���[�^�[
	closeRangeAttackDecorator = CreateCloseRangeAttackDecorator();
	//�U�艺�낵�U���̒ǉ�
	closeRangeAttackDecorator->AddNode(CreateSwingDownActionNode());


	//HP�����ȏ��Selector
	auto moreThanHalfHP = std::make_unique<SelectorNode>();
	//�ߋ����U���̒ǉ�
	moreThanHalfHP->AddNode(std::move(closeRangeAttackDecorator));
	//�������U���̒ǉ�
	moreThanHalfHP->AddNode(std::move(longRangeAttackDecorator));
	//�����̒ǉ�
	moreThanHalfHP->AddNode(CreateWalkingActionNode());

	//HP���͈͓����ǂ����̃f�R���[�^�[
	auto isMoreThanHalfHP = CreateIsHPMoreThanHalfDecorator();
	//Selector�̒ǉ�
	isMoreThanHalfHP->AddNode(std::move(moreThanHalfHP));

	///////

	auto rootSelector = std::make_unique<SelectorNode>();
	//HP�������ȏ�̂Ƃ�
	rootSelector->AddNode(std::move(isMoreThanHalfHP));
	//HP�������ȉ�
	rootSelector->AddNode(std::move(lessThanHalfHP));

	//���[�g�̍쐬
	m_root = std::make_unique<Root>();
	//RootSequence�m�[�h�̒ǉ�
	m_root->AddNode(std::move(rootSelector));


	//��Ԃ̏�����
	m_currentState = IBehaviorNode::State::FAILURE;

}


/// <summary>
/// �U�艺�낵�U���̃A�N�V�����m�[�h�̍쐬
/// </summary>
/// <returns>�N���X��Ԃ�</returns>
std::unique_ptr<ActionNode> BossBehaviorTree::CreateSwingDownActionNode()
{
	return std::make_unique<ActionNode>(std::bind(&ExecutionNode::BossEnemySwingDown,m_executionNode.get()));
}

/// <summary>
/// �r�[���U���̃A�N�V�����m�[�h�̍쐬
/// </summary>
/// <returns></returns>
std::unique_ptr<ActionNode> BossBehaviorTree::CreateBeamAttackActionNode()
{
	return std::make_unique<ActionNode>(std::bind(&ExecutionNode::BossEnemyBeamAction, m_executionNode.get()));
}

/// <summary>
/// �����A�N�V�����m�[�h�̍쐬
/// </summary>
/// <returns></returns>
std::unique_ptr<ActionNode> BossBehaviorTree::CreateWalkingActionNode()
{
	return std::make_unique<ActionNode>(std::bind(&ExecutionNode::BossEnemyWalking, m_executionNode.get()));
}

/// <summary>
/// �W�����v�U���̃A�N�V�����m�[�h�̍쐬
/// </summary>
/// <returns></returns>
std::unique_ptr<ActionNode> BossBehaviorTree::CreateJumpAttackActionNode()
{
	return std::make_unique<ActionNode>(std::bind(&ExecutionNode::BossEnemyJumpAttackAction, m_executionNode.get()));
}

std::unique_ptr<DecoratorNode> BossBehaviorTree::CreateIsHPMoreThanHalfDecorator()
{
	return std::make_unique<DecoratorNode>(std::bind(&Conditions::IsHPMoreThanHalf, m_conditions.get()));
}

/// <summary>
/// �ߋ����U���͈͓����ǂ�����Decorator�̍쐬
/// </summary>
/// <returns>�N���X��Ԃ�</returns>
std::unique_ptr<DecoratorNode> BossBehaviorTree::CreateCloseRangeAttackDecorator()
{
	return std::make_unique<DecoratorNode>(std::bind(&Conditions::IsInCloseRangeAttack, m_conditions.get()));
}

/// <summary>
/// �������U���͈͓����ǂ�������Decorator�̍쐬
/// </summary>
/// <returns></returns>
std::unique_ptr<DecoratorNode> BossBehaviorTree::CreateLongRangeAttackDecorator()
{
	return std::make_unique<DecoratorNode>(std::bind(&Conditions::IsInLongRangeAttack, m_conditions.get()));
}

/// <summary>
/// �W�����v�U���U���͈͓����ǂ�����Decorator�̍쐬
/// </summary>
/// <returns></returns>
std::unique_ptr<DecoratorNode> BossBehaviorTree::CreateJumpAttackDecorator()
{
	return std::make_unique<DecoratorNode>(std::bind(&Conditions::IsJumpAttackRange, m_conditions.get()));
}




