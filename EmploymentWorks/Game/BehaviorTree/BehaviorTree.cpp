#include "pch.h"
#include "Game/BehaviorTree/BehaviorTree.h"
#include "BehaviorTree.h"
#include "Game/BehaviorTree/Root.h"
#include "Game/BehaviorTree/SequenceNode.h"
#include "Game/BehaviorTree/ActionNode.h"
#include "Game/BehaviorTree/SelectorNode.h"
#include "Game/BehaviorTree/DecoratorNode.h"

#include "ExecutionNode.h"
#include "Conditions.h"

BehaviorTree::BehaviorTree(Player* player, Enemy* enemy)
	:
	m_player{player},
	m_enemy{enemy}
{
}

BehaviorTree::~BehaviorTree()
{
	
}

void BehaviorTree::Initialize(CommonResources* resources)
{
	m_commonResources = resources;
	//実行ノードの作成
	m_executionNode = std::make_unique<ExecutionNode>(m_player,m_enemy);
	//条件ノードの作成
	m_conditions = std::make_unique<Conditions>(m_player,m_enemy);



	//プレイヤを見つけたかどうか
	auto FindPlayerDecorator = std::make_unique<DecoratorNode>(std::bind(&Conditions::FindToPlayer,m_conditions.get()));
	//プレイヤを見つけたかのActionノードの追加
	FindPlayerDecorator->AddNode(std::make_unique<ActionNode>(std::bind(&ExecutionNode::Patrol, m_executionNode.get(), std::placeholders::_1)));

	//シーケンスノードの作成
	auto RootSequence = std::make_unique<SequenceNode>();
	//Decoratorの追加
	RootSequence->AddNode(std::move(FindPlayerDecorator));


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


