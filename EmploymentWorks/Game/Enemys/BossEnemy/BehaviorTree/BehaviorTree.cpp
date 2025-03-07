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
#include "Game/Enemys/BossEnemy/BossEnemy.h"


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
void BehaviorTree::Initialize(CommonResources* resources)
{
	m_commonResources = resources;
	//���s�m�[�h�̍쐬
	m_executionNode = std::make_unique<ExecutionNode>(m_player, m_enemy);
	m_executionNode->Initialize(m_commonResources);
	//�����m�[�h�̍쐬
	m_conditions = std::make_unique<Conditions>(m_commonResources, m_player, m_enemy);


	//�������U�����ǂ���
	auto longRangeDecoratior = std::make_unique<DecoratorNode>(std::bind(&Conditions::IsInLongRangeAttack, m_conditions.get()));
	//�������U��
	longRangeDecoratior->AddNode(std::make_unique<ActionNode>(std::bind(&BossEnemy::BeamAttack, m_enemy, std::placeholders::_1)));
	//longRangeDecoratior->AddNode(std::make_unique<ActionNode>(std::bind(&ExecutionNode::CloseRangeAttacks, m_executionNode.get(), std::placeholders::_1)));
	
	//�ߋ����U���͈͂Ȃ��ǂ���
	auto closeRangeDecoratior = std::make_unique<DecoratorNode>(std::bind(&Conditions::IsInCloseRangeAttack, m_conditions.get()));
	//�ߋ����U���̒ǉ�
	closeRangeDecoratior->AddNode(std::make_unique<ActionNode>( std::bind(&ExecutionNode::CloseRangeAttacks, m_executionNode.get(), std::placeholders::_1)));

	//����p���ǂ���
	auto isViewingAngle = std::make_unique<DecoratorNode>(std::bind(&Conditions::WithinViewingAngle, m_conditions.get()));
	//�v���C���̂ق�������
	isViewingAngle->AddNode(std::make_unique<ActionNode>(std::bind(&ExecutionNode::FacingThePlayer, m_executionNode.get(), std::placeholders::_1)));
	
	auto selector = std::make_unique<SelectorNode>();
	//����p�Ȃ����ǂ���
	selector->AddNode(std::move(isViewingAngle));
	//�ߋ����U���͈͓����ǂ���
	selector->AddNode(std::move(closeRangeDecoratior));
	//�������U���͈͓����ǂ���
	selector->AddNode(std::move(longRangeDecoratior));
	//�ړ�
	selector->AddNode(std::make_unique<ActionNode>(std::bind(&ExecutionNode::ApproachingThePlayer, m_executionNode.get(), std::placeholders::_1)));

	auto rootSequence = std::make_unique<SequenceNode>();
	//�v���C���̕����Ɍ���
	rootSequence->AddNode(std::make_unique<ActionNode>(std::bind(&ExecutionNode::FacingThePlayer, m_executionNode.get(), std::placeholders::_1)));
	//Selector�̒ǉ�
	rootSequence->AddNode(std::move(selector));

	//���[�g�̍쐬
	m_root = std::make_unique<Root>();
	//RootSequence�m�[�h�̒ǉ�
	m_root->AddNode(std::move(rootSequence));


	//��Ԃ̏�����
	m_currentState = IBehaviorNode::State::Failure;

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



/// <summary>
/// �K�v�ȃ|�C���^�̒ǉ�
/// </summary>
/// <param name="player">�v���C��</param>
/// <param name="enemy">�{�X�G</param>
void BehaviorTree::AddPointer(Player* player, BossEnemy* enemy)
{

	m_player = player;
	m_enemy = enemy;

}


