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


	////�������U�����ǂ���
	//auto longRangeDecoratior = std::make_unique<DecoratorNode>(std::bind(&Conditions::IsInLongRangeAttack, m_conditions.get()));
	////�������U��
	//longRangeDecoratior->AddNode(std::make_unique<ActionNode>(std::bind(&BossEnemy::BeamAttack, m_enemy, std::placeholders::_1)));
	////longRangeDecoratior->AddNode(std::make_unique<ActionNode>(std::bind(&ExecutionNode::CloseRangeAttacks, m_executionNode.get(), std::placeholders::_1)));
	//
	////�ߋ����U���͈͂Ȃ��ǂ���
	//auto closeRangeDecoratior = std::make_unique<DecoratorNode>(std::bind(&Conditions::IsInCloseRangeAttack, m_conditions.get()));
	////�ߋ����U���̒ǉ�
	//closeRangeDecoratior->AddNode(std::make_unique<ActionNode>( std::bind(&ExecutionNode::CloseRangeAttacks, m_executionNode.get(), std::placeholders::_1)));

	////����p���ǂ���
	//auto isViewingAngle = std::make_unique<DecoratorNode>(std::bind(&Conditions::WithinViewingAngle, m_conditions.get()));
	////�v���C���̂ق�������
	//isViewingAngle->AddNode(std::make_unique<ActionNode>(std::bind(&ExecutionNode::FacingThePlayer, m_executionNode.get(), std::placeholders::_1)));
	//
	//auto selector = std::make_unique<SelectorNode>();
	////����p�Ȃ����ǂ���
	//selector->AddNode(std::move(isViewingAngle));
	////�ߋ����U���͈͓����ǂ���
	//selector->AddNode(std::move(closeRangeDecoratior));
	////�������U���͈͓����ǂ���
	//selector->AddNode(std::move(longRangeDecoratior));
	////�ړ�
	//selector->AddNode(std::make_unique<ActionNode>(std::bind(&ExecutionNode::ApproachingThePlayer, m_executionNode.get(), std::placeholders::_1)));

	//auto rootSequence = std::make_unique<SequenceNode>();
	////�v���C���̕����Ɍ���
	//rootSequence->AddNode(std::make_unique<ActionNode>(std::bind(&ExecutionNode::FacingThePlayer, m_executionNode.get(), std::placeholders::_1)));
	////Selector�̒ǉ�
	//rootSequence->AddNode(std::move(selector));

	////���[�g�̍쐬
	//m_root = std::make_unique<Root>();
	////RootSequence�m�[�h�̒ǉ�
	//m_root->AddNode(std::move(rootSequence));

