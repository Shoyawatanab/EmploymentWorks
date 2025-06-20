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

	assert(fun);

	//�֐��̓o�^
	m_executionNode = fun;


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
IBehaviorNode::State ActionNode::Update(const float& deltaTime)
{

	return m_executionNode(deltaTime);
}





void ActionNode::Finalize()
{
}



