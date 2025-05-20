#include "pch.h"
#include "SelectorNode.h"


/// <summary>
/// �R���X�g���N�^
/// </summary>
SelectorNode::SelectorNode()
	:
	m_childNode{},
	m_runningNode{}
{
}

/// <summary>
/// �f�X�g���N�^
/// </summary>
SelectorNode::~SelectorNode()
{

}

/// <summary>
/// ������
/// </summary>
void SelectorNode::Initialize()
{
	m_runningNode = nullptr;
}

/// <summary>
/// �X�V
/// </summary>
/// <param name="elapsedTime">�o�ߎ���</param>
/// <returns>���s����</returns>
IBehaviorNode::State SelectorNode::Update(float elapsedTime)
{
	for (auto& node : m_childNode)
	{
		
		switch (node->Update(elapsedTime))
		{
			
			case IBehaviorNode::State::SUCCESS:
				//������Ԃ�
				return State::SUCCESS;
			case IBehaviorNode::State::FAILURE:
				//���̎q�m�[�h�������������邩������Ȃ����牽���Ԃ����p������
				break;
			case IBehaviorNode::State::RUNNING:
				//���s���m�[�h���i�[
				m_runningNode = node.get();
				return State::RUNNING;
			default:
				break;
		}

	}
	
	//�P���������Ȃ�������
	return State::FAILURE;

}

/// <summary>
/// ���s���̍X�V
/// </summary>
/// <param name="elapsedTime">�o�ߎ���</param>
/// <returns>���s����</returns>
IBehaviorNode::State SelectorNode::RunningUpdate(float elapsedTime)
{
	//�q�m�[�h�̎��s
	return m_runningNode->RunningUpdate(elapsedTime);
}



void SelectorNode::Finalize()
{
}

/// <summary>
/// �q�m�[�h�̒ǉ�
/// </summary>
/// <param name="node">�q�m�[�h</param>
void SelectorNode::AddNode(std::unique_ptr<IBehaviorNode> node)
{
	//������
	node->Initialize();
	//�ǉ�
	m_childNode.emplace_back(std::move(node));

}


