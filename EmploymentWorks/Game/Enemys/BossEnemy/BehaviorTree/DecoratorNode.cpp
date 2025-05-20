#include "pch.h"
#include "DecoratorNode.h"

#include "Conditions.h"

/// <summary>
/// �R���X�g���N�^
/// </summary>
/// <param name="fun">�o�^����֐�</param>
DecoratorNode::DecoratorNode(std::function<bool(float)> fun)
	:
	m_childNode{}
	,m_condition{}
{

	m_condition = fun;

	assert(m_condition);

}

/// <summary>
/// �f�X�g���N�^
/// </summary>
DecoratorNode::~DecoratorNode()
{
}

/// <summary>
/// ������
/// </summary>
void DecoratorNode::Initialize()
{

}

/// <summary>
/// �X�V
/// </summary>
/// <param name="elapsedTime">�o�ߎ���</param>
/// <returns>���s����</returns>
IBehaviorNode::State DecoratorNode::Update(float elapsedTime)
{

	//������false�Ȃ�
	if (!m_condition(elapsedTime))
	{
		return State::FAILURE;
	}
	//�q�m�[�h�̎��s
	return m_childNode->Update(elapsedTime);
}

/// <summary>
/// ���s���̍X�V
/// </summary>
/// <param name="elapsedTime">�o�ߎ���</param>
/// <returns>���s����</returns>
IBehaviorNode::State DecoratorNode::RunningUpdate(float elapsedTime)
{
	//�q�m�[�h�̎��s
	return m_childNode->RunningUpdate(elapsedTime);
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

