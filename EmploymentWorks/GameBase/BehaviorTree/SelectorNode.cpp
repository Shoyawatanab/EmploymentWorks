#include "pch.h"
#include "SelectorNode.h"


/// <summary>
/// �R���X�g���N�^
/// </summary>
SelectorNode::SelectorNode()
	:
	m_childNode{}
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
}

/// <summary>
/// �X�V
/// </summary>
/// <param name="elapsedTime">�o�ߎ���</param>
/// <returns>���s����</returns>
IBehaviorNode::State SelectorNode::Update(const float& deltaTime)
{
	for (auto& node : m_childNode)
	{
		
		switch (node->Update(deltaTime))
		{
			
			case IBehaviorNode::State::SUCCESS:
				//������Ԃ�
				return State::SUCCESS;
			case IBehaviorNode::State::FAILURE:
				//���̎q�m�[�h�������������邩������Ȃ����牽���Ԃ����p������
				break;
			default:
				break;
		}

	}
	
	//�P���������Ȃ�������
	return State::FAILURE;

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


