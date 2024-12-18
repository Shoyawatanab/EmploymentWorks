#include "pch.h"
#include "Game/BehaviorTree/SelectorNode.h"
#include "SelectorNode.h"



SelectorNode::SelectorNode()
	:
	m_childNode{},
	m_runningNode{}
{
}

SelectorNode::~SelectorNode()
{

}

void SelectorNode::Initialize()
{
	m_runningNode = nullptr;
}

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

IBehaviorNode::State SelectorNode::RunningUpdate(float elapsedTime)
{
	return m_runningNode->RunningUpdate(elapsedTime);
}

void SelectorNode::Render()
{
}

void SelectorNode::Finalize()
{
}

void SelectorNode::AddNode(std::unique_ptr<IBehaviorNode> node)
{
	node->Initialize();

	m_childNode.emplace_back(std::move(node));

}


