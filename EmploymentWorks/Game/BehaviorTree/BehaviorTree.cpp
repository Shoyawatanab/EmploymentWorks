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
	
//Hpが半分未満の時

	////近距離攻撃範囲かどうかの生成
	//auto InCloseRangeAttackDecorator = std::make_unique<DecoratorNode>(std::bind(&Conditions::IsInCloseRangeAttack,m_conditions.get()));

	////近距離攻撃をするかどうかのSelectorの生成
	//auto IsCloseRangeAttackSelector = std::make_unique<SelectorNode>();
	////近距離攻撃範囲なかどうかの追加
	//IsCloseRangeAttackSelector->AddNode(std::move(InCloseRangeAttackDecorator));
	////何もしないの追加
	//IsCloseRangeAttackSelector->AddNode(std::make_unique<ActionNode>(std::bind(&ExecutionNode::DoNothing, m_executionNode.get())));
	////Sequenceの生成
	//auto LessThanHalfHPSequence = std::make_unique<SequenceNode>();
	////プレイヤに近づくの追加
	//LessThanHalfHPSequence->AddNode(std::make_unique<ActionNode>(std::bind(&ExecutionNode::ApproachingThePlayer, m_executionNode.get(), std::placeholders::_1)));
	////近距離攻撃をするかどうかのSelectorの追加

//HPが半分以上のとき

	//攻撃するかどうかの生成
	auto IsAttackDecorator3 = std::make_unique<DecoratorNode>(std::bind(&Conditions::IsAttack, m_conditions.get(), std::placeholders::_1));
	//遠距離攻撃の追加
	IsAttackDecorator3->AddNode(std::make_unique<ActionNode>(std::bind(&Enemy::BeamAttack, m_enemy, std::placeholders::_1)));

	//HPHalfで中りょりのSelectorの生成
	auto MidDistanceSelector = std::make_unique<SelectorNode>();
	//攻撃するかどうかの追加
	MidDistanceSelector->AddNode(std::move(IsAttackDecorator3));
	//プレイヤに近づくの追加
	MidDistanceSelector->AddNode(std::make_unique<ActionNode>(std::bind(&ExecutionNode::ApproachingThePlayer, m_executionNode.get(), std::placeholders::_1)));

 // //プレイヤとの距離が近い時
	//auto CloseDistanceDecorator = std::make_unique<DecoratorNode>(std::bind(&Conditions::IsInCloseRangeAttack, m_conditions.get()));
	////近距離攻撃のアクションノードの追加
	//CloseDistanceDecorator->AddNode(std::make_unique<ActionNode>(std::bind(&ExecutionNode::CloseRangeAttacks, m_executionNode.get(), std::placeholders::_1)));

	//プレイヤとの距離が遠いかのDecorator
	auto IsFarDistanceDecorator = std::make_unique<DecoratorNode>(std::bind(&Conditions::IsFarDistance, m_conditions.get()));
	//プレイヤに近づくの追加
	IsFarDistanceDecorator->AddNode(std::make_unique<ActionNode>(std::bind(&ExecutionNode::ApproachingThePlayer, m_executionNode.get(), std::placeholders::_1)));
	//Selectorの生成
	auto HPHalfSelector = std::make_unique<SelectorNode>();
	//プレイヤとの距離が遠い時の追加
	HPHalfSelector->AddNode(std::move(IsFarDistanceDecorator));
	//プレイヤとの距離が近い時
	//HPHalfSelector->AddNode(std::move(CloseDistanceDecorator));
	//中距離のときのSelectorの追加
	HPHalfSelector->AddNode(std::move(MidDistanceSelector));
 
	//HPが半分以上かどうか
	auto IsHPHalfDecorator = std::make_unique<DecoratorNode>(std::bind(&Conditions::IsHPMoreThanHalf, m_conditions.get()));
	//Selectorの追加
	IsHPHalfDecorator->AddNode(std::move(HPHalfSelector));

//HPMAXのとき
	//攻撃するかどうか
	auto IsAttackDecorator = std::make_unique<DecoratorNode>(std::bind(&Conditions::IsAttack, m_conditions.get(), std::placeholders::_1));
	//ビーム攻撃のアクションノードの追加
	IsAttackDecorator->AddNode(std::make_unique<ActionNode>(std::bind(&Enemy::BeamAttack, m_enemy, std::placeholders::_1)));
	
	//MAXHPSeletorの生成
	auto HPMAXSelector = std::make_unique<SelectorNode>();
	//攻撃するかどうかの追加
	HPMAXSelector->AddNode(std::move(IsAttackDecorator));
	//何もしないの追加
	HPMAXSelector->AddNode(std::make_unique<ActionNode>(std::bind(&ExecutionNode::DoNothing, m_executionNode.get())));
	
	//HPMAX時のSequenceの生成
	auto HPMAXSequence = std::make_unique<SequenceNode>();
	//プレイヤの方向を向くの追加
	HPMAXSequence->AddNode(std::make_unique<ActionNode>(std::bind(&ExecutionNode::FacingThePlayer, m_executionNode.get(), std::placeholders::_1)));
	//HPMAXSelectorのついか
	HPMAXSequence->AddNode(std::move(HPMAXSelector));
	//HPがMAXかどうかDecorator
	auto IsHPMAXDecorator = std::make_unique<DecoratorNode>(std::bind(&Conditions::IsHPMax, m_conditions.get()));
	//Sequenceの追加
	IsHPMAXDecorator->AddNode(std::move(HPMAXSequence));
	
	//大本のSelector
	auto RootSelector = std::make_unique<SelectorNode>();
	//HPMAXじのDecoratoｒの追加
	RootSelector->AddNode(std::move(IsHPMAXDecorator));
	//ＨＰ半分以上のDecoratoｒの追加
	RootSelector->AddNode(std::move(IsHPHalfDecorator));
	//ルートの作成
	m_root = std::make_unique<Root>();
	//RootSequenceノードの追加
	m_root->AddNode(std::move(RootSelector));

	//状態の初期化
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


