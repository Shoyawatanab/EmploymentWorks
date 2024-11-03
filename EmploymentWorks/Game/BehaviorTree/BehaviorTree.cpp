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
	//実行ノードの作成
	m_executionNode = std::make_unique<ExecutionNode>(m_player, m_enemy);
	m_executionNode->Initialize(m_commonResources);
	//条件ノードの作成
	m_conditions = std::make_unique<Conditions>(m_commonResources, m_player, m_enemy);
	
	//攻撃するかどうか
	auto IsAttackDecorator = std::make_unique<DecoratorNode>(std::bind(&Conditions::IsAttack, m_conditions.get(), std::placeholders::_1));
	//ビーム攻撃のアクションノードの追加
	IsAttackDecorator->AddNode(std::make_unique<ActionNode>(std::bind(&Enemy::BeamAttack, m_enemy, std::placeholders::_1)));
	//シーケンスノードの作成
	auto RootSequence = std::make_unique<SequenceNode>();
	//プレイヤの方向を向くactionノードの追加
	RootSequence->AddNode(std::make_unique<ActionNode>(std::bind(&ExecutionNode::FacingThePlayer, m_executionNode.get(), std::placeholders::_1)));
	//IsAttackDecoroatorノードの追加
	RootSequence->AddNode(std::move(IsAttackDecorator));
	//ルートの作成
	m_root = std::make_unique<Root>();
	//RootSequenceノードの追加
	m_root->AddNode(std::move(RootSequence));


	m_currentState = IBehaviorNode::State::Failure;

}

void BehaviorTree::Update(float elapsedTime)
{

	//実行中とそれ以外で更新処理を変える
	switch (m_currentState)
	{
		case IBehaviorNode::State::Success:
		case IBehaviorNode::State::Failure:
			//評価と代入
			m_currentState = m_root->Update(elapsedTime);
			break;
		case IBehaviorNode::State::Runngin:
			//実行中の更新と代入
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


