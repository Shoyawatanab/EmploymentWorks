#include "pch.h"
#include "Game/BehaviorTree/ActionNode.h"
#include "ActionNode.h"


/// <summary>
/// コンストラクタ
/// </summary>
/// <param name="fun">登録する関数</param>
ActionNode::ActionNode(std::function<IBehaviorNode::State(float)> fun)
{

	//関数の登録
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



