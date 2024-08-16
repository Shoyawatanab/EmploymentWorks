#include "pch.h"
#include "Game/BehaviorTree/ActionNode.h"
#include "ActionNode.h"


/// <summary>
/// �R���X�g���N�^
/// </summary>
/// <param name="fun">�o�^����֐�</param>
ActionNode::ActionNode(std::function<IBehaviorNode::State(float)> fun)
{

	//�֐��̓o�^
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



