#include "pch.h"
#include "SequenceNode.h"


/// <summary>
/// コンストラクタ
/// </summary>
SequenceNode::SequenceNode()
	:
	m_childNode{},
	m_runningNode{}
{

}

/// <summary>
/// デストラクタ
/// </summary>
SequenceNode::~SequenceNode()
{

}

/// <summary>
/// 初期化
/// </summary>
void SequenceNode::Initialize()
{
	m_runningNode = nullptr;
}

/// <summary>
/// 更新
/// </summary>
/// <param name="elapsedTime">経過時間</param>
/// <returns>実行結果</returns>
IBehaviorNode::State SequenceNode::Update(float elapsedTime)
{

	for (auto& node : m_childNode)
	{

		switch (node->Update(elapsedTime))
		{

			case IBehaviorNode::State::Success:
				break;
			case IBehaviorNode::State::Failure:
				return State::Failure;
			case IBehaviorNode::State::Runngin:
				//実行中ノードを格納
				m_runningNode = node.get();
				return State::Runngin;
			default:
				break;
		}

	}

	//すべて成功したら
	return State::Success;
}

/// <summary>
/// 実行中の更新
/// </summary>
/// <param name="elapsedTime">経過時間</param>
/// <returns>実行結果</returns>
IBehaviorNode::State SequenceNode::RunningUpdate(float elapsedTime)
{
	//子ノードの実行
	return m_runningNode->RunningUpdate(elapsedTime);
}


void SequenceNode::Finalize()
{
}

/// <summary>
/// 子ノードの追加
/// </summary>
/// <param name="node">子ノード</param>
void SequenceNode::AddNode(std::unique_ptr<IBehaviorNode> node)
{
	//初期化
	node->Initialize();
	//追加
	m_childNode.emplace_back(std::move(node));

}


