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
/// コンストラクタ
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
/// デストラクタ
/// </summary>
BehaviorTree::~BehaviorTree()
{

}

/// <summary>
/// 初期化
/// </summary>
/// <param name="resources">共通リソース</param>
void BehaviorTree::Initialize(CommonResources* resources)
{
	m_commonResources = resources;
	//実行ノードの作成
	m_executionNode = std::make_unique<ExecutionNode>(m_player, m_enemy);
	m_executionNode->Initialize(m_commonResources);
	//条件ノードの作成
	m_conditions = std::make_unique<Conditions>(m_commonResources, m_player, m_enemy);


	//遠距離攻撃かどうか
	auto longRangeDecoratior = std::make_unique<DecoratorNode>(std::bind(&Conditions::IsInLongRangeAttack, m_conditions.get()));
	//遠距離攻撃
	longRangeDecoratior->AddNode(std::make_unique<ActionNode>(std::bind(&BossEnemy::BeamAttack, m_enemy, std::placeholders::_1)));
	//longRangeDecoratior->AddNode(std::make_unique<ActionNode>(std::bind(&ExecutionNode::CloseRangeAttacks, m_executionNode.get(), std::placeholders::_1)));
	
	//近距離攻撃範囲なかどうか
	auto closeRangeDecoratior = std::make_unique<DecoratorNode>(std::bind(&Conditions::IsInCloseRangeAttack, m_conditions.get()));
	//近距離攻撃の追加
	closeRangeDecoratior->AddNode(std::make_unique<ActionNode>( std::bind(&ExecutionNode::CloseRangeAttacks, m_executionNode.get(), std::placeholders::_1)));

	//視野角かどうか
	auto isViewingAngle = std::make_unique<DecoratorNode>(std::bind(&Conditions::WithinViewingAngle, m_conditions.get()));
	//プレイヤのほうを向く
	isViewingAngle->AddNode(std::make_unique<ActionNode>(std::bind(&ExecutionNode::FacingThePlayer, m_executionNode.get(), std::placeholders::_1)));
	
	auto selector = std::make_unique<SelectorNode>();
	//視野角ないかどうか
	selector->AddNode(std::move(isViewingAngle));
	//近距離攻撃範囲内かどうか
	selector->AddNode(std::move(closeRangeDecoratior));
	//遠距離攻撃範囲内かどうか
	selector->AddNode(std::move(longRangeDecoratior));
	//移動
	selector->AddNode(std::make_unique<ActionNode>(std::bind(&ExecutionNode::ApproachingThePlayer, m_executionNode.get(), std::placeholders::_1)));

	auto rootSequence = std::make_unique<SequenceNode>();
	//プレイヤの方向に向く
	rootSequence->AddNode(std::make_unique<ActionNode>(std::bind(&ExecutionNode::FacingThePlayer, m_executionNode.get(), std::placeholders::_1)));
	//Selectorの追加
	rootSequence->AddNode(std::move(selector));

	//ルートの作成
	m_root = std::make_unique<Root>();
	//RootSequenceノードの追加
	m_root->AddNode(std::move(rootSequence));


	//状態の初期化
	m_currentState = IBehaviorNode::State::Failure;

}

/// <summary>
/// 更新
/// </summary>
/// <param name="elapsedTime">経過時間</param>
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



/// <summary>
/// 必要なポインタの追加
/// </summary>
/// <param name="player">プレイヤ</param>
/// <param name="enemy">ボス敵</param>
void BehaviorTree::AddPointer(Player* player, BossEnemy* enemy)
{

	m_player = player;
	m_enemy = enemy;

}


