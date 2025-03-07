#include "pch.h"
#include "ActionNode.h"


/// <summary>
/// �R���X�g���N�^
/// </summary>
/// <param name="fun">�o�^����֐�</param>
ActionNode::ActionNode(std::function<IBehaviorNode::State(float)> fun)
	:
	m_executionNode{}
{

	//�֐��̓o�^
	m_executionNode = fun;

	assert(m_executionNode);

}

/// <summary>
///�f�X�g���N�^
/// </summary>
ActionNode::~ActionNode()
{

}

/// <summary>
/// ������
/// </summary>
void ActionNode::Initialize()
{

}

/// <summary>
/// �X�V
/// </summary>
/// <param name="elapsedTime">�o�ߎ���</param>
/// <returns>�֐��̎��s����</returns>
IBehaviorNode::State ActionNode::Update(float elapsedTime)
{

	return m_executionNode(elapsedTime);
}

/// <summary>
/// ���s���̍X�V
/// </summary>
/// <param name="elapsedTime">�o�ߎ���</param>
/// <returns>�֐��̎��s����</returns>
IBehaviorNode::State ActionNode::RunningUpdate(float elapsedTime)
{
	return m_executionNode(elapsedTime);
}

/// <summary>
/// �`��
/// </summary>
void ActionNode::Render()
{
}

void ActionNode::Finalize()
{
}



