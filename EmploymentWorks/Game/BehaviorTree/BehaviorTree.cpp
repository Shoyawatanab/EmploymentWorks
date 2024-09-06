#include "pch.h"
#include "Game/CommonResources.h"
#include "Game/BehaviorTree/BehaviorTree.h"
#include "BehaviorTree.h"
#include "Game/BehaviorTree/Root.h"
#include "Game/BehaviorTree/SequenceNode.h"
#include "Game/BehaviorTree/ActionNode.h"
#include "Game/BehaviorTree/SelectorNode.h"
#include "Game/BehaviorTree/DecoratorNode.h"

#include "ExecutionNode.h"
#include "Conditions.h"
#include "Game/Object/Enemy/Enemy.h"
#include "Game/Object/Player/Player.h"


BehaviorTree::BehaviorTree(Player* player, Enemy* enemy)
	:
	m_player{ player },
	m_enemy{ enemy }
{
}

BehaviorTree::~BehaviorTree()
{

}

void BehaviorTree::Initialize(CommonResources* resources)
{
	m_commonResources = resources;
	//���s�m�[�h�̍쐬
	m_executionNode = std::make_unique<ExecutionNode>(m_player, m_enemy);
	m_executionNode->Initialize(m_commonResources);
	//�����m�[�h�̍쐬
	m_conditions = std::make_unique<Conditions>(m_commonResources, m_player, m_enemy);


	//�ߋ����U�����ǂ�����Decorator�m�[�h
	auto IsCloseRangeAttack2 = std::make_unique<DecoratorNode>(std::bind(&Conditions::IsCloseRangeAttack, m_conditions.get()));
	//������m�[�h�̒ǉ�
	IsCloseRangeAttack2->AddNode(std::make_unique<ActionNode>(std::bind(&ExecutionNode::RunAway, m_executionNode.get(), std::placeholders::_1)));


	//�U���̎�ނ����߂�Z���N�^�[�m�[�h
	auto AttackMethods2Selector = std::make_unique<SelectorNode>();
	//���̋����Ȃ����ǂ�����Decorator�m�[�h�̒ǉ�
	AttackMethods2Selector->AddNode(std::move(IsCloseRangeAttack2));
	//�������U���m�[�h�̒ǉ�
	//AttackMethods2Selector->AddNode(std::make_unique<ActionNode>(std::bind(&ExecutionNode::RangedAttack, m_executionNode.get(), std::placeholders::_1)));
	AttackMethods2Selector->AddNode(std::make_unique<ActionNode>(std::bind(&Enemy::BeamAttack, m_enemy, std::placeholders::_1)));



	//�U�����邩�ǂ�����Decorator
	auto IsAttack2 = std::make_unique<DecoratorNode>(std::bind(&Conditions::IsAttack, m_conditions.get(), std::placeholders::_1));
	//�U���̎�ނ����߂�Z���N�^�[�m�[�h�̒ǉ�
	IsAttack2->AddNode(std::move(AttackMethods2Selector));

	//HP�����ȏ�̂Ƃ�
	auto Attack2Selector = std::make_unique<SelectorNode>();
	//�U���p�x���̒ǉ�
	Attack2Selector->AddNode(std::move(IsAttack2));
	//�U���p�x�O �������Ȃ��̒ǉ�
	Attack2Selector->AddNode(std::make_unique<ActionNode>(std::bind(&ExecutionNode::DoNothing, m_executionNode.get())));





	//�ߋ����U�����ǂ�����Decorator�m�[�h
	auto IsCloseRangeAttack1 = std::make_unique<DecoratorNode>(std::bind(&Conditions::IsCloseRangeAttack, m_conditions.get()));
	//�ߋ����U���m�[�h�̒ǉ�
	IsCloseRangeAttack1->AddNode(std::make_unique<ActionNode>(std::bind(&ExecutionNode::CloseRangeAttacks, m_executionNode.get(), std::placeholders::_1)));


	//�U���̎�ނ����߂�Z���N�^�[�m�[�h
	auto AttackMethods1Selector = std::make_unique<SelectorNode>();
	//���̋����Ȃ����ǂ�����Decorator�m�[�h�̒ǉ�
	AttackMethods1Selector->AddNode(std::move(IsCloseRangeAttack1));
	//�������U���m�[�h�̒ǉ�
	AttackMethods1Selector->AddNode(std::make_unique<ActionNode>(std::bind(&Enemy::BeamAttack, m_enemy, std::placeholders::_1)));


	//�U�����邩�ǂ�����Decorator
	auto IsAttack = std::make_unique<DecoratorNode>(std::bind(&Conditions::IsAttack, m_conditions.get(), std::placeholders::_1));
	//�U���̎�ނ����߂�Z���N�^�[�m�[�h�̒ǉ�
	IsAttack->AddNode(std::move(AttackMethods1Selector));

	//HP�����ȏ�̂Ƃ�
	auto Attack1Selector = std::make_unique<SelectorNode>();
	//�U���p�x���̒ǉ�
	Attack1Selector->AddNode(std::move(IsAttack));

	//�U���p�x�O �������Ȃ��̒ǉ�
	Attack1Selector->AddNode(std::make_unique<ActionNode>(std::bind(&ExecutionNode::DoNothing, m_executionNode.get())));

	//HP�������ȏォ�ǂ�����Decorator
	auto MoreThanHalfHPDecorator = std::make_unique<DecoratorNode>(std::bind(&Conditions::IsMoreThanHalfHP, m_conditions.get()));
	//�Z���N�^�[�m�[�h�̒ǉ�
	MoreThanHalfHPDecorator->AddNode(std::move(Attack1Selector));

	//HP�Z���N�^�[�m�[�h
	auto HPSelector = std::make_unique<SelectorNode>();
	//HP�������ȏォ�ǂ����Z���N�^�[�m�[�h�̒ǉ�
	HPSelector->AddNode(std::move(MoreThanHalfHPDecorator));
	//Hp�������ȉ��̎�
	HPSelector->AddNode(std::move(Attack2Selector));

	//�ǂ������鏈���̃V�[�P���X�m�[�h
	auto ChaseSequence = std::make_unique<SequenceNode>();
	//�v���C���̕����Ɍ����m�[�h�̒ǉ�
	ChaseSequence->AddNode(std::make_unique<ActionNode>(std::bind(&ExecutionNode::FacingThePlayer, m_executionNode.get(), std::placeholders::_1)));
	ChaseSequence->AddNode(std::move(HPSelector));

	//�v���C�������������ǂ���
	auto FindPlayerDecorator = std::make_unique<DecoratorNode>(std::bind(&Conditions::IsFindToPlayer, m_conditions.get()));
	//�v���C��������������Action�m�[�h�̒ǉ�
	FindPlayerDecorator->AddNode(std::make_unique<ActionNode>(std::bind(&ExecutionNode::Patrol, m_executionNode.get(), std::placeholders::_1)));

	//�V�[�P���X�m�[�h�̍쐬
	auto RootSequence = std::make_unique<SelectorNode>();
	//Decorator�̒ǉ�
	RootSequence->AddNode(std::move(FindPlayerDecorator));
	//ChaseSequence�m�[�h�̒ǉ�
	RootSequence->AddNode(std::move(ChaseSequence));

	//���[�g�̍쐬
	m_root = std::make_unique<Root>();
	//RootSequence�m�[�h�̒ǉ�
	m_root->AddNode(std::move(RootSequence));


	m_currentState = IBehaviorNode::State::Failure;

}

void BehaviorTree::Update(float elapsedTime)
{

	//���s���Ƃ���ȊO�ōX�V������ς���
	switch (m_currentState)
	{
		case IBehaviorNode::State::Success:
		case IBehaviorNode::State::Failure:
			//�]���Ƒ��
			m_currentState = m_root->Update(elapsedTime);
			break;
		case IBehaviorNode::State::Runngin:
			//���s���̍X�V�Ƒ��
			m_currentState = m_root->RunningUpdate(elapsedTime);
			break;
		default:
			break;
	}

}

void BehaviorTree::Render()
{
}

void BehaviorTree::Finalize()
{
}

void BehaviorTree::Create()
{

}