///////HP�����ȏ�

	//�U�����邩�ǂ���Decorator
	auto isAttackDecorator = std::make_unique<DecoratorNode>(std::bind(&Conditions::IsAttack, m_conditions.get()));
	//�������U��
	isAttackDecorator->AddNode(std::make_unique<ActionNode>(std::bind( & ExecutionNode::BeamAttack, m_executionNode.get(), std::placeholders::_1)));

	//Selector
	auto LongRangeAttackSelector = std::make_unique<SelectorNode>();
	//�U�����邩�ǂ���Decorator
	LongRangeAttackSelector->AddNode(std::move(isAttackDecorator));
	//�v���C���ɋ߂Â�
	LongRangeAttackSelector->AddNode(std::make_unique<ActionNode>(std::bind(&ExecutionNode::ApproachingThePlayer, m_executionNode.get(), std::placeholders::_1)));


	//�������U��
	auto longRangeDecorator = std::make_unique<DecoratorNode>(std::bind(&Conditions::IsInLongRangeAttack, m_conditions.get()));
	//Selector�̒ǉ�
	longRangeDecorator->AddNode(std::move(LongRangeAttackSelector));
	
	//�ߋ����U���͈͒�
	auto IsCloseRangAttack = std::make_unique<DecoratorNode>(std::bind(&Conditions::IsInCloseRangeAttack, m_conditions.get()));
	//�ߋ����U��
	IsCloseRangAttack->AddNode(std::make_unique<ActionNode>(std::bind( & ExecutionNode::CloseRangeAttacks, m_executionNode.get(), std::placeholders::_1)));

	//�h��s����
	auto barrirSequence = std::make_unique<SequenceNode>();
	//�U��������
	barrirSequence->AddNode(std::make_unique<ActionNode>(std::bind(&ExecutionNode::FindAttackDirection, m_executionNode.get())));
	//�h��s��
	barrirSequence->AddNode(std::make_unique<ActionNode>(std::bind(&ExecutionNode::BarrierAction, m_executionNode.get(), std::placeholders::_1)));
	//�U������Ă��邩
	auto underAttack = std::make_unique<DecoratorNode>(std::bind(&Conditions::IsUnderAttack, m_conditions.get()));
	//Sequene�̒ǉ�
	underAttack->AddNode(std::move(barrirSequence));



	//Selector
	auto halfHPSelector = std::make_unique<SelectorNode>();
	//�h��
	halfHPSelector->AddNode(std::move(underAttack));
	//�ߋ����U��
	halfHPSelector->AddNode(std::move(IsCloseRangAttack));
	//Selector�̒ǉ�
	halfHPSelector->AddNode(std::move(longRangeDecorator));
	//�v���C���ɋ߂Â�
	halfHPSelector->AddNode(std::make_unique<ActionNode>(std::bind(&ExecutionNode::ApproachingThePlayer, m_executionNode.get(), std::placeholders::_1)));

	//Sequence
	auto halfHPSequence = std::make_unique<SequenceNode>();
	//�v���C���̕���������
	halfHPSequence->AddNode(std::make_unique<ActionNode>(std::bind(&ExecutionNode::FacingThePlayer, m_executionNode.get(), std::placeholders::_1)));
	//Selector�̒ǉ�
	halfHPSequence->AddNode(std::move(halfHPSelector));


	//HP�������ȏォ�ǂ���
	auto halfHPDecoratior = std::make_unique<DecoratorNode>(std::bind(&Conditions::IsHPMoreThanHalf, m_conditions.get()));
	//Sequnce�̒ǉ�
	halfHPDecoratior->AddNode(std::move(halfHPSequence));


////////�@HPMAX��

	//�U�����邩
	auto decorator = std::make_unique<DecoratorNode>(std::bind(&Conditions::IsInLongRangeAttack, m_conditions.get()));
	//�r�[���U��
	decorator->AddNode(std::make_unique<ActionNode>(std::bind(&ExecutionNode::BeamAttack, m_executionNode.get(), std::placeholders::_1)));

	//Selector
	auto selector = std::make_unique<SelectorNode>();
	//�U��Decorator�̒ǉ�
	selector->AddNode(std::move(decorator));
	//�v���C���ɋ߂Â�
	selector->AddNode(std::make_unique<ActionNode>(std::bind(&ExecutionNode::ApproachingThePlayer, m_executionNode.get(), std::placeholders::_1)));

	//�ő�HPSequence
	auto maxHpSequence = std::make_unique<SequenceNode>();
	//�v���C���̕���������
	maxHpSequence->AddNode(std::make_unique<ActionNode>(std::bind(&ExecutionNode::FacingThePlayer, m_executionNode.get(), std::placeholders::_1)));
	//selector�̒ǉ�
	maxHpSequence->AddNode(std::move(selector));

	//�ő�HP���ǂ���
	auto maxHPDecoratior = std::make_unique<DecoratorNode>(std::bind(&Conditions::IsMaxHp, m_conditions.get()));
	//Sequence�̒ǉ�
	maxHPDecoratior->AddNode(std::move(maxHpSequence));
////////


	auto rootSelector = std::make_unique<SelectorNode>();
	//HP���ő厞�̒ǉ�
	rootSelector->AddNode(std::move(maxHPDecoratior));
	//HP�������ȏ�̒ǉ�
	rootSelector->AddNode(std::move(halfHPDecoratior));

	//���[�g�̍쐬
	m_root = std::make_unique<Root>();
	//RootSequence�m�[�h�̒ǉ�
	m_root->AddNode(std::move(rootSelector));



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


