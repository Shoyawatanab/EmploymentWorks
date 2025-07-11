/*
	�N���X��     : SequenceNode
	����         : �r�w�C�r�A�c���[�̃V�[�P���X�m�[�h
	�⑫�E���ӓ_ : ���ԂɎq�����s����B�S�Ă̎q�����s�ł����Success�A�q�����s�����炷����Failure�𔽂�
*/
#pragma once
#include "Game/Interface/ICompositeNode.h"


class CommonResources;


class SequenceNode : public ICompositeNode
{

public:
	//�R���X�g���N�^
	SequenceNode();
	//�f�X�g���N�^
	~SequenceNode()  override;
	//������
	void Initialize() override;
	//�X�V
	IBehaviorNode::State Update(const float& deltaTime) override;

	void Finalize() override;
	//�m�[�h�̒ǉ�
	void AddNode(std::unique_ptr<IBehaviorNode> node)  override;
private:
	//�q�m�[�h�z��
	std::vector<std::unique_ptr<IBehaviorNode>> m_childNode;


};