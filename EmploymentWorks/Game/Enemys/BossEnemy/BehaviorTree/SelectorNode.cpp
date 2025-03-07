#include "pch.h"
#include "SelectorNode.h"


/// <summary>
/// コンストラクタ
/// </summary>
SelectorNode::SelectorNode()
	:
	m_childNode{},
	m_runningNode{}
{
}

/// <summary>
/// デストラクタ
/// </summary>
SelectorNode::~SelectorNode()
{

}

/// <summary>
/// 初期化
/// </summary>
void SelectorNode::Initialize()
{
	m_runningNode = nullptr;
}

/// <summary>
/// 更新
/// </summary>
/// <param name="elapsedTime">経過時間</param>
/// <returns>実行結果</returns>
IBehaviorNode::State SelectorNode::Update(float elapsedTime)
{
	for (auto& node : m_childNode)
	{
		
		switch (node->Update(elapsedTime))
		{
			
			case IBehaviorNode::State::Success:
				//成功を返す
				return State::Success;
			case IBehaviorNode::State::Failure:
				//他の子ノードがせいこうするかもしれないから何も返さず継続する
				break;
			case IBehaviorNode::State::Runngin:
				//実行中ノードを格納
				m_runningNode = node.get();
				return State::Runngin;
			default:
				break;
		}

	}
	
	//１つも成功しなかったら
	return State::Failure;

}

/// <summary>
/// 実行中の更新
/// </summary>
/// <param name="elapsedTime">経過時間</param>
/// <returns>実行結果</returns>
IBehaviorNode::State SelectorNode::RunningUpdate(float elapsedTime)
{
	//子ノードの実行
	return m_runningNode->RunningUpdate(elapsedTime);
}



void SelectorNode::Finalize()
{
}

/// <summary>
/// 子ノードの追加
/// </summary>
/// <param name="node">子ノード</param>
void SelectorNode::AddNode(std::unique_ptr<IBehaviorNode> node)
{
	//初期化
	node->Initialize();
	//追加
	m_childNode.emplace_back(std::move(node));

}


