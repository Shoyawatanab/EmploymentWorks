#include "pch.h"
#include "DecoratorNode.h"

#include "Conditions.h"

/// <summary>
/// コンストラクタ
/// </summary>
/// <param name="fun">登録する関数</param>
DecoratorNode::DecoratorNode(std::function<bool(float)> fun)
	:
	m_childNode{}
	,m_condition{}
{

	m_condition = fun;

	assert(m_condition);

}

/// <summary>
/// デストラクタ
/// </summary>
DecoratorNode::~DecoratorNode()
{
}

/// <summary>
/// 初期化
/// </summary>
void DecoratorNode::Initialize()
{

}

/// <summary>
/// 更新
/// </summary>
/// <param name="elapsedTime">経過時間</param>
/// <returns>実行結果</returns>
IBehaviorNode::State DecoratorNode::Update(float elapsedTime)
{

	//条件がfalseなら
	if (!m_condition(elapsedTime))
	{
		return State::FAILURE;
	}
	//子ノードの実行
	return m_childNode->Update(elapsedTime);
}

/// <summary>
/// 実行中の更新
/// </summary>
/// <param name="elapsedTime">経過時間</param>
/// <returns>実行結果</returns>
IBehaviorNode::State DecoratorNode::RunningUpdate(float elapsedTime)
{
	//子ノードの実行
	return m_childNode->RunningUpdate(elapsedTime);
}



void DecoratorNode::Finalize()
{



}

/// <summary>
/// 子ノードの追加
/// </summary>
/// <param name="node"></param>
void DecoratorNode::AddNode(std::unique_ptr<IBehaviorNode> node)
{
	//子ノードの初期化
	node->Initialize();

	m_childNode = std::move(node);

}

