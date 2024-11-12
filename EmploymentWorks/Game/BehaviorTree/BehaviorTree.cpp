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
	
//Hp�����������̎�

	////�ߋ����U���͈͂��ǂ����̐���
	//auto InCloseRangeAttackDecorator = std::make_unique<DecoratorNode>(std::bind(&Conditions::IsInCloseRangeAttack,m_conditions.get()));

	////�ߋ����U�������邩�ǂ�����Selector�̐���
	//auto IsCloseRangeAttackSelector = std::make_unique<SelectorNode>();
	////�ߋ����U���͈͂Ȃ��ǂ����̒ǉ�
	//IsCloseRangeAttackSelector->AddNode(std::move(InCloseRangeAttackDecorator));
	////�������Ȃ��̒ǉ�
	//IsCloseRangeAttackSelector->AddNode(std::make_unique<ActionNode>(std::bind(&ExecutionNode::DoNothing, m_executionNode.get())));
	////Sequence�̐���
	//auto LessThanHalfHPSequence = std::make_unique<SequenceNode>();
	////�v���C���ɋ߂Â��̒ǉ�
	//LessThanHalfHPSequence->AddNode(std::make_unique<ActionNode>(std::bind(&ExecutionNode::ApproachingThePlayer, m_executionNode.get(), std::placeholders::_1)));
	////�ߋ����U�������邩�ǂ�����Selector�̒ǉ�

//HP�������ȏ�̂Ƃ�

	//�U�����邩�ǂ����̐���
	auto IsAttackDecorator3 = std::make_unique<DecoratorNode>(std::bind(&Conditions::IsAttack, m_conditions.get(), std::placeholders::_1));
	//�������U���̒ǉ�
	IsAttackDecorator3->AddNode(std::make_unique<ActionNode>(std::bind(&Enemy::BeamAttack, m_enemy, std::placeholders::_1)));

	//HPHalf�Œ������Selector�̐���
	auto MidDistanceSelector = std::make_unique<SelectorNode>();
	//�U�����邩�ǂ����̒ǉ�
	MidDistanceSelector->AddNode(std::move(IsAttackDecorator3));
	//�v���C���ɋ߂Â��̒ǉ�
	MidDistanceSelector->AddNode(std::make_unique<ActionNode>(std::bind(&ExecutionNode::ApproachingThePlayer, m_executionNode.get(), std::placeholders::_1)));

 // //�v���C���Ƃ̋������߂���
	//auto CloseDistanceDecorator = std::make_unique<DecoratorNode>(std::bind(&Conditions::IsInCloseRangeAttack, m_conditions.get()));
	////�ߋ����U���̃A�N�V�����m�[�h�̒ǉ�
	//CloseDistanceDecorator->AddNode(std::make_unique<ActionNode>(std::bind(&ExecutionNode::CloseRangeAttacks, m_executionNode.get(), std::placeholders::_1)));

	//�v���C���Ƃ̋�������������Decorator
	auto IsFarDistanceDecorator = std::make_unique<DecoratorNode>(std::bind(&Conditions::IsFarDistance, m_conditions.get()));
	//�v���C���ɋ߂Â��̒ǉ�
	IsFarDistanceDecorator->AddNode(std::make_unique<ActionNode>(std::bind(&ExecutionNode::ApproachingThePlayer, m_executionNode.get(), std::placeholders::_1)));
	//Selector�̐���
	auto HPHalfSelector = std::make_unique<SelectorNode>();
	//�v���C���Ƃ̋������������̒ǉ�
	HPHalfSelector->AddNode(std::move(IsFarDistanceDecorator));
	//�v���C���Ƃ̋������߂���
	//HPHalfSelector->AddNode(std::move(CloseDistanceDecorator));
	//�������̂Ƃ���Selector�̒ǉ�
	HPHalfSelector->AddNode(std::move(MidDistanceSelector));
 
	//HP�������ȏォ�ǂ���
	auto IsHPHalfDecorator = std::make_unique<DecoratorNode>(std::bind(&Conditions::IsHPMoreThanHalf, m_conditions.get()));
	//Selector�̒ǉ�
	IsHPHalfDecorator->AddNode(std::move(HPHalfSelector));

//HPMAX�̂Ƃ�
	//�U�����邩�ǂ���
	auto IsAttackDecorator = std::make_unique<DecoratorNode>(std::bind(&Conditions::IsAttack, m_conditions.get(), std::placeholders::_1));
	//�r�[���U���̃A�N�V�����m�[�h�̒ǉ�
	IsAttackDecorator->AddNode(std::make_unique<ActionNode>(std::bind(&Enemy::BeamAttack, m_enemy, std::placeholders::_1)));
	
	//MAXHPSeletor�̐���
	auto HPMAXSelector = std::make_unique<SelectorNode>();
	//�U�����邩�ǂ����̒ǉ�
	HPMAXSelector->AddNode(std::move(IsAttackDecorator));
	//�������Ȃ��̒ǉ�
	HPMAXSelector->AddNode(std::make_unique<ActionNode>(std::bind(&ExecutionNode::DoNothing, m_executionNode.get())));
	
	//HPMAX����Sequence�̐���
	auto HPMAXSequence = std::make_unique<SequenceNode>();
	//�v���C���̕����������̒ǉ�
	HPMAXSequence->AddNode(std::make_unique<ActionNode>(std::bind(&ExecutionNode::FacingThePlayer, m_executionNode.get(), std::placeholders::_1)));
	//HPMAXSelector�̂���
	HPMAXSequence->AddNode(std::move(HPMAXSelector));
	//HP��MAX���ǂ���Decorator
	auto IsHPMAXDecorator = std::make_unique<DecoratorNode>(std::bind(&Conditions::IsHPMax, m_conditions.get()));
	//Sequence�̒ǉ�
	IsHPMAXDecorator->AddNode(std::move(HPMAXSequence));
	
	//��{��Selector
	auto RootSelector = std::make_unique<SelectorNode>();
	//HPMAX����Decorato���̒ǉ�
	RootSelector->AddNode(std::move(IsHPMAXDecorator));
	//�g�o�����ȏ��Decorato���̒ǉ�
	RootSelector->AddNode(std::move(IsHPHalfDecorator));
	//���[�g�̍쐬
	m_root = std::make_unique<Root>();
	//RootSequence�m�[�h�̒ǉ�
	m_root->AddNode(std::move(RootSelector));

	//��Ԃ̏�����
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


