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
#include "Game/Enemies/BossEnemy/BossEnemy.h"
#include "Game/InstanceRegistry.h"


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
void BehaviorTree::Initialize(CommonResources* resources, BossEnemy* enemy)
{
	m_commonResources = resources;
	m_enemy = enemy;
	
	m_player = InstanceRegistry::GetInstance()->GetRegistryInstance<Player>("Player");

	//実行ノードの作成
	m_executionNode = std::make_unique<ExecutionNode>(m_player, m_enemy);
	m_executionNode->Initialize(m_commonResources);
	//条件ノードの作成
	m_conditions = std::make_unique<Conditions>(m_commonResources, m_player, m_enemy);


//////HP半分以下

	//ジャンプ攻撃のデコレーター
	auto jumpAttackDecorator = CreateJumpAttackDecorator();
	jumpAttackDecorator->AddNode(CreateJumpAttackActionNode());

	//振り下ろし攻撃のデコレーター
	auto closeRangeAttackDecorator = CreateCloseRangeAttackDecorator();
	//振り下ろし攻撃の追加
	closeRangeAttackDecorator->AddNode(CreateSwingDownActionNode());



	//HPが半分以下のSelector
	auto lessThanHalfHP = std::make_unique<SelectorNode>();
	//近距離攻撃の追加
	lessThanHalfHP->AddNode(std::move(closeRangeAttackDecorator));
	//ジャンプ攻撃の追加
	lessThanHalfHP->AddNode(std::move(jumpAttackDecorator));
	//歩きの追加
	lessThanHalfHP->AddNode(CreateWalkingActionNode());



///////HP半分以上

	//遠距離攻撃のデコレーター
	auto longRangeAttackDecorator = CreateLongRangeAttackDecorator();
	//ビーム攻撃の追加
	longRangeAttackDecorator->AddNode(CreateBeamAttackActionNode());


	//振り下ろし攻撃のデコレーター
	closeRangeAttackDecorator = CreateCloseRangeAttackDecorator();
	//振り下ろし攻撃の追加
	closeRangeAttackDecorator->AddNode(CreateSwingDownActionNode());


	//HP半分以上のSelector
	auto moreThanHalfHP = std::make_unique<SelectorNode>();
	//近距離攻撃の追加
	moreThanHalfHP->AddNode(std::move(closeRangeAttackDecorator));
	//遠距離攻撃の追加
	moreThanHalfHP->AddNode(std::move(longRangeAttackDecorator));
	//歩きの追加
	moreThanHalfHP->AddNode(CreateWalkingActionNode());

	//HPが範囲内かどうかのデコレーター
	auto isMoreThanHalfHP = CreateIsHPMoreThanHalfDecorator();
	//Selectorの追加
	isMoreThanHalfHP->AddNode(std::move(moreThanHalfHP));

///////

	auto rootSelector = std::make_unique<SelectorNode>();
	//HPが半分以上のとき
	rootSelector->AddNode(std::move(isMoreThanHalfHP));
	//HPが半分以下
	rootSelector->AddNode(std::move(lessThanHalfHP));

	//ルートの作成
	m_root = std::make_unique<Root>();
	//RootSequenceノードの追加
	m_root->AddNode(std::move(rootSelector));
	

	//状態の初期化
	m_currentState = IBehaviorNode::State::FAILURE;


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
		case IBehaviorNode::State::SUCCESS:
		case IBehaviorNode::State::FAILURE:
			//評価と代入
			m_currentState = m_root->Update(elapsedTime);
			break;
		case IBehaviorNode::State::RUNNING:
			//実行中の更新と代入
			m_currentState = m_root->RunningUpdate(elapsedTime);
			break;
		default:
			break;
	}



}






/// <summary>
/// 振り下ろし攻撃のアクションノードの作成
/// </summary>
/// <returns>クラスを返す</returns>
std::unique_ptr<ActionNode> BehaviorTree::CreateSwingDownActionNode()
{
	return std::make_unique<ActionNode>(std::bind(&ExecutionNode::BossEnemySwingDown,m_executionNode.get()));
}

/// <summary>
/// ビーム攻撃のアクションノードの作成
/// </summary>
/// <returns></returns>
std::unique_ptr<ActionNode> BehaviorTree::CreateBeamAttackActionNode()
{
	return std::make_unique<ActionNode>(std::bind(&ExecutionNode::BossEnemyBeamAction, m_executionNode.get()));
}

/// <summary>
/// 歩くアクションノードの作成
/// </summary>
/// <returns></returns>
std::unique_ptr<ActionNode> BehaviorTree::CreateWalkingActionNode()
{
	return std::make_unique<ActionNode>(std::bind(&ExecutionNode::BossEnemyWalking, m_executionNode.get()));
}

/// <summary>
/// ジャンプ攻撃のアクションノードの作成
/// </summary>
/// <returns></returns>
std::unique_ptr<ActionNode> BehaviorTree::CreateJumpAttackActionNode()
{
	return std::make_unique<ActionNode>(std::bind(&ExecutionNode::BossEnemyJumpAttackAction, m_executionNode.get()));
}

std::unique_ptr<DecoratorNode> BehaviorTree::CreateIsHPMoreThanHalfDecorator()
{
	return std::make_unique<DecoratorNode>(std::bind(&Conditions::IsHPMoreThanHalf, m_conditions.get()));
}

/// <summary>
/// 近距離攻撃範囲内かどうかのDecoratorの作成
/// </summary>
/// <returns>クラスを返す</returns>
std::unique_ptr<DecoratorNode> BehaviorTree::CreateCloseRangeAttackDecorator()
{
	return std::make_unique<DecoratorNode>(std::bind(&Conditions::IsInCloseRangeAttack, m_conditions.get()));
}

/// <summary>
/// 遠距離攻撃範囲内かどうかかのDecoratorの作成
/// </summary>
/// <returns></returns>
std::unique_ptr<DecoratorNode> BehaviorTree::CreateLongRangeAttackDecorator()
{
	return std::make_unique<DecoratorNode>(std::bind(&Conditions::IsInLongRangeAttack, m_conditions.get()));
}

/// <summary>
/// ジャンプ攻撃攻撃範囲内かどうかのDecoratorの作成
/// </summary>
/// <returns></returns>
std::unique_ptr<DecoratorNode> BehaviorTree::CreateJumpAttackDecorator()
{
	return std::make_unique<DecoratorNode>(std::bind(&Conditions::IsJumpAttackRange, m_conditions.get()));
}


