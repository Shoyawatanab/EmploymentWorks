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


BehaviorTree::BehaviorTree()
	:
	m_player{},
	m_enemy{}
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
	
	//�U�����邩�ǂ���
	auto IsAttackDecorator = std::make_unique<DecoratorNode>(std::bind(&Conditions::IsAttack, m_conditions.get(), std::placeholders::_1));
	//�r�[���U���̃A�N�V�����m�[�h�̒ǉ�
	IsAttackDecorator->AddNode(std::make_unique<ActionNode>(std::bind(&Enemy::BeamAttack, m_enemy, std::placeholders::_1)));
	//�V�[�P���X�m�[�h�̍쐬
	auto RootSequence = std::make_unique<SequenceNode>();
	//�v���C���̕���������action�m�[�h�̒ǉ�
	RootSequence->AddNode(std::make_unique<ActionNode>(std::bind(&ExecutionNode::FacingThePlayer, m_executionNode.get(), std::placeholders::_1)));
	//IsAttackDecoroator�m�[�h�̒ǉ�
	RootSequence->AddNode(std::move(IsAttackDecorator));
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

void BehaviorTree::RegistrationInformation(Player* player, Enemy* enemy)
{

	m_player = player;
	m_enemy = enemy;

}


