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
	//実行ノードの作成
	m_executionNode = std::make_unique<ExecutionNode>(m_player, m_enemy);
	m_executionNode->Initialize(m_commonResources);
	//条件ノードの作成
	m_conditions = std::make_unique<Conditions>(m_commonResources, m_player, m_enemy);


	//近距離攻撃かどうかのDecoratorノード
	auto IsCloseRangeAttack2 = std::make_unique<DecoratorNode>(std::bind(&Conditions::IsCloseRangeAttack, m_conditions.get()));
	//逃げるノードの追加
	IsCloseRangeAttack2->AddNode(std::make_unique<ActionNode>(std::bind(&ExecutionNode::RunAway, m_executionNode.get(), std::placeholders::_1)));


	//攻撃の種類を決めるセレクターノード
	auto AttackMethods2Selector = std::make_unique<SelectorNode>();
	//一定の距離ないかどうかのDecoratorノードの追加
	AttackMethods2Selector->AddNode(std::move(IsCloseRangeAttack2));
	//遠距離攻撃ノードの追加
	//AttackMethods2Selector->AddNode(std::make_unique<ActionNode>(std::bind(&ExecutionNode::RangedAttack, m_executionNode.get(), std::placeholders::_1)));
	AttackMethods2Selector->AddNode(std::make_unique<ActionNode>(std::bind(&Enemy::BeamAttack, m_enemy, std::placeholders::_1)));



	//攻撃するかどうかのDecorator
	auto IsAttack2 = std::make_unique<DecoratorNode>(std::bind(&Conditions::IsAttack, m_conditions.get(), std::placeholders::_1));
	//攻撃の種類を決めるセレクターノードの追加
	IsAttack2->AddNode(std::move(AttackMethods2Selector));

	//HP半分以上のとき
	auto Attack2Selector = std::make_unique<SelectorNode>();
	//攻撃頻度内の追加
	Attack2Selector->AddNode(std::move(IsAttack2));
	//攻撃頻度外 何もしないの追加
	Attack2Selector->AddNode(std::make_unique<ActionNode>(std::bind(&ExecutionNode::DoNothing, m_executionNode.get())));





	//近距離攻撃かどうかのDecoratorノード
	auto IsCloseRangeAttack1 = std::make_unique<DecoratorNode>(std::bind(&Conditions::IsCloseRangeAttack, m_conditions.get()));
	//近距離攻撃ノードの追加
	IsCloseRangeAttack1->AddNode(std::make_unique<ActionNode>(std::bind(&ExecutionNode::CloseRangeAttacks, m_executionNode.get(), std::placeholders::_1)));


	//攻撃の種類を決めるセレクターノード
	auto AttackMethods1Selector = std::make_unique<SelectorNode>();
	//一定の距離ないかどうかのDecoratorノードの追加
	AttackMethods1Selector->AddNode(std::move(IsCloseRangeAttack1));
	//遠距離攻撃ノードの追加
	AttackMethods1Selector->AddNode(std::make_unique<ActionNode>(std::bind(&Enemy::BeamAttack, m_enemy, std::placeholders::_1)));


	//攻撃するかどうかのDecorator
	auto IsAttack = std::make_unique<DecoratorNode>(std::bind(&Conditions::IsAttack, m_conditions.get(), std::placeholders::_1));
	//攻撃の種類を決めるセレクターノードの追加
	IsAttack->AddNode(std::move(AttackMethods1Selector));

	//HP半分以上のとき
	auto Attack1Selector = std::make_unique<SelectorNode>();
	//攻撃頻度内の追加
	Attack1Selector->AddNode(std::move(IsAttack));

	//攻撃頻度外 何もしないの追加
	Attack1Selector->AddNode(std::make_unique<ActionNode>(std::bind(&ExecutionNode::DoNothing, m_executionNode.get())));

	//HPが半分以上かどうかのDecorator
	auto MoreThanHalfHPDecorator = std::make_unique<DecoratorNode>(std::bind(&Conditions::IsMoreThanHalfHP, m_conditions.get()));
	//セレクターノードの追加
	MoreThanHalfHPDecorator->AddNode(std::move(Attack1Selector));

	//HPセレクターノード
	auto HPSelector = std::make_unique<SelectorNode>();
	//HPが半分以上かどうかセレクターノードの追加
	HPSelector->AddNode(std::move(MoreThanHalfHPDecorator));
	//Hpが半分以下の時
	HPSelector->AddNode(std::move(Attack2Selector));

	//追いかける処理のシーケンスノード
	auto ChaseSequence = std::make_unique<SequenceNode>();
	//プレイヤの方向に向くノードの追加
	ChaseSequence->AddNode(std::make_unique<ActionNode>(std::bind(&ExecutionNode::FacingThePlayer, m_executionNode.get(), std::placeholders::_1)));
	ChaseSequence->AddNode(std::move(HPSelector));

	//プレイヤを見つけたかどうか
	auto FindPlayerDecorator = std::make_unique<DecoratorNode>(std::bind(&Conditions::IsFindToPlayer, m_conditions.get()));
	//プレイヤを見つけたかのActionノードの追加
	FindPlayerDecorator->AddNode(std::make_unique<ActionNode>(std::bind(&ExecutionNode::Patrol, m_executionNode.get(), std::placeholders::_1)));

	//シーケンスノードの作成
	auto RootSequence = std::make_unique<SelectorNode>();
	//Decoratorの追加
	RootSequence->AddNode(std::move(FindPlayerDecorator));
	//ChaseSequenceノードの追加
	RootSequence->AddNode(std::move(ChaseSequence));

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


