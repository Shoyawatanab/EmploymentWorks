#include "pch.h"
#include "Root.h"


/// <summary>
/// �R���X�g���N�^
/// </summary>
Root::Root()
	:
	m_childNode{}
{

}

/// <summary>
/// �f�X�g���N�^
/// </summary>
Root::~Root()
{
	Finalize();
}

/// <summary>
/// ������
/// </summary>
void Root::Initialize()
{

}

/// <summary>
/// �X�V
/// </summary>
/// <param name="elapsedTime">�o�ߎ���</param>
/// <returns>���s����</returns>
IBehaviorNode::State Root::Update(float elapsedTime)
{
	//�q�m�[�h�̎��s
	return 	m_childNode->Update(elapsedTime);

}

/// <summary>
/// ���s���̍X�V
/// </summary>
/// <param name="elapsedTime">�o�ߎ���</param>
/// <returns>���s����</returns>
IBehaviorNode::State Root::RunningUpdate(float elapsedTime)
{
	//�q�m�[�h�̎��s
	return	m_childNode->RunningUpdate(elapsedTime);

}



void Root::Finalize()
{
}

/// <summary>
/// �K�v�ȃm�[�h�̒ǉ�
/// </summary>
/// <param name="node">�q�m�[�h</param>
void Root::AddNode(std::unique_ptr<IBehaviorNode> node)
{
	node->Initialize();

	m_childNode = std::move(node);

}


