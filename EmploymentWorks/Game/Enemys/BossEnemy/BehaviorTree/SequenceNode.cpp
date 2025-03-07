#include "pch.h"
#include "SequenceNode.h"


/// <summary>
/// �R���X�g���N�^
/// </summary>
SequenceNode::SequenceNode()
	:
	m_childNode{},
	m_runningNode{}
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
	m_runningNode = nullptr;
}

/// <summary>
/// �X�V
/// </summary>
/// <param name="elapsedTime">�o�ߎ���</param>
/// <returns>���s����</returns>
IBehaviorNode::State SequenceNode::Update(float elapsedTime)
{

	for (auto& node : m_childNode)
	{

		switch (node->Update(elapsedTime))
		{

			case IBehaviorNode::State::Success:
				break;
			case IBehaviorNode::State::Failure:
				return State::Failure;
			case IBehaviorNode::State::Runngin:
				//���s���m�[�h���i�[
				m_runningNode = node.get();
				return State::Runngin;
			default:
				break;
		}

	}

	//���ׂĐ���������
	return State::Success;
}

/// <summary>
/// ���s���̍X�V
/// </summary>
/// <param name="elapsedTime">�o�ߎ���</param>
/// <returns>���s����</returns>
IBehaviorNode::State SequenceNode::RunningUpdate(float elapsedTime)
{
	//�q�m�[�h�̎��s
	return m_runningNode->RunningUpdate(elapsedTime);
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


