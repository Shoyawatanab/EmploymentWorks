#include "pch.h"
#include "SequenceNode.h"


/// <summary>
/// �R���X�g���N�^
/// </summary>
SequenceNode::SequenceNode()
	:
	m_childNode{}
{

}

/// <summary>
/// �f�X�g���N�^
/// </summary>
SequenceNode::~SequenceNode()
{

}

/// <summary>
/// ������
/// </summary>
void SequenceNode::Initialize()
{
}

/// <summary>
/// �X�V
/// </summary>
/// <param name="elapsedTime">�o�ߎ���</param>
/// <returns>���s����</returns>
IBehaviorNode::State SequenceNode::Update(const float& deltaTime)
{

	for (auto& node : m_childNode)
	{

		switch (node->Update(deltaTime))
		{

			case IBehaviorNode::State::SUCCESS:
				break;
			case IBehaviorNode::State::FAILURE:
				return State::FAILURE;
			default:
				break;
		}

	}

	//���ׂĐ���������
	return State::SUCCESS;
}




void SequenceNode::Finalize()
{
}

/// <summary>
/// �q�m�[�h�̒ǉ�
/// </summary>
/// <param name="node">�q�m�[�h</param>
void SequenceNode::AddNode(std::unique_ptr<IBehaviorNode> node)
{
	//������
	node->Initialize();
	//�ǉ�
	m_childNode.emplace_back(std::move(node));

}


