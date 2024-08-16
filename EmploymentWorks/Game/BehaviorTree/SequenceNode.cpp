#include "pch.h"
#include "Game/BehaviorTree/SequenceNode.h"
#include "SequenceNode.h"



SequenceNode::SequenceNode()
	:
	m_childNode{},
	m_runningNode{}
{

}

SequenceNode::~SequenceNode()
{

}

void SequenceNode::Initialize()
{
	m_runningNode = nullptr;
}


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
				//ŽÀs’†ƒm[ƒh‚ðŠi”[
				m_runningNode = node.get();
				return State::Runngin;
			default:
				break;
		}

	}

	//‚·‚×‚Ä¬Œ÷‚µ‚½‚ç
	return State::Success;
}

IBehaviorNode::State SequenceNode::RunningUpdate(float elapsedTime)
{
	return m_runningNode->RunningUpdate(elapsedTime);
}

void SequenceNode::Render()
{
}

void SequenceNode::Finalize()
{
}

void SequenceNode::AddNode(std::unique_ptr<IBehaviorNode> node)
{
	node->Initialize();
	m_childNode.emplace_back(std::move(node));

}


