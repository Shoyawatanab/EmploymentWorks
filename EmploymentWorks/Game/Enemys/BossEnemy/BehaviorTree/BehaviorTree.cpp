#include "pch.h"
#include "Game/CommonResources.h"
#include "BehaviorTree.h"
#include "Root.h"
#include "SequenceNode.h"
#include "ActionNode.h"
#include "SelectorNode.h"
#include "DecoratorNode.h"

#include "ExecutionNode.h"
#include "Conditions.h"
#include "Game/Player/Player.h"
#include "Game/Enemies/BossEnemy/BossEnemy.h"
#include "Game/InstanceRegistry.h"


/// <summary>
/// �R���X�g���N�^
/// </summary>
BehaviorTree::BehaviorTree()
	:
	m_commonResources{}
	,m_root{}
	,m_player{}
	,m_enemy{}
	,m_executionNode{}
	,m_conditions{}
	,m_currentState{}
{
}

/// <summary>
/// �f�X�g���N�^
/// </summary>
BehaviorTree::~BehaviorTree()
{

}

/// <summary>
/// ������
/// </summary>
/// <param name="resources">���ʃ��\�[�X</param>
void BehaviorTree::Initialize(CommonResources* resources, BossEnemy* enemy)
{
	m_commonResources = resources;
	m_enemy = enemy;
	
	m_player = InstanceRegistry::GetInstance()->GetRegistryInstance<Player>("Player");

	//���s�m�[�h�̍쐬
	m_executionNode = std::make_unique<ExecutionNode>(m_player, m_enemy);
	m_executionNode->Initialize(m_commonResources);
	//�����m�[�h�̍쐬
	m_conditions = std::make_unique<Conditions>(m_commonResources, m_player, m_enemy);


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
/// �X�V
/// </summary>
/// <param name="elapsedTime">�o�ߎ���</param>
void BehaviorTree::Update(float elapsedTime)
{

	//���s���Ƃ���ȊO�ōX�V������ς���
	switch (m_currentState)
	{
		case IBehaviorNode::State::SUCCESS:
		case IBehaviorNode::State::FAILURE:
			//�]���Ƒ��
			m_currentState = m_root->Update(elapsedTime);
			break;
		case IBehaviorNode::State::RUNNING:
			//���s���̍X�V�Ƒ��
			m_currentState = m_root->RunningUpdate(elapsedTime);
			break;
		default:
			break;
	}



}






/// <summary>
/// �U�艺�낵�U���̃A�N�V�����m�[�h�̍쐬
/// </summary>
/// <returns>�N���X��Ԃ�</returns>
std::unique_ptr<ActionNode> BehaviorTree::CreateSwingDownActionNode()
{
	return std::make_unique<ActionNode>(std::bind(&ExecutionNode::BossEnemySwingDown,m_executionNode.get()));
}

/// <summary>
/// �r�[���U���̃A�N�V�����m�[�h�̍쐬
/// </summary>
/// <returns></returns>
std::unique_ptr<ActionNode> BehaviorTree::CreateBeamAttackActionNode()
{
	return std::make_unique<ActionNode>(std::bind(&ExecutionNode::BossEnemyBeamAction, m_executionNode.get()));
}

/// <summary>
/// �����A�N�V�����m�[�h�̍쐬
/// </summary>
/// <returns></returns>
std::unique_ptr<ActionNode> BehaviorTree::CreateWalkingActionNode()
{
	return std::make_unique<ActionNode>(std::bind(&ExecutionNode::BossEnemyWalking, m_executionNode.get()));
}

/// <summary>
/// �W�����v�U���̃A�N�V�����m�[�h�̍쐬
/// </summary>
/// <returns></returns>
std::unique_ptr<ActionNode> BehaviorTree::CreateJumpAttackActionNode()
{
	return std::make_unique<ActionNode>(std::bind(&ExecutionNode::BossEnemyJumpAttackAction, m_executionNode.get()));
}

std::unique_ptr<DecoratorNode> BehaviorTree::CreateIsHPMoreThanHalfDecorator()
{
	return std::make_unique<DecoratorNode>(std::bind(&Conditions::IsHPMoreThanHalf, m_conditions.get()));
}

/// <summary>
/// �ߋ����U���͈͓����ǂ�����Decorator�̍쐬
/// </summary>
/// <returns>�N���X��Ԃ�</returns>
std::unique_ptr<DecoratorNode> BehaviorTree::CreateCloseRangeAttackDecorator()
{
	return std::make_unique<DecoratorNode>(std::bind(&Conditions::IsInCloseRangeAttack, m_conditions.get()));
}

/// <summary>
/// �������U���͈͓����ǂ�������Decorator�̍쐬
/// </summary>
/// <returns></returns>
std::unique_ptr<DecoratorNode> BehaviorTree::CreateLongRangeAttackDecorator()
{
	return std::make_unique<DecoratorNode>(std::bind(&Conditions::IsInLongRangeAttack, m_conditions.get()));
}

/// <summary>
/// �W�����v�U���U���͈͓����ǂ�����Decorator�̍쐬
/// </summary>
/// <returns></returns>
std::unique_ptr<DecoratorNode> BehaviorTree::CreateJumpAttackDecorator()
{
	return std::make_unique<DecoratorNode>(std::bind(&Conditions::IsJumpAttackRange, m_conditions.get()));
}


