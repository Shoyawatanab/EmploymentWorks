#include "pch.h"
#include "Game/BehaviorTree/DecoratorNode.h"
#include "DecoratorNode.h"

#include "Conditions.h"

DecoratorNode::DecoratorNode(std::function<bool()> fun)
{

	m_condition = fun;

	assert(m_condition);

}

DecoratorNode::~DecoratorNode()
{
}

void DecoratorNode::Initialize()
{

}

IBehaviorNode::State DecoratorNode::Update(float elapsedTime)
{

	//èåèÇ™falseÇ»ÇÁ
	if (!m_condition())
	{
		return State::Failure;
	}

	return m_childNode->Update(elapsedTime);
}

IBehaviorNode::State DecoratorNode::RunningUpdate(float elapsedTime)
{
	//èåèÇ™falseÇ»ÇÁ
	if (!m_condition)
	{
		return State::Failure;
	}

	return m_childNode->Update(elapsedTime);
}

void DecoratorNode::Render()
{
}

void DecoratorNode::Finalize()
{
}

/// <summary>
/// éqÉmÅ[ÉhÇÃí«â¡
/// </summary>
/// <param name="node"></param>
void DecoratorNode::AddNode(std::unique_ptr<IBehaviorNode> node)
{
	node->Initialize();

	m_childNode = std::move(node);

}

void DecoratorNode::AddConditions()
{


}


