#include "pch.h"
#include "DecoratorNode.h"


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
IBehaviorNode::State DecoratorNode::Update(const float& deltaTime)
{

	//������false�Ȃ�
	if (!m_condition(deltaTime))
	{
		return State::FAILURE;
	}
	//�q�m�[�h�̎��s
	return m_childNode->Update(deltaTime);
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

