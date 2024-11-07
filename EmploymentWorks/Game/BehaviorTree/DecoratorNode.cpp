#include "pch.h"
#include "Game/BehaviorTree/DecoratorNode.h"
#include "DecoratorNode.h"

#include "Conditions.h"

DecoratorNode::DecoratorNode(std::function<bool(float)> fun)
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

	//������false�Ȃ�
	if (!m_condition(elapsedTime))
	{
		return State::Failure;
	}

	return m_childNode->Update(elapsedTime);
}

IBehaviorNode::State DecoratorNode::RunningUpdate(float elapsedTime)
{


	return m_childNode->RunningUpdate(elapsedTime);
}

void DecoratorNode::Render()
{

}

void DecoratorNode::Finalize()
{
}

/// <summary>
/// �q�m�[�h�̒ǉ�
/// </summary>
/// <param name="node"></param>
void DecoratorNode::AddNode(std::unique_ptr<IBehaviorNode> node)
{
	//�q�m�[�h�̏�����
	node->Initialize();

	m_childNode = std::move(node);

}

