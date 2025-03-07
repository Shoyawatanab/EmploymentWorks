#include "pch.h"
#include "ActionNode.h"


/// <summary>
/// コンストラクタ
/// </summary>
/// <param name="fun">登録する関数</param>
ActionNode::ActionNode(std::function<IBehaviorNode::State(float)> fun)
	:
	m_executionNode{}
{

	//関数の登録
	m_executionNode = fun;

	assert(m_executionNode);

}

/// <summary>
///デストラクタ
/// </summary>
ActionNode::~ActionNode()
{

}

/// <summary>
/// 初期化
/// </summary>
void ActionNode::Initialize()
{

}

/// <summary>
/// 更新
/// </summary>
/// <param name="elapsedTime">経過時間</param>
/// <returns>関数の実行結果</returns>
IBehaviorNode::State ActionNode::Update(float elapsedTime)
{

	return m_executionNode(elapsedTime);
}

/// <summary>
/// 実行中の更新
/// </summary>
/// <param name="elapsedTime">経過時間</param>
/// <returns>関数の実行結果</returns>
IBehaviorNode::State ActionNode::RunningUpdate(float elapsedTime)
{
	return m_executionNode(elapsedTime);
}

/// <summary>
/// 描画
/// </summary>
void ActionNode::Render()
{
}

void ActionNode::Finalize()
{
}



