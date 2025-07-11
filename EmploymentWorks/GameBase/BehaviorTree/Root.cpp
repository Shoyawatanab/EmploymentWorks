/*
	�N���X��     : Root
	����         : �r�w�C�r�A�c���[�̃��[�g�m�[�h
	�⑫�E���ӓ_ :�@���ԂɎq�����s����B�S�Ă̎q�����s�ł����Success�A�q�����s�����炷����Failure�𔽂�
*/
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
IBehaviorNode::State Root::Update(const float& deltaTime)
{
	//�q�m�[�h�̎��s
	return 	m_childNode->Update(deltaTime);

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


