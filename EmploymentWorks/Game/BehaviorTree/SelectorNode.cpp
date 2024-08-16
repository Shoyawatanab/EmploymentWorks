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
				return State::Success;
			case IBehaviorNode::State::Failure:
				break;
			case IBehaviorNode::State::Runngin:
				//ŽÀs’†ƒm[ƒh‚ðŠi”[
				m_runningNode = node.get();
				return State::Runngin;

			default:
				break;
		}

	}
	
	//‚P‚Â‚à¬Œ÷‚µ‚È‚©‚Á‚½‚ç
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


