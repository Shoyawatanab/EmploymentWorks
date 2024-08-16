#include "pch.h"
#include "Game/BehaviorTree/ActionNode.h"
#include "ActionNode.h"


/// <summary>
/// ÉRÉìÉXÉgÉâÉNÉ^
/// </summary>
/// <param name="fun">ìoò^Ç∑ÇÈä÷êî</param>
ActionNode::ActionNode(std::function<IBehaviorNode::State(float)> fun)
{

	//ä÷êîÇÃìoò^
	m_executionNode = fun;

	assert(m_executionNode);

}

ActionNode::~ActionNode()
{

}

void ActionNode::Initialize()
{

}

IBehaviorNode::State ActionNode::Update(float elapsedTime)
{

	return m_executionNode(elapsedTime);
}

IBehaviorNode::State ActionNode::RunningUpdate(float elapsedTime)
{
	return m_executionNode(elapsedTime);
}

void ActionNode::Render()
{
}

void ActionNode::Finalize()
{
}



